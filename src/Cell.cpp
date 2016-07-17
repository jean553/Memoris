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
#include "ColorsManager.hpp"
#include "Context.hpp"

namespace memoris
{
namespace entities
{

/**
 *
 */
Cell::Cell()
{
    /* TODO: this is not used inside the copy constructor,
      because we are mandatory to pass the utils::Context::get() as
      a parameter of the copy constructor. If we do that,
      this is not a copy constructor anymore... Need to
      find a solution for this... */
    /* the selector color is continually updated, that's
       why we copy it from the red color first */
    selectorColor = memoris::colors::ColorsManager::get().getColorRed();
    initializeCommonAttributes();
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
    float hPosition,
    float vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );

    hiddenCellPtr.setSpritePosition(
        horizontalPosition,
        verticalPosition
    );

    topSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition
    );

    bottomSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition +
        memoris::dimensions::CELL_PIXELS_DIMENSIONS -
        memoris::dimensions::SELECTED_CELLS_BORDER_WIDTH
    );

    leftSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition
    );

    rightSelectionBar.setPosition(
        horizontalPosition +
        memoris::dimensions::CELL_PIXELS_DIMENSIONS -
        memoris::dimensions::SELECTED_CELLS_BORDER_WIDTH,
        verticalPosition
    );
}

/**
 *
 */
void Cell::setPicturePath(std::string path)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture, true);

    picturePath = path;
}

/**
 *
 */
void Cell::display()
{
    utils::Context::get().getSfmlWindow().draw(sprite);
}

/**
 *
 */
void Cell::setStringRepresentation(const std::string& representation)
{
    stringRepresentation = representation;

    /* force the update of the picture path */
    setPicturePath("res/cells/" + representation + ".png");
}

/**
 *
 */
void Cell::initializeCommonAttributes()
{
    horizontalPosition = 0;
    verticalPosition = 0;

    topSelectionBar.setSize(
        sf::Vector2f(
            memoris::dimensions::CELL_PIXELS_DIMENSIONS,
            memoris::dimensions::SELECTED_CELLS_BORDER_WIDTH
        )
    );

    bottomSelectionBar.setSize(
        sf::Vector2f(
            memoris::dimensions::CELL_PIXELS_DIMENSIONS,
            memoris::dimensions::SELECTED_CELLS_BORDER_WIDTH
        )
    );

    leftSelectionBar.setSize(
        sf::Vector2f(
            memoris::dimensions::SELECTED_CELLS_BORDER_WIDTH,
            memoris::dimensions::CELL_PIXELS_DIMENSIONS
        )
    );

    rightSelectionBar.setSize(
        sf::Vector2f(
            memoris::dimensions::SELECTED_CELLS_BORDER_WIDTH,
            memoris::dimensions::CELL_PIXELS_DIMENSIONS
        )
    );

    topSelectionBar.setFillColor(selectorColor);
    bottomSelectionBar.setFillColor(selectorColor);
    leftSelectionBar.setFillColor(selectorColor);
    rightSelectionBar.setFillColor(selectorColor);
}

}
}
