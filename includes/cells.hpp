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
 * @file cells.hpp
 * @brief contains all the cells types strings and a factory method to generate
 * appropriate cell object according to the given type (set the correct sprite
 * texture)
 * @package cells
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLS_H_
#define MEMORIS_CELLS_H_

#include <string>

namespace memoris
{
namespace cells
{

/* NOTE: this is allowed to define std::string objects inside the header as
   long as they are extern and not class members; strings cannot be constant
   expressions */

/* NOTE: the strings are declared as extern, like that we are sure they are
   only defined one time, and all the scripts that need them use the sames */

/* empty cell type string representation */
extern const std::string EMPTY_CELL;

/* departure cell type string representation */
extern const std::string DEPARTURE_CELL;

/* arrival cell type string representation */
extern const std::string ARRIVAL_CELL;

/* star cell type string representation */
extern const std::string STAR_CELL;

/* more life cell type string representation */
extern const std::string MORE_LIFE_CELL;

/* less life cell type string representation */
extern const std::string LESS_LIFE_CELL;

/* more time cell type string representation */
extern const std::string MORE_TIME_CELL;

/* less time cell type string representation */
extern const std::string LESS_TIME_CELL;

/* wall cell type string representation */
extern const std::string WALL_CELL;

}
}

#endif
