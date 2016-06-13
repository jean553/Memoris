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

namespace memoris
{
namespace controllers
{

/**
 *
 */
Controller* getControllerById(
    const unsigned short& id,
    utils::Context& context
)
{
    /* return a pointer to the correct controller according to the id */
    switch(id)
    {
    case NEW_GAME_CONTROLLER_ID:
    {
        return new NewGameController;
    }
    break;
    case EDITOR_MENU_CONTROLLER_ID:
    {
        return new EditorMenuController;
    }
    break;
    case EDITOR_SERIE_CONTROLLER_ID:
    {
        return new EditorSerieController(context);
    }
    break;
    case OPEN_SERIE_CONTROLLER_ID:
    {
        return new OpenSerieController;
    }
    break;
    case EDITOR_LEVEL_CONTROLLER_ID:
    {
        return new EditorLevelController;
    }
    break;
    case OPEN_LEVEL_CONTROLLER_ID:
    {
        return new OpenLevelController;
    }
    break;
    case SERIE_MAIN_MENU_CONTROLLER_ID:
    {
        return new SerieMainMenuController;
    }
    break;
    case OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID:
    {
        return new OfficialSeriesSelectorController;
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
            return new GameController(context.getNxtLvlStrPath());
        }
        catch(const std::invalid_argument& e)
        {
            return getErrCtrl(e.what());
        }
    }
    break;

    /* by default, if the controller id does not exist, the main
       menu is rendered; it avoids mistakes in screens transitions;
       NOTE: the musics factory also returns the main menu music
       if an incorrect controller id is specified */
    default:
    {
        return new MainMenuController;
    }
    break;
    }
}

/**
 *
 */
ErrController* getErrCtrl(const std::string& msg)
{
    return new ErrController(msg);
}

}
}
