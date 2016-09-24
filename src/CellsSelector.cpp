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

#include "cells.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
CellsSelector::CellsSelector(utils::Context& context)
{
    cells =
    {
        entities::Cell(
            context,
            320.f,
            98.f,
            cells::EMPTY_CELL
        ),
        entities::Cell(
            context,
            320.f,
            148.f,
            cells::DEPARTURE_CELL
        ),
        entities::Cell(
            context,
            320.f,
            198.f,
            cells::ARRIVAL_CELL
        ),
        entities::Cell(
            context,
            320.f,
            248.f,
            cells::STAR_CELL
        ),
        entities::Cell(
            context,
            320.f,
            298.f,
            cells::MORE_LIFE_CELL
        ),
        entities::Cell(
            context,
            320.f,
            348.f,
            cells::LESS_LIFE_CELL
        ),
        entities::Cell(
            context,
            320.f,
            398.f,
            cells::MORE_TIME_CELL
        ),
        entities::Cell(
            context,
            320.f,
            448.f,
            cells::LESS_TIME_CELL
        ),
        entities::Cell(
            context,
            320.f,
            498.f,
            cells::WALL_CELL
        ),
        entities::Cell(
            context,
            320.f,
            548.f,
            cells::STAIRS_UP_CELL
        ),
        entities::Cell(
            context,
            320.f,
            598.f,
            cells::STAIRS_DOWN_CELL
        ),
        entities::Cell(
            context,
            320.f,
            648.f,
            cells::HORIZONTAL_MIRROR_CELL
        ),
        entities::Cell(
            context,
            320.f,
            698.f,
            cells::VERTICAL_MIRROR_CELL
        ),
        entities::Cell(
            context,
            320.f,
            748.f,
            cells::LEFT_ROTATION_CELL
        ),
        entities::Cell(
            context,
            320.f,
            798.f,
            cells::RIGHT_ROTATION_CELL
        )
    };

    /* by default, the selected cell picture is the empty cell */
    selectedCellImage.setPosition(
        320.f,
        10.f
    );

    selectedCellImage.setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::EMPTY_CELL
        )
    );
}

/**
 *
 */
void CellsSelector::display(utils::Context& context)
{
    /* the STL for_each is the best solution here as we simply execute a
       method for the whole container items */
    std::for_each(
        cells.begin(),
        cells.end(),
        [&context](entities::Cell& cell)
    {
        cell.displayWithMouseHover(context);
    }
    );

    context.getSfmlWindow().draw(selectedCellImage);
}

/**
 *
 */
void CellsSelector::selectCell(utils::Context& context)
{
    /* we use a const_iterator here to automatically return a reference to
       a constant Cell object and because we want use break; and continue;
       during the iteration */
    for(
        std::vector<entities::Cell>::const_iterator iterator = cells.begin();
        iterator != cells.end();
        iterator++
    )
    {
        /* directly iterate if the current cell is not selected */
        if (!iterator->isMouseHover())
        {
            continue;
        }

        /* if the current cell is selected, save the type and directly leave
           the function */
        selectedCellType = iterator->getType();

        /* update the selected cell image according the cell the user has just
           selected */
        selectedCellImage.setTexture(
            context.getCellsTexturesManager().getTextureReferenceByCellType(
                selectedCellType
            )
        );

        break;
    }
}

/**
 *
 */
const char& CellsSelector::getSelectedCellType() const
{
    return selectedCellType;
}

}
}
