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
const std::string CellFactory::LIFE_CELL_PICTURE_PATH = "res/cells/life.png";
const std::string CellFactory::DAMAGE_CELL_PICTURE_PATH = "res/cells/damage.png";
const std::string CellFactory::WALL_CELL_PICTURE_PATH = "res/cells/wall.png";
const std::string CellFactory::NULL_CELL_PICTURE_PATH = "res/cells/null.png";
const std::string CellFactory::MORE_TIME_CELL_PICTURE_PATH = "res/cells/more_time.png";
const std::string CellFactory::LESS_TIME_CELL_PICTURE_PATH = "res/cells/less_time.png";
const std::string CellFactory::LIGHT_CELL_PICTURE_PATH = "res/cells/light.png";

entities::Cell CellFactory::getCellPointerByStringName(const std::string& stringCell)
{
    entities::Cell cell;
    cell.setStringRepresentation(stringCell);

    if (stringCell == constants::CellsFileRepresentations::DEPARTURE_CELL)
    {
        cell.setPicturePath(DEPARTURE_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::ARRIVAL_CELL)
    {
        cell.setPicturePath(ARRIVAL_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::STAR_CELL)
    {
        cell.setPicturePath(STAR_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::LIFE_CELL)
    {
        cell.setPicturePath(LIFE_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::DAMAGE_CELL)
    {
        cell.setPicturePath(DAMAGE_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::WALL_CELL)
    {
        cell.setPicturePath(WALL_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::NULL_CELL)
    {
        cell.setPicturePath(NULL_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::MORE_TIME_CELL)
    {
        cell.setPicturePath(MORE_TIME_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::LESS_TIME_CELL)
    {
        cell.setPicturePath(LESS_TIME_CELL_PICTURE_PATH);
    }
    else if (stringCell == constants::CellsFileRepresentations::LIGHT_CELL)
    {
        cell.setPicturePath(LIGHT_CELL_PICTURE_PATH);
    }
    else
    {
        /* force the cell as an empty cell */
        cell.setStringRepresentation(
            constants::CellsFileRepresentations::EMPTY_CELL
        );

        cell.setPicturePath(EMPTY_CELL_PICTURE_PATH);
    }

    return cell;
}
