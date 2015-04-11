/**
 * Main menu screen.
 *
 * @file MainMenuScreen.hpp
 * @brief main menu of the program
 * @package screens
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_MAIN_MENU_SCREEN
#define DEF_MAIN_MENU_SCREEN

#include <SFML/Graphics.hpp>

#include "Screen.hpp"

namespace screens
{
    class MainMenuScreen : public Screen
    {
        public:

            MainMenuScreen();
            ~MainMenuScreen();

            /**
             * @brief render the main menu
             *
             * @param RenderWindow window   render window
             */
            void render(sf::RenderWindow* window);
    };
}

#endif
