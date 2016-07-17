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

#include "Context.hpp"

using namespace factories;

memoris::entities::Cell CellFactory::getCellByStringName(
    const std::string& stringCell
)
{
    memoris::entities::Cell cell(memoris::utils::Context::get());
    cell.setStringRepresentation(stringCell);
    cell.setPicturePath("res/cells/" + stringCell + ".png");
    return cell;
}
