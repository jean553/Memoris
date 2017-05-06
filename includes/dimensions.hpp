/**
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
 * @file dimensions.hpp
 * @brief provides level dimensions
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DIMENSIONS_H_
#define MEMORIS_DIMENSIONS_H_

namespace memoris
{
namespace dimensions
{

constexpr float TOP_SIDE_LAST_CELL_INDEX {128};

constexpr unsigned short CELLS_PER_LINE {16};
constexpr unsigned short CELLS_PER_FLOOR {256};

}
}

#endif
