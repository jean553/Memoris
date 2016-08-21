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
    const std::shared_ptr<utils::Context>& context
)
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
    /* just display the level during 2 seconds*/
    level->display(
        context,
        floor
    );

    /* the waiting time is 2 seconds; this is enough to let the player see
       which cell he's just found */
    if (context->getClockMillisecondsTime() - lastAnimationUpdateTime < 2000)
    {
        return;
    }

    /* ends the animation without calling the playNextAnimationStep(), this
       is superfluous for this animation a sthere is only one step exactly */
    finished = true;
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
    /* useless in this animation, only defined because this is a pure virtual
       method in the parent class */
}

}
}
