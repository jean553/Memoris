/*
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
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

#include "separators.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
DiagonalAnimation::DiagonalAnimation(
    utils::Context& context
)
{
    /* initializes both of the vertical and horizontal separator */

    initializeHorizontalSeparator(
        context,
        horizontalSeparator
    );

    initializeVerticalSeparator(
        context,
        verticalSeparator
    );

    /* plays the floor movement animation */
    context.getSoundsManager().playFloorMovementAnimationSound();
}

/**
 *
 */
void DiagonalAnimation::renderAnimation(
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    if (context.getClockMillisecondsTime() - lastAnimationUpdateTime < 100)
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
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* declare a SFML color object; we use this object to create the flashing
       effect on the different parts of the cells */
    sf::Color color;

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
        /* ends the animation after 11 steps */
        finished = true;

        /* put the player on his new cell */
        level->setPlayerCellIndex(playerCellIndexAfterAnimation);

        break;
    }
    }
}

/**
 *
 */
void DiagonalAnimation::displayLevelAndSeparator(
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* render the level at the given floor */
    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    /* displays the separators */
    context.getSfmlWindow().draw(horizontalSeparator);
    context.getSfmlWindow().draw(verticalSeparator);
}

/**
 *
 */
void DiagonalAnimation::applyPurpleColorOnCellsQuarters(
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor,
    const sf::Color& color
)
{
    for(
        unsigned short index = 256 * floor;
        index < 256 * (floor + 1);
        index++
    )
    {
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
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
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
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
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
    utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& source,
    const short& difference
)
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
        playerCellIndexAfterAnimation = source + difference;
    }
    else if (source + difference == level->getPlayerCellIndex())
    {
        playerCellIndexAfterAnimation = source;
    }
}

}
}
