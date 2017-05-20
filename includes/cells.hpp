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
 * @file cells.hpp
 * @brief contains all the cells
 * @package cells
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLS_H_
#define MEMORIS_CELLS_H_

namespace memoris
{
namespace cells
{

constexpr char EMPTY_CELL {'e'};
constexpr char DEPARTURE_CELL {'d'};
constexpr char ARRIVAL_CELL {'a'};
constexpr char STAR_CELL {'s'};
constexpr char MORE_LIFE_CELL {'L'};
constexpr char LESS_LIFE_CELL {'l'};
constexpr char MORE_TIME_CELL {'T'};
constexpr char LESS_TIME_CELL {'t'};
constexpr char WALL_CELL {'w'};
constexpr char STAIRS_UP_CELL {'u'};
constexpr char STAIRS_DOWN_CELL {'p'};
constexpr char HORIZONTAL_MIRROR_CELL {'%'};
constexpr char VERTICAL_MIRROR_CELL {'P'};
constexpr char DIAGONAL_CELL {'?'};
constexpr char LEFT_ROTATION_CELL {'('};
constexpr char RIGHT_ROTATION_CELL {')'};
constexpr char HIDDEN_CELL {'h'};
constexpr char ELEVATOR_UP_CELL {'U'};
constexpr char ELEVATOR_DOWN_CELL {'V'};
constexpr char QUARTER_ROTATION_CELL {'q'};
constexpr char INVERTED_QUARTER_ROTATION_CELL {'Q'};

constexpr char NO_CELL {' '};

}
}

#endif
