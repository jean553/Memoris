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
 * @file ControllerFactory.hpp
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ControllerFactory.hpp"
#include "MainMenuController.hpp"
#include "NewGameController.hpp"
#include "EditorMenuController.hpp"
#include "EditorSerieController.hpp"
#include "OpenSerieController.hpp"
#include "EditorLevelController.hpp"
#include "OpenLevelController.hpp"
#include "GameController.hpp"
#include "SerieMainMenuController.hpp"
#include "Messages.hpp"

using namespace factories;

const unsigned short ControllerFactory::EXIT = 1;
const unsigned short ControllerFactory::MAIN_MENU_CONTROLLER_ID = 2;
const unsigned short ControllerFactory::NEW_GAME_CONTROLLER_ID = 3;
const unsigned short ControllerFactory::EDITOR_MENU_CONTROLLER_ID = 4;
const unsigned short ControllerFactory::EDITOR_SERIE_CONTROLLER_ID = 5;
const unsigned short ControllerFactory::OPEN_SERIE_CONTROLLER_ID = 6;
const unsigned short ControllerFactory::EDITOR_LEVEL_CONTROLLER_ID = 7;
const unsigned short ControllerFactory::OPEN_LEVEL_CONTROLLER_ID = 8;
const unsigned short ControllerFactory::GAME_CONTROLLER_ID = 9;

const uint8_t ControllerFactory::SERIE_MAIN_MENU_CONTROLLER_ID = 10;

/**
 *
 */
controllers::Controller* ControllerFactory::getControllerById(
    unsigned short id,
    utils::Context* pContext
)
{
    switch(id)
    {
    case MAIN_MENU_CONTROLLER_ID:
        return new controllers::MainMenuController;
    case NEW_GAME_CONTROLLER_ID:
        return new controllers::NewGameController;
    case EDITOR_MENU_CONTROLLER_ID:
        return new controllers::EditorMenuController;
    case EDITOR_SERIE_CONTROLLER_ID:
        return new controllers::EditorSerieController(pContext);
    case OPEN_SERIE_CONTROLLER_ID:
        return new controllers::OpenSerieController;
    case EDITOR_LEVEL_CONTROLLER_ID:
        return new controllers::EditorLevelController;
    case OPEN_LEVEL_CONTROLLER_ID:
        return new controllers::OpenLevelController;
    case GAME_CONTROLLER_ID:
        return new controllers::GameController;
    case SERIE_MAIN_MENU_CONTROLLER_ID:
        return new controllers::SerieMainMenuController;
    default:
        return NULL;
    }
}
