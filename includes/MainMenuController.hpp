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

#include "Controller.hpp"
#include "HasMenuSelectorAnimation.hpp"
#include "AnimatedBackground.hpp"
#include "MenuGradient.hpp"

namespace controllers
{
class MainMenuController : public Controller
{
    friend class policies::HasMenuSelectorAnimation;

    static const std::string PATH_IMAGE_GITHUB;

    static const std::string STRING_TITLE;
    static const std::string STRING_NEW_GAME;
    static const std::string STRING_LOAD_GAME;
    static const std::string STRING_EDITOR;
    static const std::string STRING_OPTIONS;
    static const std::string STRING_EXIT;

    static const unsigned short COLOR_TITLE_RED_INIT;
    static const unsigned short COLOR_TITLE_GREEN_INIT;
    static const unsigned short COLOR_TITLE_BLUE_INIT;

    static const unsigned short COLOR_TITLE_RED_MAX;
    static const unsigned short COLOR_TITLE_GREEN_MAX;
    static const unsigned short COLOR_TITLE_BLUE_MAX;

    static const unsigned short COLOR_TITLE_ALL_MIN;

    static const unsigned short POSITION_TITLE_X;
    static const unsigned short POSITION_TITLE_Y;

    static const unsigned short POSITION_GITHUB_X;
    static const unsigned short POSITION_GITHUB_Y;

    static const unsigned short POSITION_ITEM_NEW_GAME_X;
    static const unsigned short POSITION_ITEM_NEW_GAME_Y;

    static const unsigned short POSITION_ITEM_LOAD_GAME_X;
    static const unsigned short POSITION_ITEM_LOAD_GAME_Y;

    static const unsigned short POSITION_ITEM_EDITOR_X;
    static const unsigned short POSITION_ITEM_EDITOR_Y;

    static const unsigned short POSITION_ITEM_OPTIONS_X;
    static const unsigned short POSITION_ITEM_OPTIONS_Y;

    static const unsigned short POSITION_ITEM_EXIT_X;
    static const unsigned short POSITION_ITEM_EXIT_Y;

    static const unsigned short DIRECTION_TITLE_RED_INIT;
    static const unsigned short DIRECTION_TITLE_GREEN_INIT;

    static const unsigned short MAIN_MENU_SELECTOR_MIN;
    static const unsigned short MAIN_MENU_SELECTOR_MAX;

    static const unsigned short MAIN_MENU_ITEM_NEW_GAME;
    static const unsigned short MAIN_MENU_ITEM_LOAD_GAME;
    static const unsigned short MAIN_MENU_ITEM_EDITOR;
    static const unsigned short MAIN_MENU_ITEM_OPTIONS;
    static const unsigned short MAIN_MENU_ITEM_EXIT;

    static const short DIRECTION_TITLE_BLUE_INIT;

    static const short SELECTOR_COLOR_MINIMUM;
    static const short SELECTOR_COLOR_MAXIMUM;

public:

    MainMenuController();

    /**
     * @brief render the main menu
     *
     * @param pContext   commons items for controller
     *
     * @return uint8_t   id of the next screen controller
     */
    uint8_t render(
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
     */
    void selectMenuItem();

    unsigned short titleRedDirection;
    unsigned short titleGreenDirection;
    unsigned short selectorPosition;

    short titleBlueDirection;
    short selectorDirection;

    sf::Font fontTitle;
    sf::Font fontItem;

    sf::Color colorTitle;
    sf::Color colorWhite;
    sf::Color colorSelector;

    sf::Text title;
    sf::Text itemNewGame;
    sf::Text itemLoadGame;
    sf::Text itemEditor;
    sf::Text itemOptions;
    sf::Text itemExit;

    sf::Texture textureGithub;

    sf::Sprite spriteGithub;

    sf::Clock clockTitle;

    sf::SoundBuffer soundBuffer;

    sf::Sound soundSelectorMove;

    utils::AnimatedBackground background;

    utils::MenuGradient menuGradient;
};
}

#endif
