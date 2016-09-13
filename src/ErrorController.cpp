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
 * @file ErrorController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ErrorController.hpp"

#include "controllers.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
ErrorController::ErrorController(
    utils::Context& context
) :
    Controller(context)
{
    /* does nothing, only used to pass parameters to the parent class */
}

/**
 *
 */
unsigned short ErrorController::render(
    utils::Context& context
)
{
    /* used for screen switch animation */
    nextControllerId = animateScreenTransition(context);

    /* main loop event of the error controller */
    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        /* a key is pressed down */
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            /* the escape key has been pressed down */
            case sf::Keyboard::Escape:
            {
                /* TODO: #532 return to the official series menu screen for
                   now, the error controller is only accessible from this
                   screen when a level is not found; should go back to the
                   previous controller */
                expectedControllerId = OFFICIAL_SERIES_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
                /* useless, only added here in order to have a correct
                   syntax */
                break;
            }
            }
        }
        default:
        {
            /* useless, only added here in order to have a correct syntax */
            break;
        }
        }
    }

    return nextControllerId;
}

}
}
