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
 * @file CellsFilter.hpp
 * @brief filter the cells when added
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CELLS_FILTER
#define DEF_CELLS_FILTER

#include <string>

namespace utils
{
class CellsFilter
{

public:

    /**
     * @brief certifies if a given cell can be
     * added on a given level according to properties
     *
     * @param levelCellsString string representation of the level
     * @param cellStringRepresentation string representation of the cell to add
     * @param isOnFirstFloor true if the cell has to be added on the first floor
     *
     * @return true if the cell can be added
     */
    static bool canBeAdded(
        std::string levelCellsString,
        std::string cellStringRepresentation,
        bool isOnFirstFloor
    );
};
}

#endif
