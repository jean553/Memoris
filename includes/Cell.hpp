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

#include "Context.hpp"
#include "aliases.hpp"

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
     * @param context reference to the current context
     * @param hPosition the horizontal position of the cell
     * @param vPosition the vertical position of the cell
     * @param cellType the type of the cell, represented by a unique character
     */
    Cell(
        const utils::Context& context,
        const float& hPosition,
        const float& vPosition,
        const char& cellType
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
     * @brief returns the horizontal position of the cell
     *
     * @return const float&
     */
    const float& getHorizontalPosition() const & noexcept;

    /**
     * @brief returns the vertical position of the cell
     *
     * @return const float&
     */
    const float& getVerticalPosition() const & noexcept;

    /**
     * @brief displays the cell according to the context
     *
     * @param context shared pointer to the context to use
     * @param transform unique pointer to the transform to use, nullptr if no
     * transform to use; the transform is a SFML object used for the animation
     * of all the cells; if the transform is not null, the modification defined
     * in this transform object is applied to every cell
     */
    void display(
        const utils::Context& context,
        aliases::ConstTransformUniquePtrRef transform = nullptr
    );

    /**
     * @brief displays the cell in the context and enable the mouse hover
     * feature that highlight the cell when the mouse is hover; this function
     * is used when rendering the level inside the level editor; we use a
     * separated function to avoid adding logic just to choose if the cell
     * must be highlighted
     *
     * @param context shared pointer to the context to use
     * @param transform unique pointer reference to a transform
     *
     * TODO: #691 the transform is not used at all in this function
     */
    void displayWithMouseHover(
        const utils::Context& context,
        aliases::ConstTransformUniquePtrRef transform = nullptr
    );

    /**
     * @brief hide the cell, the sprite is replaced by the hidden cell texture
     *
     * @param context shared pointer to the context to use
     */
    void hide(utils::Context& context);

    /**
     * @brief show the cell, loads a reference of the texture to display
     * according to the current set type character; this method can be called
     * from the level object but is also called automatically by the Cell
     * constructor when the object is built
     *
     * @param context shared pointer to the context to use
     */
    void show(const utils::Context& context);

    /**
     * @brief returns a reference to the current set cell type character; we
     * return a constant because this attribute should not be modified from
     * the outside in that way; this function is only a getter; we return
     * a reference to optimize and avoid copy;
     *
     * @return const char&
     */
    const char& getType() const;

    /**
     * @brief setter for the type of the cell
     *
     * @param typeChar character representation of the type
     */
    void setType(const char& typeChar);

    /**
     * @brief get a copy of the white color from the colors manager; apply
     * the given transparency to this color and set it as the cell current
     * color
     *
     * @param context reference to the current context to use
     * @param alpha the SFML sf::Color oject transparency value
     */
    void setCellColorTransparency(
        utils::Context& context,
        const sf::Uint8& alpha
    );

    /**
     * @brief color to apply on the cell
     *
     * @param color reference to the SFML color to use
     */
    void setCellColor(const sf::Color& color);

    /**
     * @brief changes the cell to an empty cell, this is used by the game
     * controller when the player leaves a cell;
     */
    void empty();

    /**
     * @brief getter for the visible parameter
     *
     * @return const bool&
     */
    const bool& isVisible() const;

    /**
     * @brief setter for the visibility boolean of the cell
     *
     * @param visibility is the cell visible
     *
     * the method is not 'const' because it is a setter that modifies an
     * attribute
     */
    void setIsVisible(const bool& visibility) noexcept;

    /**
     * @brief indicates if the mouse is currently hover this cell
     *
     * @return const bool
     */
    const bool isMouseHover() const;

private:

    static constexpr float CELL_DIMENSION {49.f};

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

    /* contains the current type of the cell according of the 'cells' types
       list into cells.hpp; this variable is not directly initialized here
       because it is initialized inside the constructor */
    char type;

    /* this boolean is true if the current cell is visible; false if hidden;
       used by the animations to transfer visibility of the cells; by default,
       all the cells are hidden; this value is modified by the hide() and
       show() methods */
    bool visible {false};

    /* used to know if the cell is current highlight or not to avoid
       superfluous execution when rendering the level editor */
    bool highlight {false};
};

}
}

#endif
