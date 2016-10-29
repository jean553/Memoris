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

#include "Level.hpp"
#include "ShapesManager.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
void AbstractMirrorAnimation::renderAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    if (
        context.getClockMillisecondsTime() -
        lastAnimationUpdateTime < ANIMATION_STEPS_INTERVAL
    )
    {
        level->display(
            context,
            floor,
            &entities::Cell::display
        );

        context.getSfmlWindow().draw(
            context.getShapesManager().getHorizontalSeparator()
        );

        return;
    }

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

    context.getSfmlWindow().draw(separator);
}

}
}
