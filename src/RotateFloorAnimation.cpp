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
 * @file RotateFloorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "RotateFloorAnimation.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
RotateFloorAnimation::RotateFloorAnimation(const short& movementDirection) :
    direction(movementDirection)
{
    /* useless constructor, only used to set attributes */
}

/**
 *
 */
void RotateFloorAnimation::playNextAnimationStep(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* if the animation step is the first one, we create a sf::Transform object
       pointed by the level transform unique pointer */
    if (animationSteps == 0)
    {
        /* dynamically create the SFML transform object of the Level object */
        level->createTransform();
    }

    /* apply a rotation */
    level->rotateAllCells(5 * direction);
}

/**
 *
 */
void RotateFloorAnimation::renderAnimation(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    if (context->getClockMillisecondsTime() - lastAnimationUpdateTime < 50)
    {
        return;
    }

    playNextAnimationStep(
        context,
        level,
        floor
    );

    if (animationSteps == 18)
    {
        /* dynamically delete the SFML transform of the level object, we
           do not need it anymore at the end of the animation */
        level->deleteTransform();

        finished = true;
    }

    incrementAnimationStep(context);
}

}
}
