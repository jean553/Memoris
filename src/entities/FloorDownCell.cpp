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
 * @file FloorDownCell.cpp
 * @brief floor down cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@sdowninfo.com>
 */

#include "FloorDownCell.hpp"

using namespace entities;

const std::string FloorDownCell::FLOOR_DOWN_CELL_PICTURE_PATH = "res/cells/floor_down.png";

/**
 *
 */
FloorDownCell::FloorDownCell() : Cell("FD")
{
    setPicturePath(FLOOR_DOWN_CELL_PICTURE_PATH);
}

/**
 *
 */
void FloorDownCell::performAction()
{
}
