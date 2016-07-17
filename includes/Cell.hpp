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

#include "HiddenCellPicture.hpp"

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
     * @brief default constructor
     */
    Cell();

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
     */
    void setPosition(
        float hPosition,
        float vPosition
    );

    /**
     * @brief set the picture
     *
     * @param path image path
     */
    void setPicturePath(std::string path);

    /**
     * @brief displays the cell according to the context
     */
    void display();

    /**
     * @brief setter for the string representation
     *
     * @param representation string representation
     */
    void setStringRepresentation(const std::string& representation);

private:

    /**
     * @brief common initializer for all constructors
     */
    void initializeCommonAttributes();

    float horizontalPosition;
    float verticalPosition;

    sf::Texture texture;

    sf::Sprite sprite;

    sf::RectangleShape topSelectionBar;
    sf::RectangleShape bottomSelectionBar;
    sf::RectangleShape leftSelectionBar;
    sf::RectangleShape rightSelectionBar;

    /* the color of the animated cell selector; this is
       declared here as the color is animated and continually
       modified */
    sf::Color selectorColor;

    /* TODO: should be refactored, for now
     * we create one hidden cell per cell... */
    ::utils::HiddenCellPicture hiddenCellPtr;

    std::string picturePath;
    std::string stringRepresentation;
};

}
}

#endif
