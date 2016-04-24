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
 * @file CellsUtils.hpp
 * @brief utils methods for cells management
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CELLS_UTILS
#define DEF_CELLS_UTILS

#include <string>

namespace utils
{
class CellsUtils
{
public:

    /**
     * @brief checks if the given cell string is
     * already inside the level cells string
     *
     * @param cells level cells string
     * @param cell cell string
     *
     * @return true if the cell is already
     * inside the cells of the level
     */
    static bool isCellAlreadyInLevel(
        std::string cells,
        std::string cell
    );
};
}

#endif
