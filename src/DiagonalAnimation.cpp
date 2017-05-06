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
void DiagonalAnimation::renderAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    if (context.getClockMillisecondsTime() - getAnimationLastUpdateTime() < 100)
    {
        displayLevelAndSeparator(
            context,
            level,
            floor
        );

        return;
    }

    playNextAnimationStep(
        context,
        level,
        floor
    );

    displayLevelAndSeparator(
        context,
        level,
        floor
    );

    incrementAnimationStep(context);
}

/**
 *
 */
void DiagonalAnimation::playNextAnimationStep(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    /* declare a SFML color object; we use this object to create the flashing
       effect on the different parts of the cells */
    sf::Color color;

    const auto animationSteps = getAnimationSteps();

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
        context,
        level,
        floor,
        color
    );

    switch(animationSteps)
    {
    case 3:
    {
        invertTopLeftWithBottomRight(
            context,
            level,
            floor
        );

        break;
    }
    case 9:
    {
        invertBottomLeftWithTopRight(
            context,
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
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
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
    const utils::Context& context,
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
    const utils::Context& context,
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
                context,
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
    const utils::Context& context,
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
                context,
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
    const utils::Context& context,
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
        context,
        level,
        source + difference,
        level->getCells()[source]->isVisible()
    );

    showOrHideCell(
        context,
        level,
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
