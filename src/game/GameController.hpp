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
 * Main controller of the game.
 * Contains the main loop and
 * manage the different screens.
 *
 * @file GameController.hpp
 * @brief main program class, contains the game loop
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_GAME_CONTROLLER
#define DEF_GAME_CONTROLLER

#include <SFML/Graphics.hpp>

#include "../utils/ScreenFactory.hpp"
#include "../utils/MusicFactory.hpp"
#include "../utils/Controller.hpp"
#include "../utils/Context.hpp"

namespace controllers
{
    class GameController
    {
        public:

            GameController();
            ~GameController();

            /**
             * @brief run the game, contains
             * the main loop of the program
             *
             * @param RenderWindow window   main window
             */
            void run(sf::RenderWindow* window);

        private:

            controllers::Controller *currentController;

            factories::ScreenFactory *screenFactory;
            factories::MusicFactory *musicFactory;

            utils::Context *context;

            unsigned char currentControllerId;
            unsigned char nextControllerId;

            std::string currentMusicPath;
            std::string nextMusicPath;
    };
}

#endif
