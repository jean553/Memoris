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
    const std::shared_ptr<utils::Context>& context
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
}

/**
 *
 */
void DiagonalAnimation::renderAnimation(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    if (context->getClockMillisecondsTime() - lastAnimationUpdateTime < 250)
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
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* declare a SFML color object; we use this object to create the flashing
       effect on the different parts of the cells */
    sf::Color color;

    if (animationSteps % 2 == 0)
    {
        color = context->getColorsManager().getColorPurpleLowAlpha();
    }
    else
    {
        color = context->getColorsManager().getColorWhite();
    }

    applyPurpleColorOnCellsQuarters(
        context,
        level,
        floor,
        color
    );

    /* ends the animation when necessary */
    if (animationSteps == 11)
    {
        finished = true;
    }
}

/**
 *
 */
void DiagonalAnimation::displayLevelAndSeparator(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* render the level at the given floor */
    level->display(
        context,
        floor
    );

    /* displays the separators */
    context->getSfmlWindow().draw(horizontalSeparator);
    context->getSfmlWindow().draw(verticalSeparator);
}

/**
 *
 */
void DiagonalAnimation::applyPurpleColorOnCellsQuarters(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor,
    const sf::Color& color
)
{
    for(
        unsigned short index = 320 * floor;
        index < 320 * (floor + 1);
        index++
    )
    {
        /* use the purple color if the cell is located in the top left
           corner or the if the cell is located in the bottom right corner */
        if (
            (
                (
                    (
                        index < floor * 320 + 160 &&
                        ((index - floor * 320) % 20) < 10
                    ) ||
                    (
                        index > floor * 320 + 160 &&
                        ((index - floor * 320) % 20) >= 10
                    )
                ) &&
                animationSteps < 6
            ) ||
            (
                (
                    (
                        index < floor * 320 + 160 &&
                        ((index - floor * 320) % 20) >= 10
                    ) ||
                    (
                        index >= floor * 320 + 160 &&
                        ((index - floor * 320) % 20) < 10
                    )
                ) && animationSteps >= 6
            )
        )
        {
            level->getCells()[index]->setCellColor(color);
        }
    }
}

}
}
