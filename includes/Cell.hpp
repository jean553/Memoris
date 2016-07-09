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
#include "HiddenCellPicture.hpp"

namespace entities
{
class Cell
{

public:

    /**
     * @brief default constructor
     */
    Cell(memoris::utils::Context& context);

    /**
     * @brief copy constructor
     *
     * @param context current context reference
     * @param Cell reference to a cell to copy
     *
     * XXX: the copy is not done correctly anymore,
     * the sf::Sprite and textures are not copied
     * anymore. This is because this constructor is
     * not called at all anymore, this is not a
     * copy constructor anymore...
     *
     * the only place we need the context in this
     * constructor is inside the initializeCommonAttributes
     * function for the selector color... I guess the
     * best solution is maybe declare the selector color
     * attributes, directly inside the Cell, in "static" variables...
     */
    Cell(
        const Cell& cell
    );

    /**
     * @brief constructor
     *
     * @param context current context reference
     * @param fileRepresentation the string representation
     * of the cell into the level file
     */
    Cell(
        memoris::utils::Context& context,
        std::string fileRepresentation
    );

    /**
     * @brief destructor, mandatory as the class is abstract
     */
    virtual ~Cell();

    /**
     * @brief abstract method that defines the action
     * to perform when the cell is triggered
     */
    virtual void performAction();

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
     * @brief get the picture path
     *
     * @return string
     */
    std::string getPicturePath() const;

    /**
     * @brief displays the cell according to the context
     *
     * @param context context pointer
     */
    void display(memoris::utils::Context& context);

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
     * @param cellAddress address of the cell inside the array
     *
     * TODO: should be deleted, check if a vector function exists
     * to get the current index of an item in the array...
     */
    void setLevelAddresses(const uint16_t& cellAddress);

    /**
     * @brief getter for the horizontal address of the cell on a level grid
     *
     * @return uint16_t
     */
    uint16_t getAddress() const;

    /**
     * @brief setter for hidden parameter
     *
     * @param hidden true if the cell is hidden
     */
    void setHidden(const bool& hidden);

    /**
     * @brief getter for the hidden parameter
     *
     * @return bool
     */
    bool getIsHidden() const;

    /**
     * @brief setter for the cursor sensitivity of the cell,
     * if sensitive, the cell's color changes when the cursor
     * is overring it
     *
     * @param sensitivity true if the cell is sensitive
     */
    void setCursorSensitivity(const bool& sensitivity);

    /**
     * @brief setter for the string representation
     *
     * @param representation string representation
     */
    void setStringRepresentation(const std::string& representation);

    /**
     * @brief getter for the string representation
     *
     * @return string
     */
    std::string getStringRepresentation() const;

    /**
     * @brief setter for the animation boolean
     *
     * @param animate boolean for the animation
     */
    void setIsAnimated(const bool& animate);

private:

    static const uint8_t INTERVAL_ANIMATION;
    static const uint8_t SELECTOR_COLOR_INCREMENTATION_STEP;

    static const uint16_t MINIMUM_RED_COLOR_AMOUNT;
    static const uint16_t MAXIMUM_RED_COLOR_AMOUNT;

    /**
     * @brief common initializer for all constructors
     */
    void initializeCommonAttributes();

    /**
     * @brief animate the cell selector
     */
    void animateCell();

    bool isSelected;
    bool isHidden;
    bool isCursorSensitive;
    bool isAnimated;

    float horizontalPosition;
    float verticalPosition;

    uint16_t address;

    int8_t selectorDirection;

    sf::Texture texture;

    sf::Sprite sprite;

    sf::Clock clock;

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
    utils::HiddenCellPicture hiddenCellPtr;

    std::string picturePath;
    std::string stringRepresentation;
};
}

#endif
