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

#include "AbstractMenuController.hpp"

#include "AnimatedBackground.hpp"
#include "MenuGradient.hpp"
#include "MenuItem.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace controllers
{

class MainMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor
     */
    MainMenuController(utils::Context& context);

    /**
     * @brief destructor, delete the dynamically allocated menu items
     */
    ~MainMenuController();

    /**
     * @brief render the main menu controller
     *
     * @param context current context reference
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render(utils::Context& context);

private:

    /**
     * @brief update the color of the title
     */
    void animateTitleColor();

    /**
     * @brief call action for one selected menu item
     *
     * TODO: #466 should be a pure virtual method ( the destructor does not
     * need to be pure virtual anymore );
     */
    void selectMenuItem();

    /* NOTE: we use SFML 32 bits long integers to save the
       last updated time of each animation; we use this
       data type as it is the one used by SFML clock */

    /* save the last time the title color has been modified */
    sf::Int32 titleLastAnimationTime;

    /* variables to animate the colors of the main menu title */
    /* TODO: #444 to refactor, should be sf::Uint8 and should
       not be less than 0...*/
    unsigned short titleRedDirection;
    unsigned short titleGreenDirection;
    short titleBlueDirection;

    /* the main menu 'Memoris' animated title color, copied here because
       this color is animated and change all the time */
    sf::Color colorTitle;

    /* the main menu 'Memoris' animated title */
    sf::Text title;

    /* main menu items pointers; we use pointers because we store them
       in the abstract menu class items list; we do this to prevent copy */
    /* TODO: #463 use smart pointers/use move sementics ? */
    items::MenuItem* newGame;
    items::MenuItem* loadGame;
    items::MenuItem* editor;
    items::MenuItem* options;
    items::MenuItem* exit;

    /* the displayed github texture sprite, in the top right corner */
    sf::Sprite spriteGithub;

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
