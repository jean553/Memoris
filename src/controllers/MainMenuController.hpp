/**
 * Main menu controller.
 *
 * @file MainMenuController.hpp
 * @brief main menu of the program
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_MAIN_MENU_CONTROLLER
#define DEF_MAIN_MENU_CONTROLLER

#include <SFML/Graphics.hpp>

namespace controllers 
{
    class MainMenuController
    {
        public:

            MainMenuController();
            ~MainMenuController();

            /**
             * TODO: must be an abstract method
             * inside a parent class 'Screen'
             *
             * @brief render the main menu
             *
             * @param RenderWindow window   render window
             */
            void render(sf::RenderWindow* window);
    };
}

#endif
