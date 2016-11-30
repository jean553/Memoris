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
 * @brief factory to generate the game screens controllers
 * @file controllers.hpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTROLLERS_H_
#define MEMORIS_CONTROLLERS_H_

#include "Controller.hpp"

#include "ErrorController.hpp"
#include "Context.hpp"

#include <SFML/System/String.hpp>

namespace memoris
{
namespace controllers
{

/* all the controllers ids */

/* TODO: #875 no need to store integers here, try to use an enumeration ? */
constexpr unsigned short EXIT {1};
constexpr unsigned short MAIN_MENU_CONTROLLER_ID {2};
constexpr unsigned short NEW_GAME_CONTROLLER_ID {3};
constexpr unsigned short GAME_CONTROLLER_ID {4};
constexpr unsigned short SERIE_MAIN_MENU_CONTROLLER_ID {5};
constexpr unsigned short OFFICIAL_SERIES_MENU_CONTROLLER_ID {6};
constexpr unsigned short EDITOR_MENU_CONTROLLER_ID {8};
constexpr unsigned short LEVEL_EDITOR_CONTROLLER_ID {9};
constexpr unsigned short OPEN_LEVEL_CONTROLLER_ID {10};
constexpr unsigned short OPEN_GAME_CONTROLLER_ID {11};
constexpr unsigned short SERIE_EDITOR_CONTROLLER_ID {12};

/* TODO: #894 delete this id when each error controller has his own message */
constexpr unsigned short ERROR_CONTROLLER_ID {7};
constexpr unsigned short UNLOCKED_SERIE_ERROR_CONTROLLER_ID {13};

constexpr unsigned short WIN_SERIE_CONTROLLER_ID {14};
constexpr unsigned short REMOVE_GAME_CONTROLLER_ID {15};

/**
 * @brief factory method to create controllers by id, each controller is linked
 * to an unique id; this method returns a pointer to a Controller child object
 *
 * @param context reference to the current context
 * @param id the id of the controller
 *
 * @return std::unique_ptr<Controller>
 */
std::unique_ptr<Controller> getControllerById(
    const utils::Context& context,
    const unsigned short& id
);

/**
 * @brief refactored function to get a unique pointer to a error controller;
 * this controller is needed in different cases, that's why it is refactored
 * here
 *
 * @param context constant reference to the current context to use
 * @param message constant reference to the SFML string to display
 *
 * @return std::unique_ptr<ErrorController>
 */
std::unique_ptr<ErrorController> getErrorController(
    const utils::Context& context,
    const sf::String& message
);

/**
 * @brief returns the full path of a level file, including the file extension
 *
 * @param levelName constant reference to the level name
 *
 * @return const std::string&
 *
 * returns by copy because directly returns the calculated result
 */
const std::string getLevelFilePath(const std::string& levelName);

}
}

#endif
