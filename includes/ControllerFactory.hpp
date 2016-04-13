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

namespace factories
{
class ControllerFactory
{

public:

    static const unsigned short EXIT;
    static const unsigned short MAIN_MENU_CONTROLLER_ID;
    static const unsigned short NEW_GAME_CONTROLLER_ID;
    static const unsigned short EDITOR_MENU_CONTROLLER_ID;
    static const unsigned short EDITOR_SERIE_CONTROLLER_ID;
    static const unsigned short OPEN_SERIE_CONTROLLER_ID;
    static const unsigned short EDITOR_LEVEL_CONTROLLER_ID;
    static const unsigned short OPEN_LEVEL_CONTROLLER_ID;

    /**
     * @brief returns a new controller
     * pointer according to the given
     * screen id, used for screens
     * generation and screens switching.
     *
     * @param id      screen id
     * @param pContext current context
     *
     * @return screen controller pointer,
     * returns null if no screen match
     */
    static controllers::Controller* getControllerById(
        unsigned short id,
        utils::Context* pContext
    );
};
}

#endif
