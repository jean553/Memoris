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
 * @file Cell.hpp
 * @brief cell entity, represents one cell
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELL_H_
#define MEMORIS_CELL_H_

#include <SFML/Graphics.hpp>

#include <string>

namespace memoris
{
namespace entities
{

class Cell
{

public:

    /**
     * @brief cell constructor, get the horizontal and vertical position of
     * the cell, get the type of the cell. Set the cell at the given
     * position, set the cell type
     *
     * @param hPosition the horizontal position of the cell
     * @param vPosition the vertical position of the cell
     * @param type the type of the cell, represented by a unique character
     */
    Cell(
        const float& hPosition,
        const float& vPosition,
        const char& type
    );

    /**
     * @brief move the cell to one pixel on the right; this method is used
     * with the animated background
     */
    void moveOnTheRight();

    /**
     * @brief setter for the position
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     *
     * NOTE: we use a separated method to set the horizontal and vertical
     * position, because this is a code called by the constructor but also
     * by the methods that update the cells position (like the animated
     * background animation)
     */
    void setPosition(
        const float& hPosition,
        const float& vPosition
    );

    /**
     * @brief displays the cell according to the context
     */
    void display();

    /**
     * @brief hide the cell, the sprite is replaced by the hidden cell texture
     */
    void hide();

private:

    /* the horizontal and vertical positions of the cell on the screen */
    /* NOTE: we do not initialize the positions here, because they have to
       be initialized inside the cell constructor; these positions are already
       saved into the SFML surface object but we save them also into this
       class object; in fact, we need to access them quickly to calculate the
       cells movements and also to use the cells selector */
    float horizontalPosition;
    float verticalPosition;

    /* the SFML surface of the cell */
    sf::Sprite sprite;
};

}
}

#endif
