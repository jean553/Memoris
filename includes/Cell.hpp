/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
     * public because used by the quarter rotation animation
     */
    enum class MovementDirection
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

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
     * @brief copy constructor, used to copy cells during the rotation floor
     * animation
     *
     * @param cell constant reference to a cell object
     */
    Cell(const Cell& cell);

    /**
     * @brief default destructor, empty, only declared here in order to use
     * the forwarding declaration
     */
    ~Cell() noexcept;

    /**
     * @brief move the cell to one pixel on the right; this method is used
     * with the animated background
     */
    void moveOnTheRight() const &;

    /**
     * @brief move the cells into the given direction; used by the quarter
     * rotate animation
     *
     * @param direction the expected direction of the movement
     *
     * not 'const' because modifies the position
     * TODO: this const should be added when adding impl idiom in the class
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void moveInDirection(const MovementDirection& direction) &;

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
    ) const &;

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
        const std::unique_ptr<sf::Transform>& transform = nullptr
    ) const &;

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
        const std::unique_ptr<sf::Transform>& transform = nullptr
    ) const &;

    /**
     * @brief hide the cell, the sprite is replaced by the hidden cell texture
     *
     * @param context shared pointer to the context to use
     */
    void hide(const utils::Context& context) const &;

    /**
     * @brief show the cell, loads a reference of the texture to display
     * according to the current set type character; this method can be called
     * from the level object but is also called automatically by the Cell
     * constructor when the object is built
     *
     * @param context shared pointer to the context to use
     */
    void show(const utils::Context& context) const &;

    /**
     * @brief returns a reference to the current set cell type character; we
     * return a constant because this attribute should not be modified from
     * the outside in that way; this function is only a getter; we return
     * a reference to optimize and avoid copy;
     *
     * @return const char&
     */
    const char& getType() const & noexcept;

    /**
     * @brief setter for the type of the cell
     *
     * @param typeChar character representation of the type
     *
     * TODO: should be const after integration of pimpl idiom
     */
    void setType(const char& typeChar) const & noexcept;

    /**
     * @brief get a copy of the white color from the colors manager; apply
     * the given transparency to this color and set it as the cell current
     * color
     *
     * @param context reference to the current context to use
     * @param alpha the SFML sf::Color oject transparency value
     */
    void setCellColorTransparency(
        const utils::Context& context,
        const sf::Uint8& alpha
    ) const &;

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
    void empty() const &;

    /**
     * @brief getter for the visible parameter
     *
     * @return const bool&
     */
    const bool& isVisible() const & noexcept;

    /**
     * @brief setter for the visibility boolean of the cell
     *
     * @param visibility is the cell visible
     *
     * the method is not 'const' because it is a setter that modifies an
     * attribute
     *
     * TODO: should be const after integration of pimpl idiom
     */
    void setIsVisible(const bool& visibility) const & noexcept;

    /**
     * @brief indicates if the mouse is currently hover this cell
     *
     * @return const bool
     */
    const bool isMouseHover() const;

    /**
     * @brief reset the graphical position of the cell to the original one
     *
     * not const because it mofifies the current position of the cell
     *
     * not noexcept because it calls SFML functions that are not noexcept
     *
     * public because it is called by the quarter rotation animations in order
     * to graphically refresh the positions of the cells
     */
    void resetPosition() &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
