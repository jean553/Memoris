/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

/* the center position of the cells rotation in the animations */
constexpr float FLOOR_CENTER_X = 800.f;
constexpr float FLOOR_CENTER_Y = 498.f;

/* the dimensions of a cell in pixels and the separation between cells in
   pixels */
constexpr float CELL_PIXELS_DIMENSIONS = 49.f;
constexpr float CELLS_PIXELS_SEPARATION = 1.f;

};
}

#endif
