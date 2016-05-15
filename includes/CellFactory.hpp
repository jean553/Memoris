/**
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
 * Factory that generates the cells.
 *
 * @file CellFactory.hpp
 * @brief factory that generates the cells
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CELL_FACTORY
#define DEF_CELL_FACTORY

#include "Cell.hpp"

namespace factories
{
class CellFactory
{
public:

    static const std::string DEPARTURE_CELL_PICTURE_PATH;
    static const std::string ARRIVAL_CELL_PICTURE_PATH;
    static const std::string STAR_CELL_PICTURE_PATH;
    static const std::string EMPTY_CELL_PICTURE_PATH;

    /**
     * @brief returns a new cell
     * pointer according to the given
     * cell string
     *
     * @param stringCell       cell string representation
     *
     * @return cell pointer
     */
    static entities::Cell* getCellPointerByStringName(const std::string& stringCell);
};
}

#endif
