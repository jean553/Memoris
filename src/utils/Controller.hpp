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
 * @file Controller.hpp
 * @brief parent class for all controllers
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN
#define DEF_SCREEN

#include <SFML/Graphics.hpp>

namespace controllers
{
    class Controller
    {
        public:

            Controller();
            ~Controller();

            /**
             * @brief render the screen, contains events catcher,
             *
             * @param RenderWindow window   the game main window
             */
            virtual void render(sf::RenderWindow* window) = 0;

        protected:

            sf::Event event;
    };
}

#endif
