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

#include "Cell.hpp"

namespace memoris
{
namespace cells
{

constexpr float HORIZONTAL_POSITION_ORIGIN {400.f};
constexpr float VERTICAL_POSITION_ORIGIN {98.f};
constexpr float CELL_DIMENSIONS {50.f};

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

/**
 * @brief create Cell unique pointers, usuable at a given position inside
 * the level; the given positions are the positions of the cell *inside* the
 * level (the level position is the origin of the cells positions); we use
 * a template for the positions types (whatever the type, the position is
 * cast to float)
 *
 * @param context reference to the current context to use
 * @param horizontalPosition the horizontal position of the cell
 * @param verticalPosiition the vertical position of the cell
 * @param type the cell type
 *
 * @return std::unique_ptr<entities::Cell>
 */
template<typename T>
std::unique_ptr<entities::Cell> getCellByType(
    const utils::Context& context,
    const T& horizontalPosition,
    const T& verticalPosition,
    const char type
);

}
}

#endif
