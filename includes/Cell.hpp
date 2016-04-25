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

#include "Context.hpp"

namespace entities
{
class Cell
{

public:

    const std::string IN_FILE_REPRESENTATION;

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
     *
     * @param pContext context pointer
     */
    void display(utils::Context* pContext);

    /**
     * TODO: this parameter has two different uses: set the selected cell in the selector widget
     * but also update manually when the user clicks on one cell of the level grid. Each use
     * should be separated, should create a new parameter... ?
     *
     * @brief set the cell as selected, used to display
     * the selection frame around the cell
     */
    void setSelected(bool selected);

    /**
     * @brief getter for cell selection parameter
     *
     * @return bool
     */
    bool getIsSelected() const;

    /**
     * @brief check if the mouse is hover the cell
     *
     * @return bool
     */
    bool isMouseHover() const;

    /**
     * @brief getter for the horizontal position of the cell on the screen
     *
     * @return float
     */
    float getHorizontalPosition() const;

    /**
     * @brief getter for the vertical position of the cell on the screen
     *
     * @return float
     */
    float getVerticalPosition() const;

    /**
     * @brief setter for the horizontal and vertical address of the cell on a level grid
     *
     * @param hAddress horizontal address
     * @param vAddress vertical address
     */
    void setLevelAddresses(
        short hAddress,
        short vAddress
    );

    /**
     * @brief getter for the horizontal address of the cell on a level grid
     *
     * @return short
     */
    short getHorizontalAddress() const;

    /**
     * @brief getter for the vertical address of the cell on a level grid
     *
     * @return short
     */
    short getVerticalAddress() const;

protected:

    /**
     * @brief constructor
     */
    Cell(std::string fileRepresentation);

private:

    bool isSelected;

    float horizontalPosition;
    float verticalPosition;

    short horizontalAddress;
    short verticalAddress;

    sf::Texture texture;

    sf::Sprite sprite;

    sf::RectangleShape topSelectionBar;
    sf::RectangleShape bottomSelectionBar;
    sf::RectangleShape leftSelectionBar;
    sf::RectangleShape rightSelectionBar;

    sf::Color transparentWhiteColor;
    sf::Color whiteColor;
    sf::Color selectorColor;
};
}

#endif
