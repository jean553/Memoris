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

/**
 *
 */
Controller::Controller()
{
    /* when the controller starts, there is no new controller to load at
       the moment, that's why the next controller id is initialized with 0 */
    nextControllerId = 0;

    /* when the controller starts, there is no ask for a new controller to
       start and no controller switch animation; that's why the expected
       controller id is initialized with 0 */
    expectedControllerId = 0;

    /* when a new controller starts, there is an opening animation; for every
       controller, the boolean to indicate that there is an opening animation
       is set to true by default; it becomes false at the end of the opening
       animation */
    openingScreen = true;

    /* the default last screen transition time is initialized to 0 */
    lastScreenTransitionTime = 0;

    /* when a new screen opens, it appears in an animation after a short time;
       the screen is totally black when the screen is opened; the alpha
       value of the screen transition surface is equal to 255 (5 * 51) */
    transitionTime = 5;

    /* the screen transition color is continually modified
       when screens are switched, that's why we copy the
       default color from the black color */
    transitionSurfaceColor =
        memoris::colors::ColorsManager::get().getColorBlackCopy();

    /* the size of the screen transition surface is equal to the window
       dimension; in fact, the screen transition surface covers the whole
       screen */
    transitionSurface.setSize(
        sf::Vector2f(
            window::WIDTH,
            window::HEIGHT
        )
    );

    /* initialize the screen transition surface with a default color, this
       color will change all the time during the animation */
    transitionSurface.setFillColor(transitionSurfaceColor);
}

/**
 *
 */
Controller::~Controller()
{
    /* virtual destructor that we have to declare in order to ensure that
       the children constructors are called correctly when a child object
       is pointed by a parent pointer and the pointed object is deleted */
}

/**
 *
 */
unsigned short Controller::animateScreenTransition()
{
    /* the animation is rendered only if a new screen is called ( the program
       is closing the current screen ) or if the new called screen is
       opening */
    if (!expectedControllerId && !openingScreen)
    {
        return 0;
    }

    /* update the transparency amount of the transition surface according
       to the current animation duration; no need for casting here: sf::Uint8
       is an unsigned char type on SFML side; the operation here is between
       two values of the same type */
    transitionSurfaceColor.a = transitionTime * 51;

    /* update the whole animation color ( with the new transparency value ) */
    transitionSurface.setFillColor(transitionSurfaceColor);

    /* draw the transition surface */
    utils::Context::get().getSfmlWindow().draw(transitionSurface);

    /* animate the screen transition animation according to the last screen
       transition animation update time */
    if (
        utils::Context::get().getClockMillisecondsTime() -
        lastScreenTransitionTime > 25
    )
    {
        if (openingScreen)
        {
            transitionTime--;
        }
        else
        {
            transitionTime++;
        }

        /* update the last screen transition time with the current time for
           the next animation step */
        lastScreenTransitionTime =
            utils::Context::get().getClockMillisecondsTime();
    }

    /* when the closing animation is finished, the color transparency value is
       equal to 255 ( 5 * 51 ). The expected controller id is returned and
       the new controller can be rendered */
    if (transitionTime > 5)
    {
        return expectedControllerId;
    }

    /* when the opening animation is finished, the color transparency value is
       equal to 0; the opening animation boolean is set to false; the
       new controller is still rendered but without any animation */
    if (transitionTime <= 0)
    {
        openingScreen = false;
    }

    /* if the screen is opening or closing, as long as the animation is not
       finished, the function does not indicate that the controllers can be
       really switched and just return 0 */
    return 0;
}

}
}
