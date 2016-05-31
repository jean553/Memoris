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
 * @file ErrController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ErrController.hpp"
#include "ControllerFactory.hpp"

using namespace controllers;

const float_t ErrController::ERR_HRTL_PSTN = 10.f;
const float_t ErrController::ERR_VRTL_PSTN = 10.f;

/**
 *
 */
ErrController::ErrController(const std::string& msg) : Controller()
{
    font.loadFromFile(constants::Fonts::getTextFontPath());

    colorErr.r = constants::Colors::COLOR_RED_RED;
    colorErr.g = constants::Colors::COLOR_RED_GREEN;
    colorErr.b = constants::Colors::COLOR_RED_BLUE;
    colorErr.a = constants::Colors::COLOR_ALPHA_FULL;

    error.setFont(font);
    error.setString(msg);
    error.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    error.setColor(colorErr);
    error.setPosition(
        ERR_HRTL_PSTN,
        ERR_VRTL_PSTN
    );

    errMsg = msg;
}

/**
 *
 */
uint8_t ErrController::render(utils::Context* ctx)
{
    nextControllerId = animateScreenTransition(ctx);

    ctx->getWindow()->draw(error);

    while(ctx->getWindow()->pollEvent(event))
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
                    factories::ControllerFactory::OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID;

                break;
            }
            }
        }
        }
    }

    return nextControllerId;
}
