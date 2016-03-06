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
 * @file ElevatorDownCell.hpp
 * @brief elevator down cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@sdowninfo.com>
 */

#ifndef DEF_ELEVATOR_DOWN_CELL
#define DEF_ELEVATOR_DOWN_CELL

#include "Cell.hpp"

#include <string>

namespace entities {
class ElevatorDownCell : public Cell {

    static const std::string ELEVATOR_DOWN_CELL_PICTURE_PATH;

public:

    ElevatorDownCell();

    /**
     * @brief definition of the action to
     * perform when the cell is triggered
     */
    void performAction();
};
}

#endif
