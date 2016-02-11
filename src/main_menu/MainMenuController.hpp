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

namespace controllers {
class MainMenuController : public Controller {

    static const std::string PATH_IMAGE_GITHUB;
    static const std::string STRING_TITLE;
    static const std::string STRING_NEW_GAME;
    static const std::string STRING_LOAD_GAME;
    static const std::string STRING_EDITOR;
    static const std::string STRING_OPTIONS;
    static const std::string STRING_EXIT;

    static const unsigned short COLOR_TITLE_RED_INIT = 0;
    static const unsigned short COLOR_TITLE_GREEN_INIT = 0;
    static const unsigned short COLOR_TITLE_BLUE_INIT = 255;
    static const unsigned short COLOR_TITLE_RED_MAX = 255;
    static const unsigned short COLOR_TITLE_GREEN_MAX = 180;
    static const unsigned short COLOR_TITLE_BLUE_MAX = 255;
    static const unsigned short COLOR_TITLE_ALL_MIN = 0;
    static const unsigned short POSITION_TITLE_X = 480;
    static const unsigned short POSITION_TITLE_Y = 100;
    static const unsigned short POSITION_GITHUB_X = 1300;
    static const unsigned short POSITION_GITHUB_Y = 0;
    static const unsigned short POSITION_ITEM_NEW_GAME_X = 615;
    static const unsigned short POSITION_ITEM_NEW_GAME_Y = 300;
    static const unsigned short POSITION_ITEM_LOAD_GAME_X = 605;
    static const unsigned short POSITION_ITEM_LOAD_GAME_Y = 400;
    static const unsigned short POSITION_ITEM_EDITOR_X = 685;
    static const unsigned short POSITION_ITEM_EDITOR_Y = 500;
    static const unsigned short POSITION_ITEM_OPTIONS_X = 660;
    static const unsigned short POSITION_ITEM_OPTIONS_Y = 600;
    static const unsigned short POSITION_ITEM_EXIT_X = 725;
    static const unsigned short POSITION_ITEM_EXIT_Y = 700;
    static const unsigned short DIRECTION_TITLE_RED_INIT = 1;
    static const unsigned short DIRECTION_TITLE_GREEN_INIT = 1;
    static const unsigned short MAIN_MENU_SELECTOR_MIN = 0;
    static const unsigned short MAIN_MENU_SELECTOR_MAX = 4;
    static const unsigned short MAIN_MENU_ITEM_NEW_GAME = 0;
    static const unsigned short MAIN_MENU_ITEM_LOAD_GAME = 1;
    static const unsigned short MAIN_MENU_ITEM_EDITOR = 2;
    static const unsigned short MAIN_MENU_ITEM_OPTIONS = 3;
    static const unsigned short MAIN_MENU_ITEM_EXIT = 4;

    static const short DIRECTION_TITLE_BLUE_INIT = -1;

    static const int INTERVAL_ANIMATION_TITLE = 10;

public:

    MainMenuController();

    /**
     * @brief render the main menu
     *
     * @param pContext   commons items for controller
     *
     * @return short   id of the next screen controller
     */
    unsigned short render(
        utils::Context* pContext
    );

private:

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
     * @param window        main window
     */
    void selectMenuItem(sf::RenderWindow* window);

    unsigned short titleRedDirection;
    unsigned short titleGreenDirection;
    short titleBlueDirection;
    unsigned short selectorPosition;

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

    sf::Clock clock;

    sf::SoundBuffer soundBuffer;

    sf::Sound soundSelectorMove;
};
}

#endif
