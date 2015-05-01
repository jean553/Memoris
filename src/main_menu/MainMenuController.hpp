/**
 * Main menu screen.
 *
 * @file MainMenuController.hpp
 * @brief main menu of the program
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_MAIN_MENU_CONTROLLER
#define DEF_MAIN_MENU_CONTROLLER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../utils/Controller.hpp"

#define TITLE_FONT_SIZE 80
#define PATH_FONT_TITLE "res/fonts/designer_block.ttf"
#define PATH_MUSIC_MAIN_MENU "res/musics/dj-xtrm-killer-symphonyX-outro.ogg"

namespace controllers
{
    class MainMenuController : public Controller
    {
        public:

            MainMenuController();
            ~MainMenuController();

            /**
             * @brief render the main menu
             *
             * @param RenderWindow window   render window
             */
            void render(sf::RenderWindow* window);

        private:

            sf::Font fontTitle;

            sf::Text title;

            sf::Music musicMainMenu;
    };
}

#endif
