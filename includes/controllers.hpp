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

namespace memoris
{
namespace controllers
{

/* all the controllers ids */
constexpr unsigned short EXIT = 1;
constexpr unsigned short MAIN_MENU_CONTROLLER_ID = 2;
constexpr unsigned short NEW_GAME_CONTROLLER_ID = 3;
constexpr unsigned short EDITOR_MENU_CONTROLLER_ID = 4;
constexpr unsigned short EDITOR_SERIE_CONTROLLER_ID = 5;
constexpr unsigned short OPEN_SERIE_CONTROLLER_ID = 6;
constexpr unsigned short EDITOR_LEVEL_CONTROLLER_ID = 7;
constexpr unsigned short OPEN_LEVEL_CONTROLLER_ID = 8;
constexpr unsigned short GAME_CONTROLLER_ID = 9;
constexpr unsigned short SERIE_MAIN_MENU_CONTROLLER_ID = 10;
constexpr unsigned short OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID = 11;

/**
 * @brief factory method to create controllers by id, each controller is linked
 * to an unique id; this method returns a pointer to a Controller child object
 *
 * @param id the id of the controller
 *
 * @return std::unique_ptr<Controller>
 */
std::unique_ptr<Controller> getControllerById(const unsigned short& id);

}
}

#endif
