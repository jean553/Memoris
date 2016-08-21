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
 * @file StairsAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "StairsAnimation.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
StairsAnimation::StairsAnimation(
    const std::shared_ptr<utils::Context>& context,
    const short& dir
) :
    direction(dir)
{
    /* this animation is a simple waiting period; in order to wait the
       appropriated time, we just save the current time once before the
       waiting period; if the animation just started, the last animation
       update time is equal to 0 */
    lastAnimationUpdateTime = context->getClockMillisecondsTime();
}

/**
 *
 */
void StairsAnimation::renderAnimation(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    level->display(
        context,
        floor + transformation
    );

    /* the waiting time is 2 seconds; this is enough to let the player see
       which cell he's just found */
    if (context->getClockMillisecondsTime() - lastAnimationUpdateTime < 100)
    {
        return;
    }

    playNextAnimationStep(
        context,
        level,
        floor
    );

    lastAnimationUpdateTime = context->getClockMillisecondsTime();
}

/**
 *
 */
void StairsAnimation::playNextAnimationStep(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* the animation does nothing during the 10 first steps (first second) */

    /* play the stop sound when the player just arrived on the cell */
    if (animationSteps == 0)
    {
        context->getSoundsManager().getCollisionSound().play();
    }

    /* play the floor switch sound when the floor starts to change */
    if (animationSteps == 10)
    {
        context->getSoundsManager().getFloorSwitchSound().play();
    }

    if (animationSteps >= 10 && animationSteps < 15)
    {
        /* change the transparency amount */
        cellsTransparency -= 51.f;

        /* update the transparency of all the cells to create a smooth floor
           closing effect */
        level->setCellsTransparency(
            context,
            cellsTransparency,
            floor
        );
    }
    else if (animationSteps == 15)
    {
        /* in order to animate the transition, we have to make all the next
           floor cells not visible first */
        level->setCellsTransparency(
            context,
            0.f,
            floor + direction
        );

        /* set the transformation variable, the next floor has to be displayed
           now instead of the original one */
        transformation = direction;
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        /* change the transparency amount */
        cellsTransparency += 51.f;

        /* displays the cells of the next floor and progressively apply the
           transparency */
        level->setCellsTransparency(
            context,
            cellsTransparency,
            floor + direction
        );
    }
    else if (animationSteps == 21)
    {
        /* the cells of the previous floor have to be visible, even if we are
           not on this floor anymore */
        level->setCellsTransparency(
            context,
            255.f,
            floor
        );

        finished = true;
    }

    animationSteps++;
}

}
}
