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
 * @file AbstractMirrorAnimation.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractMirrorAnimation.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
void AbstractMirrorAnimation::showOrHideCell(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& index,
    const bool& visible
)
{
    if (visible)
    {
        level->cells[index]->show(context);
    }
    else
    {
        level->cells[index]->hide(context);
    }
}

/**
 *
 */
void AbstractMirrorAnimation::renderAnimation(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* check if the animation interval time is elapsed; the animation step
       is incremented every 50 milliseconds */
    if (context->getClockMillisecondsTime() - lastAnimationUpdateTime < 50)
    {
        /* just render the level and the animation separator */
        displayLevelAndSeparator(
            context,
            level,
            floor
        );

        /* ends immedialely the animation process */
        return;
    }

    /* increment the animation step, this method is virtual and defined in
       both of the vertical and horizontal class definitions; so according
       to the current object type, the correct function is always called */
    playNextAnimationStep(
        context,
        level,
        floor
    );
}

/**
 *
 */
void AbstractMirrorAnimation::displayLevelAndSeparator(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* render the given floor of the level */
    level->display(
        context,
        floor
    );

    /* displays the mirror separator */
    context->getSfmlWindow().draw(separator);
}

/**
 *
 */
void AbstractMirrorAnimation::incrementAnimationStep(
    const std::shared_ptr<utils::Context>& context
)
{
    /* increments the animations step */
    animationSteps++;

    /* update the last animation update time to calculate the next iteration */
    lastAnimationUpdateTime = context->getClockMillisecondsTime();
}

}
}
