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
 * Factory which generates the screens.
 *
 * @file ControllerFactory.hpp
 * @brief factory to generate the game screens controllers
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN_FACTORY
#define DEF_SCREEN_FACTORY

#include "Controller.hpp"
#include "Context.hpp"
#include "ErrController.hpp"

namespace factories
{
class ControllerFactory
{

public:

    static constexpr unsigned short EXIT = 1;
    static constexpr unsigned short MAIN_MENU_CONTROLLER_ID = 2;
    static constexpr unsigned short NEW_GAME_CONTROLLER_ID = 3;
    static constexpr unsigned short EDITOR_MENU_CONTROLLER_ID = 4;
    static constexpr unsigned short EDITOR_SERIE_CONTROLLER_ID = 5;
    static constexpr unsigned short OPEN_SERIE_CONTROLLER_ID = 6;
    static constexpr unsigned short EDITOR_LEVEL_CONTROLLER_ID = 7;
    static constexpr unsigned short OPEN_LEVEL_CONTROLLER_ID = 8;
    static constexpr unsigned short GAME_CONTROLLER_ID = 9;
    static constexpr unsigned short SERIE_MAIN_MENU_CONTROLLER_ID = 10;
    static constexpr unsigned short OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID = 11;

    /**
     * @brief returns a new controller
     * pointer according to the given
     * screen id, used for screens
     * generation and screens switching.
     *
     * @param id      screen id
     * @param context current context
     *
     * @return screen controller pointer,
     * returns null if no screen match
     */
    static controllers::Controller* getControllerById(
        unsigned short id,
        utils::Context& context
    );

private:

    /**
     * @brief returns a pointer to error controller
     *
     * @param msg error message to display in the error controller
     *
     * @return controllers::ErrController*
     */
    static controllers::ErrController* getErrCtrl(const std::string& msg);
};
}

#endif
