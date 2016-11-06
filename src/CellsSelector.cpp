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

    Impl(const utils::Context& context)
    {
        selectedCellImage.setTexture(
            context.getCellsTexturesManager().getTextureReferenceByCellType(
                cells::EMPTY_CELL
            )
        );
    }

    std::vector<entities::Cell> cells;

    char selectedCellType {'e'};

    sf::Sprite selectedCellImage;
};

/**
 *
 */
CellsSelector::CellsSelector(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    constexpr float FIRST_COLUMN_CELLS_HORIZONTAL_POSITION {150.f};
    constexpr float SECOND_COLUMN_CELLS_HORIZONTAL_POSITION {200.f};

    /* initialized here and not the implementation because needs access to
       constant */
    impl->cells =
    {
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            98.f,
            cells::EMPTY_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            148.f,
            cells::DEPARTURE_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            198.f,
            cells::ARRIVAL_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            248.f,
            cells::STAR_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            298.f,
            cells::MORE_LIFE_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            348.f,
            cells::LESS_LIFE_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            398.f,
            cells::MORE_TIME_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            448.f,
            cells::LESS_TIME_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            498.f,
            cells::WALL_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            548.f,
            cells::STAIRS_UP_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            598.f,
            cells::STAIRS_DOWN_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            648.f,
            cells::HORIZONTAL_MIRROR_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            698.f,
            cells::VERTICAL_MIRROR_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            748.f,
            cells::LEFT_ROTATION_CELL
        ),
        entities::Cell(
            context,
            FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
            798.f,
            cells::RIGHT_ROTATION_CELL
        ),
        entities::Cell(
            context,
            SECOND_COLUMN_CELLS_HORIZONTAL_POSITION,
            98.f,
            cells::ELEVATOR_UP_CELL
        ),
        entities::Cell(
            context,
            SECOND_COLUMN_CELLS_HORIZONTAL_POSITION,
            148.f,
            cells::ELEVATOR_DOWN_CELL
        ),
        entities::Cell(
            context,
            SECOND_COLUMN_CELLS_HORIZONTAL_POSITION,
            198.f,
            cells::DIAGONAL_CELL
        ),
        entities::Cell(
            context,
            SECOND_COLUMN_CELLS_HORIZONTAL_POSITION,
            248.f,
            cells::QUARTER_ROTATION_CELL
        )
    };

    impl->selectedCellImage.setPosition(
        FIRST_COLUMN_CELLS_HORIZONTAL_POSITION,
        10.f
    );
}

/**
 *
 */
CellsSelector::~CellsSelector() noexcept = default;

/**
 *
 */
void CellsSelector::display(const utils::Context& context) &
{
    /* the STL for_each is the best solution here as we simply execute a
       method for the whole container items; do not deduce constant reference
       because we maybe modify the cell */
    std::for_each(
        impl->cells.begin(),
        impl->cells.end(),
        [&context](auto& cell) // entities::Cell&
    {
        cell.displayWithMouseHover(context);
    }
    );

    context.getSfmlWindow().draw(impl->selectedCellImage);
}

/**
 *
 */
void CellsSelector::selectCell(const utils::Context& context) &
{
    /* we use a const_iterator here to automatically return a reference to
       a constant Cell object and because we want use break; and continue;
       during the iteration */
    for(
        std::vector<entities::Cell>::const_iterator iterator =
        impl->cells.begin();
        iterator != impl->cells.end();
        iterator++
    )
    {
        if (!iterator->isMouseHover())
        {
            continue;
        }

        impl->selectedCellType = iterator->getType();

        impl->selectedCellImage.setTexture(
            context.getCellsTexturesManager().getTextureReferenceByCellType(
                impl->selectedCellType
            )
        );

        break;
    }
}

/**
 *
 */
const char& CellsSelector::getSelectedCellType() const & noexcept
{
    return impl->selectedCellType;
}

}
}
