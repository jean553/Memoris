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
 * @brief cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CELL
#define DEF_CELL

#include <SFML/Graphics.hpp>

#include <string>

namespace entities {
class Cell {

public:

    Cell();

    /**
     * @brief destructor, mandatory as the class is abstract
     */
    virtual ~Cell();

    /**
     * @brief abstract method that defines the action
     * to perform when the cell is triggered
     */
    virtual void performAction() = 0;

    /**
     * @brief setter for the position
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     */
    void setPosition(int hPosition, int vPosition);

    /**
     * @brief set the picture
     *
     * @param path image path
     */
    void setPicturePath(std::string path);

private:

    int horizontalPosition;
    int verticalPosition;

    sf::Texture texture;

    sf::Sprite sprite;
};
}

#endif
