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
CellsSelector::CellsSelector(const std::shared_ptr<utils::Context>& context)
{
    /* load the SFML textures and set them as sprite textures */

    emptyCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::EMPTY_CELL
        )
    );

    /* set the sprites positions */

    emptyCell.setPosition(
        320.f,
        98.f
    );
}

/**
 *
 */
void CellsSelector::display(const std::shared_ptr<utils::Context>& context)
{
    context->getSfmlWindow().draw(emptyCell);
}

}
}
