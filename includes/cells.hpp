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
 * @brief each cell is represented by one character (value between 0 and 255),
 * we use this data type because it makes loading and manipulations faster
 * when reading, playing and comparing; the character of a cell is always the
 * first letter of its type, in lowercase; if it's a bonus, the character is
 * uppercase, if it is a malus, the character is in lowercase
 * @package cells
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLS_H_
#define MEMORIS_CELLS_H_

namespace memoris
{
namespace cells
{

/* empty */
constexpr char EMPTY_CELL {'e'};

/* departure */
constexpr char DEPARTURE_CELL {'d'};

/* arrival */
constexpr char ARRIVAL_CELL {'a'};

/* star */
constexpr char STAR_CELL {'s'};

/* more life */
constexpr char MORE_LIFE_CELL {'L'};

/* less life */
constexpr char LESS_LIFE_CELL {'l'};

/* more time */
constexpr char MORE_TIME_CELL {'T'};

/* less time */
constexpr char LESS_TIME_CELL {'t'};

/* wall */
constexpr char WALL_CELL {'w'};

/* stairs up */
constexpr char STAIRS_UP_CELL {'u'};

/* stairs down */
constexpr char STAIRS_DOWN_CELL {'p'};

/* horizontal mirror event cell */
constexpr char HORIZONTAL_MIRROR_CELL {'%'};

/* vertical mirror event cell */
constexpr char VERTICAL_MIRROR_CELL {'P'};

/* quarters diagonal animation */
constexpr char DIAGONAL_CELL {'?'};

}
}

#endif
