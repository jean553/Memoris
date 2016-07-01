/**
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
 * @file Controller.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Controller.hpp"

#include "window.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace controllers
{

const unsigned short Controller::TRANSITION_ALPHA_INTERVAL = 51;
const unsigned short Controller::TRANSITION_MILLISECONDS_INTERVAL = 25;
const unsigned short Controller::TRANSITION_TIME_MAX = 5;

/**
 *
 */
Controller::Controller(utils::Context& context)
{
    nextControllerId = 0;
    expectedControllerId = 0;
    transitionTime = 5;

    openScreen = true;

    /* the screen transition color is continually modified
       when screens are switched, that's why we copy the
       default color from the black color */
    transitionSurfaceColor = memoris::colors::ColorsManager::get().getColorBlackCopy();

    transitionSurface.setSize(
        sf::Vector2f(
            window::WIDTH,
            window::HEIGHT
        )
    );

    transitionSurface.setPosition(0, 0);

    transitionSurface.setFillColor(transitionSurfaceColor);
}

/**
 * NOTE: empty destructor necessary for virtual
 * methods used in children of Controller type
 */
Controller::~Controller()
{
}

/**
 *
 */
unsigned short Controller::animateScreenTransition(utils::Context& context)
{
    if (!expectedControllerId && !openScreen)
    {
        return 0;
    }

    transitionSurfaceColor.a = static_cast<sf::Uint8>(
                                   transitionTime * TRANSITION_ALPHA_INTERVAL
                               );
    transitionSurface.setFillColor(transitionSurfaceColor);

    context.getSfmlWindow().draw(transitionSurface);

    if (
        screenTransitionClock.getElapsedTime().asMilliseconds() >
        TRANSITION_MILLISECONDS_INTERVAL
    )
    {
        screenTransitionClock.restart();

        if (openScreen)
        {
            transitionTime--;
        }
        else
        {
            transitionTime++;
        }
    }

    if (transitionTime > TRANSITION_TIME_MAX)
    {
        return expectedControllerId;
    }

    if (transitionTime <= 0)
    {
        openScreen = false;
    }

    return 0;
}

}
}
