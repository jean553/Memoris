/*
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
 * @file MenuGradient.hpp
 * @brief this class manages the rendering of color gradients displayed on
 * both of the two menu sides
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MENUGARDIENT_H_
#define MEMORIS_MENUGARDIENT_H_

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

namespace memoris
{
namespace others
{

class MenuGradient
{
public:

    /**
     * @brief constructor, loads the main surface and call a separated method
     * to initialize all the gradient rectangles
     */
    MenuGradient();

    /**
     * @brief display the menu background and all the gradient effect lines
     * surfaces
     */
    void display();

private:

    /**
     * @brief private method called by the constructor only to create the
     * background sides lines with the gradient effect
     *
     * NOTE: the creation of the rectangles can be done directly inside the
     * constructor of the class; in fact, there are many local variables
     * to use to create these surfaces; in order to improve the code
     * organization and clarity, we create these surfaces into a dedicated
     * function.
     */
    void initializeGradientRectangles();

    /* the main rectangle shape is the black rectangle without any gradient
       that is directly the background of the menu items; the gradient
       surfaces are at both left and right sides of this rectangle */
    sf::RectangleShape menuBackground;

    /* the sides rectangles are vertical lines displayed on both of the menu
       background; they all have the same color but a different alpha value
       to create the gradient visual effect */
    /* TODO: #484 is it really necessary to use smart pointers here ?
       Investigate, eventually modify and document... */
    std::vector<std::unique_ptr<sf::RectangleShape>> sidesLines;
};

}
}

#endif
