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
 * @file CellsFileRepresentations.hpp
 * @brief string representation of the cells
 * @package constants
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CELLS_FILE_REPRESENTATIONS
#define DEF_CELLS_FILE_REPRESENTATIONS

#include <string>

namespace constants
{
class CellsFileRepresentations
{
public:
    static const std::string DEPARTURE_CELL;
    static const std::string ARRIVAL_CELL;
    static const std::string STAR_CELL;
    static const std::string EMPTY_CELL;
};
}

#endif
