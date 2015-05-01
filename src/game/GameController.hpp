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
#include "../utils/Controller.hpp"

#define MAIN_MENU_CONTROLLER_ID 1

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
    };
}

#endif
