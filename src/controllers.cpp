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
#include "SerieMainMenuController.hpp"
#include "OfficialSeriesMenuController.hpp"
#include "GameController.hpp"
#include "EditorMenuController.hpp"

#include "Level.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
std::unique_ptr<Controller> getControllerById(
    const std::shared_ptr<utils::Context>& context,
    const unsigned short& id
)
{
    /* return a unique pointer to the correct controller according to the id */
    switch(id)
    {
    case NEW_GAME_CONTROLLER_ID:
    {
        return std::make_unique<NewGameController>(context);
    }
    case SERIE_MAIN_MENU_CONTROLLER_ID:
    {
        return std::make_unique<SerieMainMenuController>(context);
    }
    case OFFICIAL_SERIES_MENU_CONTROLLER_ID:
    {
        return std::make_unique<OfficialSeriesMenuController>(context);
    }
    case GAME_CONTROLLER_ID:
    {
        try
        {
            /* creates a level object using the next level file path; this path
               is located inside the context object; this part of the code
               throw an exception if an error occures during the file reading
               process; we use auto, the generates type is
               std::shared_ptr<entities::Level>; create this pointer here
               instead of directly creating it inside the game controller makes
               the code easier to maintain; the level pointer is used in the
               game controller and also in the LevelAnimation object */
            auto level = std::make_shared<entities::Level>(context);

            /* creates the game controller and pass the level pointer to it */
            return std::make_unique<GameController>(
                       context,
                       level
                   );

            /* catch the invalid argument exception if the game cannot start;
               we get it as a reference to make the program runs faster */
        }
        catch(std::invalid_argument&)
        {
            /* render the error controller instead of the game controller */
            return getErrorController(context);
        }
    }
    case ERROR_CONTROLLER_ID:
    {
        return getErrorController(context);
    }
    case EDITOR_MENU_CONTROLLER_ID:
    {
        return std::make_unique<EditorMenuController>(context);
    }
    }

    /* by default, if the controller id does not exist, the main
       menu is rendered; it avoids mistakes in screens transitions;
       NOTE: the musics factory also returns the main menu music
       if an incorrect controller id is specified */
    return std::make_unique<MainMenuController>(context);
}

/**
 *
 */
std::unique_ptr<ErrorController> getErrorController(
    const std::shared_ptr<utils::Context>& context
)
{
    return std::make_unique<ErrorController>(context);
}

}
}
