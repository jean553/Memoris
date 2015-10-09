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
 * @file OpenSerieController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenSerieController.hpp"

using namespace controllers;

const std::string OpenSerieController::STRING_OPEN_SERIE_TITLE = "Open serie";

/**
 *
 */
OpenSerieController::OpenSerieController() : Controller()
{
    titleBar.setDisplayedText(
        STRING_OPEN_SERIE_TITLE
    );
}

/**
 *
 */
unsigned char OpenSerieController::render(utils::Context* context)
{
    titleBar.display(context);

    while(context->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Escape: {
                        nextControllerId = factories::ScreenFactory::EDITOR_SERIE_CONTROLLER_ID;                        
                    }
                }
            }
        }
    }

    return nextControllerId;
}
