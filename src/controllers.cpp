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
 * @file controllers.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "controllers.hpp"

#include "MainMenuController.hpp"
#include "NewGameController.hpp"
#include "EditorMenuController.hpp"
#include "EditorSerieController.hpp"
#include "OpenSerieController.hpp"
#include "EditorLevelController.hpp"
#include "OpenLevelController.hpp"
#include "SerieMainMenuController.hpp"
#include "OfficialSeriesSelectorController.hpp"
#include "GameController.hpp"

#include "Context.hpp"
#include "ErrorController.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
std::unique_ptr<Controller> getControllerById(const unsigned short& id)
{
    /* create an unique pointer in order to store the future generated
       controller pointer; initialize it with a null pointer; the type of the
       pointer is Controller, in order to store any type of controller */
    std::unique_ptr<Controller> controller(nullptr);

    /* NOTE: the returned variable is an unique pointer, that's why we have
       to create the pointed object with reset() */

    /* return a pointer to the correct controller according to the id */
    switch(id)
    {
    case NEW_GAME_CONTROLLER_ID:
    {
        controller.reset(new NewGameController());
    }
    break;
    case EDITOR_MENU_CONTROLLER_ID:
    {
        controller.reset(new EditorMenuController());
    }
    break;
    case EDITOR_SERIE_CONTROLLER_ID:
    {
        controller.reset(new EditorSerieController());
    }
    break;
    case OPEN_SERIE_CONTROLLER_ID:
    {
        controller.reset(new OpenSerieController());
    }
    break;
    case EDITOR_LEVEL_CONTROLLER_ID:
    {
        controller.reset(new EditorLevelController());
    }
    break;
    case OPEN_LEVEL_CONTROLLER_ID:
    {
        controller.reset(new OpenLevelController());
    }
    break;
    case SERIE_MAIN_MENU_CONTROLLER_ID:
    {
        controller.reset(new SerieMainMenuController());
    }
    break;
    case OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID:
    {
        controller.reset(new OfficialSeriesSelectorController());
    }
    break;
    case GAME_CONTROLLER_ID:
    {
        /* the game controller constructor tries to open the level file;
           the process to open the file is handled by the FileWriter; if the
           read process fails, an exception is thrown and the error controller
           with a specific message for this case is rendered instead; the
           error message is also set in the FileWriter class */
        try
        {
            controller.reset(new GameController());
        }
        catch(const std::invalid_argument& e)
        {
            controller.reset(new ErrorController(e.what()));
        }
    }
    break;

    /* by default, if the controller id does not exist, the main
       menu is rendered; it avoids mistakes in screens transitions;
       NOTE: the musics factory also returns the main menu music
       if an incorrect controller id is specified */
    default:
    {
        controller.reset(new MainMenuController());
    }
    break;
    }

    return controller;
}

}
}
