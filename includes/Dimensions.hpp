/**
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
 * @file dimensions.hpp
 * @brief contains defined and fixed dimensions
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DIMENSIONS_H_
#define MEMORIS_DIMENSIONS_H_

namespace memoris
{
namespace dimensions
{

/* the common width of all the editor buttons, used into Editor level
controller */
constexpr unsigned short EDITOR_BUTTONS_WIDTH = 200;

/* amount of cells per floor, used in Level entity */
constexpr unsigned short LEVEL_CELLS_PER_FLOOR = 320;

/* amount of cells per level, used into the editor level controller and the
level entity */
constexpr unsigned short CELLS_PER_LEVEL = 3200;

/* amount of cells per column, used into the level entity */
constexpr unsigned short CELLS_PER_COLUMN = 16;

/* width and height of a cell, used into the animated background, the cell
   entity, the cell selector widget and level entity */
constexpr float CELL_PIXELS_DIMENSIONS = 49.f;

/* the separation between each cell in pixels, used into the animated
   background, the cell selector widget and the level entity */
constexpr float CELLS_PIXELS_SEPARATION = 1.f;

/* the border width of each cells in pixels, used into the Cell entity */
constexpr float SELECTED_CELLS_BORDER_WIDTH = 3.f;

/* the separation between cells into the cells selector widget */
constexpr float SELECTOR_CELLS_PIXELS_SEPARATION = 5.f;

};
}

#endif
