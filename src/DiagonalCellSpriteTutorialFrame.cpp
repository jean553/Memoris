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
 * @file DiagonalCellSpriteTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DiagonalCellSpriteTutorialFrame.hpp"

#include "Context.hpp"
#include "CellsTexturesManager.hpp"
#include "cells.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
DiagonalCellSpriteTutorialFrame::DiagonalCellSpriteTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        330.f,
        150.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();

    auto diagonalCell = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "The diagonal effect cell is the following cell :"
    );

    secondLine->setString(
        "The game starts when you press Enter."
    );

    diagonalCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::DIAGONAL_CELL
        )
    );

    applyPropertiesToText(
        context,
        firstLine
    );

    applyPropertiesToText(
        context,
        secondLine
    );

    firstLine->setPosition(
        20.f,
        210.f
    );

    diagonalCell->setPosition(
        160.f,
        250.f
    );

    secondLine->setPosition(
        20.f,
        310.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(diagonalCell));
}

}
}
