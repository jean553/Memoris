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
 * @file CellsSelector.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellsSelector.hpp"

#include "cells.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
CellsSelector::CellsSelector(const std::shared_ptr<utils::Context>& context) :
    emptyCell(
        context,
        320.f,
        98.f,
        cells::EMPTY_CELL
    ),
    departureCell(
        context,
        320.f,
        148.f,
        cells::DEPARTURE_CELL
    ),
    arrivalCell(
        context,
        320.f,
        198.f,
        cells::ARRIVAL_CELL
    ),
    starCell(
        context,
        320.f,
        248.f,
        cells::STAR_CELL
    ),
    moreLifeCell(
        context,
        320.f,
        298.f,
        cells::MORE_LIFE_CELL
    ),
    lessLifeCell(
        context,
        320.f,
        348.f,
        cells::LESS_LIFE_CELL
    ),
    moreTimeCell(
        context,
        320.f,
        398.f,
        cells::MORE_TIME_CELL
    ),
    lessTimeCell(
        context,
        320.f,
        448.f,
        cells::LESS_TIME_CELL
    ),
    wallCell(
        context,
        320.f,
        498.f,
        cells::WALL_CELL
    ),
    stairsUpCell(
        context,
        320.f,
        548.f,
        cells::STAIRS_UP_CELL
    ),
    stairsDownCell(
        context,
        320.f,
        598.f,
        cells::STAIRS_DOWN_CELL
    ),
    horizontalMirrorCell(
        context,
        320.f,
        648.f,
        cells::HORIZONTAL_MIRROR_CELL
    ),
    verticalMirrorCell(
        context,
        320.f,
        698.f,
        cells::VERTICAL_MIRROR_CELL
    ),
    leftRotationCell(
        context,
        320.f,
        748.f,
        cells::LEFT_ROTATION_CELL
    ),
    rightRotationCell(
        context,
        320.f,
        798.f,
        cells::RIGHT_ROTATION_CELL
    )
{
}

/**
 *
 */
void CellsSelector::display(const std::shared_ptr<utils::Context>& context)
{
    emptyCell.displayWithMouseHover(context);
    departureCell.displayWithMouseHover(context);
    arrivalCell.displayWithMouseHover(context);
    starCell.displayWithMouseHover(context);
    moreLifeCell.displayWithMouseHover(context);
    lessLifeCell.displayWithMouseHover(context);
    moreTimeCell.displayWithMouseHover(context);
    lessTimeCell.displayWithMouseHover(context);
    wallCell.displayWithMouseHover(context);
    stairsUpCell.displayWithMouseHover(context);
    stairsDownCell.displayWithMouseHover(context);
    horizontalMirrorCell.displayWithMouseHover(context);
    verticalMirrorCell.displayWithMouseHover(context);
    leftRotationCell.displayWithMouseHover(context);
    rightRotationCell.displayWithMouseHover(context);
}

}
}
