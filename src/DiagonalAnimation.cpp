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
void DiagonalAnimation::renderAnimation(const unsigned short& floor) &
{
    const auto& level = getLevel();

    if (
        getContext().getClockMillisecondsTime() - 
        getAnimationLastUpdateTime() < 100
    )
    {
        displayLevelAndSeparator(
            level,
            floor
        );

        return;
    }

    playNextAnimationStep(
        level,
        floor
    );

    displayLevelAndSeparator(
        level,
        floor
    );

    incrementAnimationStep();
}

/**
 *
 */
void DiagonalAnimation::playNextAnimationStep(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    /* declare a SFML color object; we use this object to create the flashing
       effect on the different parts of the cells */
    sf::Color color;

    const auto animationSteps = getAnimationSteps();
    const auto& context = getContext();

    if (animationSteps == 0)
    {
        context.getSoundsManager().playFloorMovementAnimationSound();
    }

    if (animationSteps % 2 == 0)
    {
        color = context.getColorsManager().getColorPurpleLowAlpha();
    }
    else
    {
        color = context.getColorsManager().getColorWhite();
    }

    applyPurpleColorOnCellsQuarters(
        level,
        floor,
        color
    );

    switch(animationSteps)
    {
    case 3:
    {
        invertTopLeftWithBottomRight(
            level,
            floor
        );

        break;
    }
    case 9:
    {
        invertBottomLeftWithTopRight(
            level,
            floor
        );

        break;
    }
    case 11:
    {
        endsAnimation();

        level->setPlayerCellIndex(getUpdatedPlayerIndex());

        break;
    }
    }
}

/**
 *
 */
void DiagonalAnimation::displayLevelAndSeparator(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    const auto& context = getContext();

    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    context.getSfmlWindow().draw(
        context.getShapesManager().getHorizontalSeparator()
    );
    context.getSfmlWindow().draw(
        context.getShapesManager().getVerticalSeparator()
    );
}

/**
 *
 */
void DiagonalAnimation::applyPurpleColorOnCellsQuarters(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor,
    const sf::Color& color
) &
{
    for(
        unsigned short index = 256 * floor;
        index < 256 * (floor + 1);
        index++
    )
    {
        const auto animationSteps = getAnimationSteps();

        /* use the purple color if the cell is located in the top left
           corner or the if the cell is located in the bottom right corner */
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
            level->getCells()[index]->setCellColor(color);
        }
    }
}

/**
 *
 */
void DiagonalAnimation::invertTopLeftWithBottomRight(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short index = floor * 256;

    while(index != floor * 256 + 128)
    {
        if (
            index < floor * 256 + 128 &&
            ((index - floor * 256) % 16) < 8
        )
        {
            invertCells(
                level,
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
void DiagonalAnimation::invertBottomLeftWithTopRight(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short index = floor * 256 + 128;

    while(index < (floor + 1) * 256)
    {
        if (
            index >= floor * 256 + 128 &&
            ((index - floor * 256) % 16) < 8
        )
        {
            invertCells(
                level,
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
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& source,
    const short& difference
) &
{
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
