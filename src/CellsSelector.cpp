/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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

#include "CellsTexturesManager.hpp"
#include "Cell.hpp"
#include "cells.hpp"

namespace memoris
{
namespace utils
{

class CellsSelector::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context),
        emptyCell(
            context,
            150.f,
            98.f,
            cells::EMPTY_CELL
        ),
        departureCell(
            context,
            150.f,
            148.f,
            cells::DEPARTURE_CELL
        ),
        arrivalCell(
            context,
            150.f,
            198.f,
            cells::ARRIVAL_CELL
        ),
        starCell(
            context,
            150.f,
            248.f,
            cells::STAR_CELL
        ),
        moreLifeCell(
            context,
            150.f,
            298.f,
            cells::MORE_LIFE_CELL
        ),
        lessLifeCell(
            context,
            150.f,
            348.f,
            cells::LESS_LIFE_CELL
        ),
        moreTimeCell(
            context,
            150.f,
            398.f,
            cells::MORE_TIME_CELL
        ),
        lessTimeCell(
            context,
            150.f,
            448.f,
            cells::LESS_TIME_CELL
        ),
        wallCell(
            context,
            150.f,
            498.f,
            cells::WALL_CELL
        ),
        stairsUpCell(
            context,
            150.f,
            548.f,
            cells::STAIRS_UP_CELL
        ),
        stairsDownCell(
            context,
            150.f,
            598.f,
            cells::STAIRS_DOWN_CELL
        ),
        horizontalMirrorCell(
            context,
            150.f,
            648.f,
            cells::HORIZONTAL_MIRROR_CELL
        ),
        verticalMirrorCell(
            context,
            150.f,
            698.f,
            cells::VERTICAL_MIRROR_CELL
        ),
        leftRotationCell(
            context,
            150.f,
            748.f,
            cells::LEFT_ROTATION_CELL
        ),
        rightRotationCell(
            context,
            150.f,
            798.f,
            cells::RIGHT_ROTATION_CELL
        ),
        elevatorUpCell(
            context,
            200.f,
            98.f,
            cells::ELEVATOR_UP_CELL
        ),
        elevatorDownCell(
            context,
            200.f,
            148.f,
            cells::ELEVATOR_DOWN_CELL
        ),
        diagonalCell(
            context,
            200.f,
            198.f,
            cells::DIAGONAL_CELL
        ),
        quarterRotationCell(
            context,
            200.f,
            248.f,
            cells::QUARTER_ROTATION_CELL
        )
    {
        selectedCellImage.setTexture(
            context.getCellsTexturesManager().getTextureReferenceByCellType(
                cells::EMPTY_CELL
            )
        );

        constexpr float SELECTED_CELL_IMAGE_HORIZONTAL_POSITION {150.f};
        constexpr float SELECTED_CELL_IMAGE_VERTICAL_POSITION {10.f};
        selectedCellImage.setPosition(
            SELECTED_CELL_IMAGE_HORIZONTAL_POSITION,
            SELECTED_CELL_IMAGE_VERTICAL_POSITION
        );
    }

    const utils::Context& context;

    entities::Cell emptyCell;
    entities::Cell departureCell;
    entities::Cell arrivalCell;
    entities::Cell starCell;
    entities::Cell moreLifeCell;
    entities::Cell lessLifeCell;
    entities::Cell moreTimeCell;
    entities::Cell lessTimeCell;
    entities::Cell wallCell;
    entities::Cell stairsUpCell;
    entities::Cell stairsDownCell;
    entities::Cell horizontalMirrorCell;
    entities::Cell verticalMirrorCell;
    entities::Cell leftRotationCell;
    entities::Cell rightRotationCell;
    entities::Cell elevatorUpCell;
    entities::Cell elevatorDownCell;
    entities::Cell diagonalCell;
    entities::Cell quarterRotationCell;

    char selectedCellType {'e'};

    sf::Sprite selectedCellImage;
};

/**
 *
 */
CellsSelector::CellsSelector(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
CellsSelector::~CellsSelector() = default;

/**
 *
 */
void CellsSelector::display() const &
{
    const auto& context = impl->context;

    impl->emptyCell.displayWithMouseHover(context);
    impl->departureCell.displayWithMouseHover(context);
    impl->arrivalCell.displayWithMouseHover(context);
    impl->starCell.displayWithMouseHover(context);
    impl->moreLifeCell.displayWithMouseHover(context);
    impl->lessLifeCell.displayWithMouseHover(context);
    impl->moreTimeCell.displayWithMouseHover(context);
    impl->lessTimeCell.displayWithMouseHover(context);
    impl->wallCell.displayWithMouseHover(context);
    impl->stairsUpCell.displayWithMouseHover(context);
    impl->stairsDownCell.displayWithMouseHover(context);
    impl->horizontalMirrorCell.displayWithMouseHover(context);
    impl->verticalMirrorCell.displayWithMouseHover(context);
    impl->leftRotationCell.displayWithMouseHover(context);
    impl->rightRotationCell.displayWithMouseHover(context);
    impl->elevatorUpCell.displayWithMouseHover(context);
    impl->elevatorDownCell.displayWithMouseHover(context);
    impl->diagonalCell.displayWithMouseHover(context);
    impl->quarterRotationCell.displayWithMouseHover(context);

    context.getSfmlWindow().draw(impl->selectedCellImage);
}

/**
 *
 */
void CellsSelector::selectCell(const char& selectedCellType) const &
{
    impl->selectedCellImage.setTexture(
        impl->context.getCellsTexturesManager().getTextureReferenceByCellType(
            selectedCellType
        )
    );

    impl->selectedCellType = selectedCellType;
}

/**
 *
 */
const char& CellsSelector::getSelectedCellType() const & noexcept
{
    return impl->selectedCellType;
}

/**
 *
 */
const char CellsSelector::getMouseHoverCellType() const &
{
    if (impl->emptyCell.isMouseHover())
    {
        return cells::EMPTY_CELL;
    }
    else if (impl->departureCell.isMouseHover())
    {
        return cells::DEPARTURE_CELL;
    }
    else if (impl->arrivalCell.isMouseHover())
    {
        return cells::ARRIVAL_CELL;
    }
    else if (impl->starCell.isMouseHover())
    {
        return cells::STAR_CELL;
    }
    else if (impl->moreLifeCell.isMouseHover())
    {
        return cells::MORE_LIFE_CELL;
    }
    else if (impl->lessLifeCell.isMouseHover())
    {
        return cells::LESS_LIFE_CELL;
    }
    else if (impl->moreTimeCell.isMouseHover())
    {
        return cells::MORE_TIME_CELL;
    }
    else if (impl->lessTimeCell.isMouseHover())
    {
        return cells::LESS_TIME_CELL;
    }
    else if (impl->wallCell.isMouseHover())
    {
        return cells::WALL_CELL;
    }
    else if (impl->stairsUpCell.isMouseHover())
    {
        return cells::STAIRS_UP_CELL;
    }
    else if (impl->stairsDownCell.isMouseHover())
    {
        return cells::STAIRS_DOWN_CELL;
    }
    else if (impl->horizontalMirrorCell.isMouseHover())
    {
        return cells::HORIZONTAL_MIRROR_CELL;
    }
    else if (impl->verticalMirrorCell.isMouseHover())
    {
        return cells::VERTICAL_MIRROR_CELL;
    }
    else if (impl->leftRotationCell.isMouseHover())
    {
        return cells::LEFT_ROTATION_CELL;
    }
    else if (impl->rightRotationCell.isMouseHover())
    {
        return cells::RIGHT_ROTATION_CELL;
    }
    else if (impl->elevatorUpCell.isMouseHover())
    {
        return cells::ELEVATOR_UP_CELL;
    }
    else if (impl->elevatorDownCell.isMouseHover())
    {
        return cells::ELEVATOR_DOWN_CELL;
    }
    else if (impl->diagonalCell.isMouseHover())
    {
        return cells::DIAGONAL_CELL;
    }
    else if (impl->quarterRotationCell.isMouseHover())
    {
        return cells::QUARTER_ROTATION_CELL;
    }

    return cells::NO_CELL;
}

}
}
