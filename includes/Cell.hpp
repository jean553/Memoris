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

#include <memory>

namespace sf
{
class Transform;
class Color;

/* 'typedef unsigned char Uint8' in SFML/Config.hpp, we declare exactly
   the same type here in order to both use declaration forwarding and
   prevent conflicting declaration */
typedef unsigned char Uint8;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace entities
{

class Cell
{

public:

    /**
     * @brief use to indicates the cell movement direction (for animations) 
     */
    enum class MovementDirection
    {
        UP, /** < move up */
        DOWN, /** < move down */
        LEFT, /** < move to the left */
        RIGHT /** < move to the right */
    };

    /**
     * @brief cell constructor from position and cell type
     *
     * @param context the current context
     * @param hPosition the horizontal position of the cell
     * @param vPosition the vertical position of the cell
     * @param cellType a character indicating the cell type
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    Cell(
        const utils::Context& context,
        const float& hPosition,
        const float& vPosition,
        const char& cellType
    );

    /**
     * @brief copy constructor, copy cells during the rotation floor animation
     *
     * @param cell constant reference to a cell object
     */
    Cell(const Cell& cell);

    Cell& operator=(const Cell&) = delete;

    /**
     * @brief default destructor
     */
    ~Cell();

    /**
     * @brief move the cell to one pixel on the right (used by menu animation)
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void moveHorizontally() const &;

    /**
     * @brief move the cells into the given direction (used by animation)
     *
     * @param direction the expected direction of the movement
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void moveInDirection(const MovementDirection& direction) const &;

    /**
     * @brief setter for the position
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     *
     * not noexcept because it calls SFML methods that are not noexcept
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
     * @brief returns the horizontal and vertical position of the cell
     *
     * @return const std::pair<float, float>
     */
    const std::pair<float, float> getPosition() const & noexcept;

    /**
     * @brief displays the cell according to the context
     *
     * @param context the context to use
     * @param transform SFML transform to use (for animation)
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void display(
        const utils::Context& context,
        const std::unique_ptr<sf::Transform>& transform = nullptr
    ) const &;

    /**
     * @brief displays the cell and highlights it when the mouse is hover
     *
     * @param context the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void displayWithMouseHover(const utils::Context& context) const &;

    /**
     * @brief hide the cell, the sprite is replaced by the hidden cell texture
     *
     * @param context the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void hide(const utils::Context& context) const &;

    /**
     * @brief show the cell
     *
     * @param context the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void show(const utils::Context& context) const &;

    /**
     * @brief cell type getter
     *
     * @return const char&
     */
    const char& getType() const & noexcept;

    /**
     * @brief setter for the type of the cell
     *
     * @param typeChar character representation of the type
     */
    void setType(const char& typeChar) const & noexcept;

    /**
     * @brief apply the given transparency on the cell
     *
     * @param context the context to use
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
    void setCellColor(const sf::Color& color) const &;

    /**
     * @brief set the cell to empty cell
     */
    void empty() const & noexcept;

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
     */
    void setIsVisible(const bool& visibility) const & noexcept;

    /**
     * @brief indicates if the mouse is currently hover this cell
     *
     * @return const bool
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    const bool isMouseHover() const &;

    /**
     * @brief reset the graphical position of the cell to the original one
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void resetPosition() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
