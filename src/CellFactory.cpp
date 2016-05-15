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
 * @file CellFactory.cpp
 * @brief factory that generates the cells
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellFactory.hpp"
#include "CellsFileRepresentations.hpp"

using namespace factories;

const std::string CellFactory::DEPARTURE_CELL_PICTURE_PATH = "res/cells/departure.png";
const std::string CellFactory::ARRIVAL_CELL_PICTURE_PATH = "res/cells/arrival.png";
const std::string CellFactory::STAR_CELL_PICTURE_PATH = "res/cells/star.png";
const std::string CellFactory::EMPTY_CELL_PICTURE_PATH = "res/cells/empty.png";

entities::Cell* CellFactory::getCellPointerByStringName(const std::string& stringCell)
{
    /* TODO: very bad, but the pointer will be refactored anyway... */
    entities::Cell* pCell = new entities::Cell(stringCell);
    pCell->IN_FILE_REPRESENTATION = stringCell;

    if (stringCell == constants::CellsFileRepresentations::DEPARTURE_CELL)
    {
        pCell->setPicturePath(DEPARTURE_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::ARRIVAL_CELL)
    {
        pCell->setPicturePath(ARRIVAL_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::STAR_CELL)
    {
        pCell->setPicturePath(STAR_CELL_PICTURE_PATH);
    }
    else
    {

        /* force the cell as an empty cell */
        pCell->IN_FILE_REPRESENTATION = "EC";

        pCell->setPicturePath(EMPTY_CELL_PICTURE_PATH);
    }

    return pCell;
}
