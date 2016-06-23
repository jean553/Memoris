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
 * @file MainMenuController.hpp
 * @brief render the main menu of the program; this is the
 * first controller which is loaded
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MAINMENUCONTROLLER_H_
#define MEMORIS_MAINMENUCONTROLLER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Controller.hpp"
#include "HasMenuSelectorAnimation.hpp"
#include "AnimatedBackground.hpp"
#include "MenuGradient.hpp"

namespace memoris
{
namespace controllers
{

class MainMenuController : public Controller
{
    /* TODO: #438 to delete, use a dedicated function */
    friend class policies::HasMenuSelectorAnimation;

public:

    /**
     * @brief constructor
     */
    MainMenuController(utils::Context& context);

    /**
     * @brief render the main menu controller
     *
     * @param context current context reference
     *
     * @return uint8_t id of the next screen controller
     *
     * TODO: #443 wrong return type, should be unsigned short
     */
    uint8_t render(utils::Context& context);

private:

    /**
     * @brief update the color of the title
     */
    void animateTitleColor();

    /**
     * @brief visually update the selector position
     *
     * @param context unique context
     */
    void updateSelectorPosition(utils::Context& context);

    /**
     * @brief call action for one selected menu item
     */
    void selectMenuItem();

    /* the file path of the Github picture, displayed in the top right
       corner fo the main menu screen */
    static const std::string PATH_IMAGE_GITHUB;

    /* the text content of each menu selectable item */
    static const std::string TITLE;
    static const std::string NEW_GAME;
    static const std::string LOAD_GAME;
    static const std::string EDITOR;
    static const std::string OPTIONS;
    static const std::string EXIT;

    /* maximum amount of RGB color for the title color animation: during
       rendering, the color of the title is continually changed. During the
       animation, the red, green and blue colors of the title cannot have a
       value that is more than these given constants */
    static const sf::Uint8 COLOR_TITLE_RED_MAX = 255;
    static const sf::Uint8 COLOR_TITLE_GREEN_MAX = 180;
    static const sf::Uint8 COLOR_TITLE_BLUE_MAX = 255;

    /* minimum amount of RGB color for the title color animation: the red,
       blue and green colors of the title cannot have a value that is less
       than this given constant */
    static const sf::Uint8 COLOR_TITLE_ALL_MIN = 0;

    /* position of the title */
    static constexpr float TITLE_HORIZONTAL_POSITION = 480.f;
    static constexpr float TITLE_VERTICAL_POSITION = 100.f;

    /* position of the new game menu item */
    static constexpr float NEW_GAME_HORIZONTAL_POSITION = 615.f;
    static constexpr float NEW_GAME_VERTICAL_POSITION = 300.f;

    /* position of the load game menu item */
    static constexpr float LOAD_GAME_HORIZONTAL_POSITION = 605.f;
    static constexpr float LOAD_GAME_VERTICAL_POSITION = 400.f;

    /* position of the editor menu item */
    static constexpr float EDITOR_HORIZONTAL_POSITION = 685.f;
    static constexpr float EDITOR_VERTICAL_POSITION = 500.f;

    /* position of the options menu item */
    static constexpr float OPTIONS_HORIZONTAL_POSITION = 660.f;
    static constexpr float OPTIONS_VERTICAL_POSITION = 600.f;

    /* position of the exit menu item */
    static constexpr float EXIT_HORIZONTAL_POSITION = 725.f;
    static constexpr float EXIT_VERTICAL_POSITION = 700.f;

    /* position of the github picture */
    static constexpr float GITHUB_PICTURE_HORIZONTAL_POSITION = 1300.f;
    static constexpr float GITHUB_PICTURE_VERTICAL_POSITION = 0.f;

    /* main menu items order, used to identify them */
    static constexpr unsigned short ITEM_NEW_GAME = 0;
    static constexpr unsigned short ITEM_LOAD_GAME = 1;
    static constexpr unsigned short ITEM_EDITOR = 2;
    static constexpr unsigned short ITEM_OPTIONS = 3;
    static constexpr unsigned short ITEM_EXIT = 4;

    static constexpr unsigned short DIRECTION_TITLE_RED_INIT = 1;
    static constexpr unsigned short DIRECTION_TITLE_GREEN_INIT = 1;
    static constexpr short DIRECTION_TITLE_BLUE_INIT = -1;

    /* TODO: #444 to refactor, should be sf::Uint8 and should
       not be less than 0...*/
    unsigned short titleRedDirection;
    unsigned short titleGreenDirection;
    short titleBlueDirection;

    /* TODO: #436 to refactor, should be refactored in a middleware,
       class or trait */
    unsigned short selectorPosition;
    short selectorDirection;

    /* the title and selector colors are declared here
       because they are animated and continually modified */
    sf::Color colorTitle;
    sf::Color colorSelector;

    sf::Text title;
    sf::Text itemNewGame;
    sf::Text itemLoadGame;
    sf::Text itemEditor;
    sf::Text itemOptions;
    sf::Text itemExit;

    sf::Texture textureGithub;
    sf::Sprite spriteGithub;

    /* TODO: #437 to refactor */
    sf::Clock clockTitle;

    /* object that generates and display the random
       cells in the main menu backround */
    utils::AnimatedBackground background;

    /* object that displays the black color gradient on
       both sides of the main menu items */
    utils::MenuGradient menuGradient;
};

}
}

#endif
