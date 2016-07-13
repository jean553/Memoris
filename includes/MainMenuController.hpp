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
    MainMenuController();

    /**
     * @brief render the main menu controller
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render();

private:

    /**
     * @brief update the color of the title
     */
    void animateTitleColor();

    /**
     * @brief overwrite the parent method, defines which controller
     * is called when one menu item is selected
     */
    void selectMenuItem();

    /* NOTE: we use SFML 32 bits long integers to save the
       last updated time of each animation; we use this
       data type as it is the one used by SFML clock */

    /* save the last time the title color has been modified; the default
       value is 0 */
    sf::Int32 titleLastAnimationTime {0};

    /* booleans used to indicate if we have to increment or decrement each
       color value (rgb) of the main menu title color animation; we use
       booleans instead of having signed numbers to indicate the direction
       (increment or decrement) : in fact, we avoid to mix signed numbers
       with sf::Uint8 (color number type) */
    bool incrementTitleRedColor;
    bool incrementTitleGreenColor;
    bool incrementTitleBlueColor;

    /* the main menu 'Memoris' animated title color, copied here because
       this color is animated and change all the time */
    sf::Color colorTitle;

    /* the main menu 'Memoris' animated title */
    sf::Text title;

    /* the displayed github texture sprite, in the top right corner */
    sf::Sprite spriteGithub;
};

}
}

#endif
