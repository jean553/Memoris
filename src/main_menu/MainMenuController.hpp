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

#define SIZE_TITLE_FONT 140

#define PATH_FONT_TITLE "res/fonts/crystal_regular.ttf"
#define PATH_MUSIC_MAIN_MENU "res/musics/dj-xtrm-killer-symphonyX-outro.ogg"
#define PATH_IMAGE_GITHUB "res/images/fork-me.png"

#define COLOR_TITLE_RED_INIT 0
#define COLOR_TITLE_GREEN_INIT 0
#define COLOR_TITLE_BLUE_INIT 255
#define COLOR_TITLE_RED_MAX 255
#define COLOR_TITLE_GREEN_MAX 180
#define COLOR_TITLE_BLUE_MAX 255
#define COLOR_TITLE_ALL_MIN 0
#define COLOR_TITLE_ALPHA 255

#define POSITION_TITLE_X 480
#define POSITION_TITLE_Y 100
#define POSITION_GITHUB_X 1300
#define POSITION_GITHUB_Y 0

#define DIRECTION_TITLE_RED_INIT 1
#define DIRECTION_TITLE_GREEN_INIT 1
#define DIRECTION_TITLE_BLUE_INIT -1

#define INTERVAL_ANIMATION_TITLE 10

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

            sf::Color colorTitle;

            sf::Text title;

            sf::Texture textureGithub;

            sf::Sprite spriteGithub;

            sf::Music musicMainMenu;

            sf::Clock clock;

            char titleRedDirection;
            char titleGreenDirection;
            char titleBlueDirection;

            /**
             * @brief update the color of the title
             */
            void animateTitleColor();
    };
}

#endif
