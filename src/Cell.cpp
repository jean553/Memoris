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
 * @file Cell.cpp
 * @brief cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Cell.hpp"

#include "dimensions.hpp"
#include "window.hpp"
#include "cells.hpp"
#include "ColorsManager.hpp"
#include "CellsTexturesManager.hpp"

namespace memoris
{
namespace entities
{

/**
 *
 */
Cell::Cell(
    const utils::Context& context,
    const float& hPosition,
    const float& vPosition,
    const char& cellType
) :
    type(cellType)
{
    /* set the given position */
    setPosition(
        hPosition,
        vPosition
    );

    /* the cell is shown by default; we get the reference of the texture to
       display according to the given cell type */
    show(context);
}

/**
 *
 */
void Cell::moveOnTheRight()
{
    /* increment the horizontal position of the cell; we do
       it separately to make it clear */
    horizontalPosition++;

    /* if the cell is outside of the screen on the right side, the position
       is reset to -49 because a cell width is 49 pixel; the cell is now
       outside of the screen, on the left corner and will be displayed soon
       during the animation; we considere the cell outside of the screen on
       the right corner when the position is 1649, that means the window
       width and one cell width */
    if (horizontalPosition == memoris::window::WIDTH)
    {
        /* note that the cell pixel dimensions is forced to be signed */
        horizontalPosition = -memoris::dimensions::CELL_PIXELS_DIMENSIONS;
    }

    /* update the horizontal position */
    setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void Cell::moveInDirection(const MovementDirection& direction) &
{
    switch(direction)
    {
    case MovementDirection::UP:
    {
        verticalPosition -= POSITION_UPDATE_STEP;

        break;
    }
    case MovementDirection::DOWN:
    {
        verticalPosition += POSITION_UPDATE_STEP;

        break;
    }
    case MovementDirection::LEFT:
    {
        horizontalPosition -= POSITION_UPDATE_STEP;

        break;
    }
    case MovementDirection::RIGHT:
    {
        horizontalPosition += POSITION_UPDATE_STEP;

        break;
    }
    }

    setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void Cell::setPosition(
    const float& hPosition,
    const float& vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
const float& Cell::getHorizontalPosition() const & noexcept
{
    return horizontalPosition;
}

/**
 *
 */
const float& Cell::getVerticalPosition() const & noexcept
{
    return verticalPosition;
}

/**
 *
 */
void Cell::display(
    const utils::Context& context,
    aliases::ConstTransformUniquePtrRef transform
)
{
    /* display the cell with a transform SFML object if an object is pointed
       by the given unique pointer reference */
    if (transform != nullptr)
    {
        context.getSfmlWindow().draw(sprite, *transform);
    }
    else
    {
        context.getSfmlWindow().draw(sprite);
    }
}

/**
 *
 */
void Cell::displayWithMouseHover(
    const utils::Context& context,
    aliases::ConstTransformUniquePtrRef transform
)
{
    if (isMouseHover() && !highlight)
    {
        highlight = true;

        sprite.setColor(context.getColorsManager().getColorDarkGrey());
    }
    else if(!isMouseHover() && highlight)
    {
        highlight = false;

        sprite.setColor(context.getColorsManager().getColorWhite());
    }

    context.getSfmlWindow().draw(sprite);
}

/**
 *
 */
void Cell::hide(const utils::Context& context)
{
    sprite.setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::HIDDEN_CELL
        )
    );

    /* the cell is hidden, so the boolean of visibility is updated to false */
    visible = false;
}

/**
 *
 */
void Cell::show(const utils::Context& context)
{
    /* get the texture from the cells textures manager according to the type
       of cell; set this reference as a texture for the current cell object */
    sprite.setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            type
        )
    );

    /* the cell is shown, so the boolean of visibility is updated to true */
    visible = true;
}

/**
 *
 */
const char& Cell::getType() const & noexcept
{
    return type;
}

/**
 *
 */
void Cell::setType(const char& typeChar) & noexcept
{
    type = typeChar;
}

/**
 *
 */
void Cell::setCellColorTransparency(
    const utils::Context& context,
    const sf::Uint8& alpha
) &
{
    sf::Color cellColor = context.getColorsManager().getColorWhiteCopy();

    cellColor.a = alpha;

    sprite.setColor(cellColor);
}

/**
 *
 */
void Cell::setCellColor(const sf::Color& color)
{
    sprite.setColor(color);
}

/**
 *
 */
void Cell::empty()
{
    /* set the cell as empty by changing the type to empty cell */
    type = cells::EMPTY_CELL;
}

/**
 *
 */
const bool& Cell::isVisible() const & noexcept
{
    return visible;
}

/**
 *
 */
void Cell::setIsVisible(const bool& visibility) & noexcept
{
    visible = visibility;
}

/**
 *
 */
const bool Cell::isMouseHover() const
{
    /* get the position of the cursor */
    sf::Vector2<int> cursorPosition = sf::Mouse::getPosition();

    if (
        cursorPosition.x > horizontalPosition &&
        cursorPosition.x < horizontalPosition + CELL_DIMENSION &&
        cursorPosition.y > verticalPosition &&
        cursorPosition.y < verticalPosition + CELL_DIMENSION
    )
    {
        return true;
    }

    return false;
}

}
}
