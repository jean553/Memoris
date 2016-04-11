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
 * @file OpenLevelController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenLevelController.hpp"
#include "ControllerFactory.hpp"
#include "DirReader.hpp"
#include "Screens.hpp"

using namespace controllers;

const std::string OpenLevelController::STRING_OPEN_LEVEL_TITLE = "Open level";

const unsigned short OpenLevelController::LEVELS_LIST_WIDTH = 1580;
const unsigned short OpenLevelController::LEVELS_LIST_POSITION_X = 10;
const unsigned short OpenLevelController::LEVELS_LIST_POSITION_Y = 130;
const unsigned short OpenLevelController::LEVELS_LIST_LEVELS_NUMBER = 18;

/**
 *
 */
OpenLevelController::OpenLevelController() : Controller()
{
    titleBar.setDisplayedText(
        STRING_OPEN_LEVEL_TITLE
    );

    levelsList.setLayout(
        LEVELS_LIST_POSITION_X,
        LEVELS_LIST_POSITION_Y,
        LEVELS_LIST_WIDTH,
        LEVELS_LIST_LEVELS_NUMBER
    );

    levelsList.setStringsList(
        utils::DirReader::getAllFiles(
            "data/levels",
            ".level"
        )
    );
}

/**
 *
 */
unsigned short OpenLevelController::render(utils::Context* pContext)
{
    titleBar.display(pContext);
    levelsList.display(pContext);
    cursor.display(pContext);

    while(pContext->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                changeNextControllerId(pContext);
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                if (levelsList.isMouseHover()) {
                    pContext->setMessage(levelsList.getSelectedItemValue());
                    changeNextControllerId(pContext);
                }
                levelsList.scroll();
            }
            }
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void OpenLevelController::changeNextControllerId(utils::Context* pContext)
{
    nextControllerId = pContext->getPreviousControllerName() == constants::Screens::SERIE_EDITOR_SCREEN_NAME ?
                       factories::ControllerFactory::EDITOR_SERIE_CONTROLLER_ID :
                       factories::ControllerFactory::EDITOR_LEVEL_CONTROLLER_ID;
}
