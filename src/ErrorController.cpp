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

#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace controllers
{

/**
 *
 */
ErrorController::ErrorController(const utils::Context& context) :
    Controller(context)
{
}

/**
 *
 */
const unsigned short& ErrorController::render(const utils::Context& context) &
{
    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
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
                break;
            }
            }
        }
        default:
        {
            break;
        }
        }
    }

    return nextControllerId;
}

}
}
