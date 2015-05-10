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
 * @file ScreenFactory.hpp
 * @brief factory to generate the game screens
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN_FACTORY
#define DEF_SCREEN_FACTORY

#include "Controller.hpp"
#include "ScreensIdentifiers.hpp"

#include "../main_menu/MainMenuController.hpp"
#include "../new_game/NewGameController.hpp"

namespace factories
{
    class ScreenFactory
    {
        public:

            ScreenFactory();
            ~ScreenFactory();

            /**
             * @brief returns a new controller
             * pointer according to the given
             * screen id, used for screens
             * generation and screens switching.
             *
             * @param char id   id of the screen
             *
             * @return screen controller pointer,
             * returns null if no screen match
             */
            controllers::Controller* getScreenById(unsigned char id);
    };
}

#endif
