/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file DiagonalAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DiagonalAnimation.hpp"

#include "SoundsManager.hpp"
#include "ColorsManager.hpp"
#include "ShapesManager.hpp"
#include "Cell.hpp"
#include "Level.hpp"

namespace memoris
{
namespace animations
{

class DiagonalAnimation::Impl
{

public:

    sf::RectangleShape verticalSeparator;
    sf::RectangleShape horizontalSeparator;
};

/**
 *
 */
DiagonalAnimation::DiagonalAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) :
    LevelAnimation(
        context,
        level,
        floor
    )
{
}

/**
 *
 */
DiagonalAnimation::~DiagonalAnimation() = default;

/**
 *
 */
void DiagonalAnimation::renderAnimation() &
{
    constexpr sf::Uint32 ANIMATION_INTERVAL {100};
    if (
        getContext().getClockMillisecondsTime() - 
        getAnimationLastUpdateTime() < ANIMATION_INTERVAL
    )
    {
        displayLevelAndSeparator();

        return;
    }

    playNextAnimationStep();

    displayLevelAndSeparator();

    incrementAnimationStep();
}

/**
 *
 */
void DiagonalAnimation::playNextAnimationStep() const &
{
    sf::Color color;

    const auto animationSteps = getAnimationSteps();
    const auto& context = getContext();
    const auto& colorsManager = context.getColorsManager();

    if (animationSteps == 0)
    {
        context.getSoundsManager().playFloorMovementAnimationSound();
    }

    if (animationSteps % 2 == 0)
    {
        color = colorsManager.getColorPurpleLowAlpha();
    }
    else
    {
        color = colorsManager.getColorWhite();
    }

    applyPurpleColorOnCellsQuarters(color);

    switch(animationSteps)
    {
    case 3:
    {
        invertTopLeftWithBottomRight();

        break;
    }
    case 9:
    {
        invertBottomLeftWithTopRight();

        break;
    }
    case 11:
    {
        endsAnimation();

        getLevel()->setPlayerCellIndex(getUpdatedPlayerIndex());

        break;
    }
    }
}

/**
 *
 */
void DiagonalAnimation::displayLevelAndSeparator() const &
{
    const auto& context = getContext();

    getLevel()->display(getFloor());

    auto& window = context.getSfmlWindow();
    const auto& shapesManager = context.getShapesManager();
    window.draw(shapesManager.getHorizontalSeparator());
    window.draw(shapesManager.getVerticalSeparator());
}

/**
 *
 */
void DiagonalAnimation::applyPurpleColorOnCellsQuarters(const sf::Color& color) 
    const &
{
    /* TODO: #1194 numbers should be constant expressions */

    const auto& floor = getFloor();

    for(
        unsigned short index = 256 * floor;
        index < 256 * (floor + 1);
        index++
    )
    {
        const auto animationSteps = getAnimationSteps();

        if (
            (
                (
                    (
                        index < floor * 256 + 128 &&
                        ((index - floor * 256) % 16) < 8
                    ) ||
                    (
                        index > floor * 256 + 128 &&
                        ((index - floor * 256) % 16) >= 8
                    )
                ) &&
                animationSteps < 6
            ) ||
            (
                (
                    (
                        index < floor * 256 + 128 &&
                        ((index - floor * 256) % 16) >= 8
                    ) ||
                    (
                        index >= floor * 256 + 128 &&
                        ((index - floor * 256) % 16) < 8
                    )
                ) && animationSteps >= 6
            )
        )
        {
            getLevel()->getCells()[index]->setCellColor(color);
        }
    }
}

/**
 *
 */
void DiagonalAnimation::invertTopLeftWithBottomRight() const &
{
    const auto& floor = getFloor();

    unsigned short index = floor * 256;

    while(index != floor * 256 + 128)
    {
        if (
            index < floor * 256 + 128 &&
            ((index - floor * 256) % 16) < 8
        )
        {
            invertCells(
                index,
                136
            );
        }

        index++;
    }
}

/**
 *
 */
void DiagonalAnimation::invertBottomLeftWithTopRight() const &
{
    const auto& floor = getFloor();
    unsigned short index = floor * 256 + 128;

    while(index < (floor + 1) * 256)
    {
        if (
            index >= floor * 256 + 128 &&
            ((index - floor * 256) % 16) < 8
        )
        {
            invertCells(
                index,
                -120
            );
        }

        index++;
    }
}

/**
 *
 */
void DiagonalAnimation::invertCells(
    const unsigned short& source,
    const short& difference
) const &
{
    const auto& level = getLevel();

    char type = level->getCells()[source + difference]->getType();
    bool visible = level->getCells()[source + difference]->isVisible();

    level->getCells()[source + difference]->setType(
        level->getCells()[source]->getType()
    );

    level->getCells()[source]->setType(type);

    showOrHideCell(
        source + difference,
        level->getCells()[source]->isVisible()
    );

    showOrHideCell(
        source,
        visible
    );

    if (source == level->getPlayerCellIndex())
    {
        setUpdatedPlayerIndex(source + difference);
    }
    else if (source + difference == level->getPlayerCellIndex())
    {
        setUpdatedPlayerIndex(source);
    }
}

}
}
