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

const float_t ErrorController::ERR_HRTL_PSTN = 10.f;
const float_t ErrorController::ERR_VRTL_PSTN = 10.f;

/**
 *
 */
ErrorController::ErrorController(
    utils::Context& context,
    const std::string& msg
) : Controller(context)
{
    error.setFont(context.getFontsManager().getTextFont());
    error.setString(msg);
    error.setCharacterSize(memoris::fonts::TEXT_SIZE);
    error.setColor(context.getColorsManager().getColorRed());
    error.setPosition(
        ERR_HRTL_PSTN,
        ERR_VRTL_PSTN
    );

    errMsg = msg;
}

/**
 *
 */
uint8_t ErrorController::render(utils::Context& context)
{
    nextControllerId = animateScreenTransition(context);

    context.getSfmlWindow().draw(error);

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
                /* TODO: return to the official series menu screen for now,
                 * as this error screen can obly be displayed from this first screen */
                expectedControllerId =
                    OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID;

                break;
            }
            }
        }
        }
    }

    return nextControllerId;
}

}
}
