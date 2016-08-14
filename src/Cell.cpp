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

namespace memoris
{
namespace entities
{

/**
 *
 */
Cell::Cell(
    const std::shared_ptr<utils::Context>& context,
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
void Cell::setPosition(
    const float& hPosition,
    const float& vPosition
)
{
    /* save the given values */
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    /* set the new position of the SFML surface */
    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void Cell::display(const std::shared_ptr<utils::Context>& context)
{
    /* display the cell sprite */
    context->getSfmlWindow().draw(sprite);
}

/**
 *
 */
void Cell::hide(const std::shared_ptr<utils::Context>& context)
{
    sprite.setTexture(
        context->getCellsTexturesManager().getHiddenCellTexture()
    );
}

/**
 *
 */
void Cell::show(const std::shared_ptr<utils::Context>& context)
{
    /* get the texture from the cells textures manager according to the type
       of cell; set this reference as a texture for the current cell object */
    sprite.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            type
        )
    );
}

/**
 *
 */
const char& Cell::getType()
{
    return type;
}

/**
 *
 */
void Cell::setCellColorTransparency(
    const std::shared_ptr<utils::Context>& context,
    const sf::Uint8& alpha
)
{
    /* get a copy of the white color from the colors manager */
    sf::Color cellColor = context->getColorsManager().getColorWhiteCopy();

    /* update the transparency of the color */
    cellColor.a = alpha;

    /* update the color of the cell */
    sprite.setColor(cellColor);
}

/**
 *
 */
void Cell::empty()
{
    /* set the cell as empty by changing the type to empty cell */
    type = cells::EMPTY_CELL;
}

}
}
