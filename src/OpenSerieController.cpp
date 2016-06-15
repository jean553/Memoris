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
#include "DirReader.hpp"
#include "controllers.hpp"

namespace memoris
{
namespace controllers
{

const std::string OpenSerieController::STRING_OPEN_SERIE_TITLE = "Open serie";
const std::string OpenSerieController::OPEN_SERIE_BUTTON_EXIT = "Exit";

const unsigned short OpenSerieController::OPEN_SERIE_BUTTON_EXIT_POSITION_X = 1400;
const unsigned short OpenSerieController::OPEN_SERIE_BUTTON_EXIT_POSITION_Y = 10;
const unsigned short OpenSerieController::OPEN_SERIE_BUTTONS_WIDTH = 200;
const unsigned short OpenSerieController::SERIES_LIST_WIDTH = 1580;
const unsigned short OpenSerieController::SERIES_LIST_POSITION_X = 10;
const unsigned short OpenSerieController::SERIES_LIST_POSITION_Y = 130;
const unsigned short OpenSerieController::SERIES_LIST_SERIES_NUMBER = 18;

/**
 *
 */
OpenSerieController::OpenSerieController(utils::Context& context) :
    Controller(),
    titleBar(context)
{
    titleBar.setDisplayedText(
        STRING_OPEN_SERIE_TITLE
    );

    buttonExit.setLabel(OPEN_SERIE_BUTTON_EXIT);

    buttonExit.setLayout(
        context,
        OPEN_SERIE_BUTTON_EXIT_POSITION_X,
        OPEN_SERIE_BUTTON_EXIT_POSITION_Y,
        OPEN_SERIE_BUTTONS_WIDTH
    );

    seriesList.setLayout(
        SERIES_LIST_POSITION_X,
        SERIES_LIST_POSITION_Y,
        SERIES_LIST_WIDTH,
        SERIES_LIST_SERIES_NUMBER
    );

    seriesList.setStringsList(
        utils::DirReader::getAllFiles(
            "data/series",
            ".serie"
        )
    );
}

/**
 *
 */
uint8_t OpenSerieController::render(utils::Context& context)
{
    titleBar.display(context);
    buttonExit.display(context);
    seriesList.display(context);
    cursor.display(context);

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
                expectedControllerId =
                    EDITOR_SERIE_CONTROLLER_ID;
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                if(buttonExit.isMouseHover())
                {
                    expectedControllerId =
                        EDITOR_SERIE_CONTROLLER_ID;
                }

                seriesList.scroll();
            }
            }
        }
        }
    }

    return nextControllerId;
}

}
}
