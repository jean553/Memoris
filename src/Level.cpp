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
 * @file Level.cpp
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Level.hpp"

#include "Context.hpp"
#include "cells.hpp"

namespace memoris
{
namespace entities
{

/**
 *
 */
Level::Level()
{
    /* call the separated method that initializes all the cells with empty
       cells */
    initializeCells();
}

/**
 *
 */
void Level::display(const unsigned short& floor) const
{
    /* calculate the index of the first cell of the given floor */
    const unsigned short firstCellIndex = floor * 320;

    /* calculate the index of the last cell of the given floor */
    const unsigned short lastCellIndex = floor * 320 + 320;

    /* only display the cells of the given floor; all the other cells of the
       level are ignored */
    for(
        unsigned short index = firstCellIndex;
        index < lastCellIndex;
        index++
    )
    {
        /* get an unique pointer, get the cell object from this pointer */
        (*cells[index]).display();
    }
}

/**
 *
 */
void Level::initializeCells()
{
    /* positions cursor used to keep trace of the initialized cell position
       when initializing every cell one by one */
    unsigned short horizontalPositionCursor {0}, verticalPositionCursor {0};

    /* there are 3200 cells per level, 320 per floor, there are 10 floors */
    for(unsigned short index {0}; index < 3200; index++)
    {
        /* create an unique pointer to a cell object; the horizontal position
           of a cell is equal to 300 (horizontal position of the grid) + 50
           (cell width including separator) * the horizontal position cursor;
           the vertical position of a cell is equal to 98 (vertical position of
           the grid) + 50 (cell height including separator) * the vertical
           position cursor; the data type expected by the Cell constructor for
           the position is a float; this is faster to calculate positions with
           unsigned shorts, and cast them to float at the end when setting
           the data; this is not a problem to cast as we always manipulate
           integer values anyway */
        std::unique_ptr<Cell> cell(
            new Cell(
                300.f + 50.f * static_cast<float>(horizontalPositionCursor),
                98.f + 50.f * static_cast<float>(verticalPositionCursor),
                cells::EMPTY_CELL
            )
        );

        /* increment the horizontal position cursor */
        horizontalPositionCursor++;

        /* the cells are created line by line; when one line is finished
           (modulo 20, there are 20 cells per line), jump to the next line
           and reset the horizontal position cursor; we do not use !() but
           == 0 instead: we really want make this test explicit */
        if (horizontalPositionCursor % 20 == 0)
        {
            /* reset the horizontal position cursor */
            horizontalPositionCursor = 0;

            /* increment the vertical position cursor */
            verticalPositionCursor++;
        }

        /* move the unique pointer into the cells unique pointers container */
        cells.push_back(std::move(cell));
    }
}

}
}
