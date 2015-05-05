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
#define SIZE_ITEM_FONT 60

#define PATH_FONT_TITLE "res/fonts/crystal_regular.ttf"
#define PATH_FONT_ITEM "res/fonts/hi.otf"
#define PATH_MUSIC_MAIN_MENU "res/musics/dj-xtrm-killer-symphonyX-outro.ogg"
#define PATH_IMAGE_GITHUB "res/images/fork-me.png"

#define COLOR_ALPHA 255

#define COLOR_TITLE_RED_INIT 0
#define COLOR_TITLE_GREEN_INIT 0
#define COLOR_TITLE_BLUE_INIT 255
#define COLOR_TITLE_RED_MAX 255
#define COLOR_TITLE_GREEN_MAX 180
#define COLOR_TITLE_BLUE_MAX 255
#define COLOR_TITLE_ALL_MIN 0
#define COLOR_WHITE_RED 255
#define COLOR_WHITE_GREEN 255
#define COLOR_WHITE_BLUE 255
#define COLOR_RED_RED 255
#define COLOR_RED_GREEN 0
#define COLOR_RED_BLUE 0

#define POSITION_TITLE_X 480
#define POSITION_TITLE_Y 100
#define POSITION_GITHUB_X 1300
#define POSITION_GITHUB_Y 0
#define POSITION_ITEM_NEW_GAME_X 615
#define POSITION_ITEM_NEW_GAME_Y 300
#define POSITION_ITEM_LOAD_GAME_X 605
#define POSITION_ITEM_LOAD_GAME_Y 400
#define POSITION_ITEM_EDITOR_X 685
#define POSITION_ITEM_EDITOR_Y 500
#define POSITION_ITEM_OPTIONS_X 660
#define POSITION_ITEM_OPTIONS_Y 600
#define POSITION_ITEM_EXIT_X 725
#define POSITION_ITEM_EXIT_Y 700

#define DIRECTION_TITLE_RED_INIT 1
#define DIRECTION_TITLE_GREEN_INIT 1
#define DIRECTION_TITLE_BLUE_INIT -1

#define INTERVAL_ANIMATION_TITLE 10

#define STRING_TITLE "Memoris"
#define STRING_NEW_GAME "New game"
#define STRING_LOAD_GAME "Load game"
#define STRING_EDITOR "Editor"
#define STRING_OPTIONS "Options"
#define STRING_EXIT "Exit"

#define MENU_SELECTOR_MIN 0
#define MENU_SELECTOR_MAX 4

#define SOUND_SELECTOR_MOVE "res/sounds/001.wav"

#define MENU_ITEM_NEW_GAME 0
#define MENU_ITEM_LOAD_GAME 1
#define MENU_ITEM_EDITOR 2
#define MENU_ITEM_OPTIONS 3
#define MENU_ITEM_EXIT 4

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
            sf::Font fontItem;

            sf::Color colorTitle;
            sf::Color colorWhite;
            sf::Color colorRed;

            sf::Text title;
            sf::Text itemNewGame;
            sf::Text itemLoadGame;
            sf::Text itemEditor;
            sf::Text itemOptions;
            sf::Text itemExit;

            sf::Texture textureGithub;

            sf::Sprite spriteGithub;

            sf::Music musicMainMenu;

            sf::Clock clock;

            sf::SoundBuffer soundBuffer;

            sf::Sound soundSelectorMove;

            char titleRedDirection;
            char titleGreenDirection;
            char titleBlueDirection;

            unsigned char selectorPosition;

            /**
             * @brief update the color of the title
             */
            void animateTitleColor();

            /**
             * @brief visually update the selector position
             */
            void updateSelectorPosition();

            /**
             * @brief call action for one selected menu item
             *
             * @param RenderWindow window main window
             */
            void selectMenuItem(sf::RenderWindow* window);
    };
}

#endif
