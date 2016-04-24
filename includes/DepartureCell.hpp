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
 * @file DepartureCell.hpp
 * @brief departure cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_DEPARTURE_CELL
#define DEF_DEPARTURE_CELL

#include "Cell.hpp"

#include <string>

namespace entities
{
class DepartureCell : public Cell
{

    static const std::string DEPARTURE_CELL_PICTURE_PATH;

public:

    DepartureCell();

    /**
     * @brief definition of the action to
     * perform when the cell is triggered
     */
    void performAction();

    /**
     * @brief check if a departure cell already exists
     * inside the given cells string
     *
     * @param stringLevel cells string representation of a level
     *
     * @return true if one departure cell already exists
     */
    bool authorizeAddAction(std::string stringLevel);
};
}

#endif
