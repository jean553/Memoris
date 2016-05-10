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
 * @file ArrivalCell.cpp
 * @brief arrival cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ArrivalCell.hpp"
#include "CellsUtils.hpp"

using namespace entities;

const std::string ArrivalCell::ARRIVAL_CELL_PICTURE_PATH = "res/cells/arrival.png";

/**
 *
 */
ArrivalCell::ArrivalCell() : Cell("AC")
{
    setPicturePath(ARRIVAL_CELL_PICTURE_PATH);
}

/**
 *
 */
void ArrivalCell::performAction(utils::GameContext* pGameContext)
{
    /* finish the game */
    pGameContext->setTerminateGame(true);
}
