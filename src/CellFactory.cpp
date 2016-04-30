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
#include "EmptyCell.hpp"
#include "DepartureCell.hpp"
#include "ArrivalCell.hpp"
#include "LifeCell.hpp"
#include "DamageCell.hpp"
#include "ElevatorDownCell.hpp"
#include "ElevatorUpCell.hpp"
#include "FloorDownCell.hpp"
#include "FloorUpCell.hpp"
#include "HorizontalMirrorCell.hpp"
#include "VerticalMirrorCell.hpp"
#include "LessTimeCell.hpp"
#include "MoreTimeCell.hpp"
#include "WallCell.hpp"
#include "StarCell.hpp"
#include "QuarterHalfRotateCell.hpp"
#include "QuarterLeftRotateCell.hpp"
#include "QuarterRightRotateCell.hpp"
#include "StarCell.hpp"

using namespace factories;

entities::Cell* CellFactory::getCellPointerByStringName(const std::string& stringCell)
{
    /* TODO: should use constant strings instead of string literals... */
    if (stringCell == "DP")
    {
        return new entities::DepartureCell();
    }
    else if (stringCell == "AC")
    {
        return new entities::ArrivalCell();
    }
    else if (stringCell == "LC")
    {
        return new entities::LifeCell();
    }
    else if (stringCell == "ED")
    {
        return new entities::ElevatorDownCell();
    }
    else if (stringCell == "EU")
    {
        return new entities::ElevatorUpCell();
    }
    else if (stringCell == "FD")
    {
        return new entities::FloorDownCell();
    }
    else if (stringCell == "FU")
    {
        return new entities::FloorUpCell();
    }
    else if (stringCell == "HM")
    {
        return new entities::HorizontalMirrorCell();
    }
    else if (stringCell == "LT")
    {
        return new entities::LessTimeCell();
    }
    else if (stringCell == "MT")
    {
        return new entities::MoreTimeCell();
    }
    else if (stringCell == "QH")
    {
        return new entities::QuarterHalfRotateCell();
    }
    else if (stringCell == "QL")
    {
        return new entities::QuarterLeftRotateCell();
    }
    else if (stringCell == "QR")
    {
        return new entities::QuarterRightRotateCell();
    }
    else if (stringCell == "VM")
    {
        return new entities::VerticalMirrorCell();
    }
    else if (stringCell == "WC")
    {
        return new entities::WallCell();
    }
    else if (stringCell == "SC")
    {
        return new entities::StarCell();
    }
    else if (stringCell == "DC")
    {
        return new entities::DamageCell();
    }
    else
    {
        return new entities::EmptyCell();
    }
}
