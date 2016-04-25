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
 * @file CellsFilter.cpp
 * @brief filter the cells when added
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellsFilter.hpp"
#include "CellsUtils.hpp"

using namespace utils;

bool CellsFilter::canBeAdded(
    std::string levelCellsString,
    std::string cellStringRepresentation,
    bool isOnFirstFloor
)
{
    // only one departure and arrival cell
    if (
        cellStringRepresentation == "DP" ||
        cellStringRepresentation == "AC"
    )
    {
        return !utils::CellsUtils::isCellAlreadyInLevel(
                   levelCellsString,
                   cellStringRepresentation
               );
    }

    // the floor down cell is not allowed on the first floor
    if (
        cellStringRepresentation == "FD"
    )
    {
        return !isOnFirstFloor;
    }

    return true;
}
