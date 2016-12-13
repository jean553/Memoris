/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file MirrorsCellsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MirrorsCellsTutorialFrame.hpp"

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
MirrorsCellsTutorialFrame::MirrorsCellsTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        530.f,
        200.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto horizontalLine = std::make_unique<sf::Text>();
    auto verticalLine = std::make_unique<sf::Text>();

    auto horizontalCell = std::make_unique<sf::Sprite>();
    auto verticalCell = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "There is a horizontal mirror effect cell, and a "
        "vertical mirror effect "
    );

    secondLine->setString(
        "cell."
    );

    thirdLine->setString(
        "The game starts when you press Enter."
    );

    horizontalLine->setString(
        "Horizontal mirror"
    );

    verticalLine->setString(
        "Vertical mirror"
    );

    horizontalCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::HORIZONTAL_MIRROR_CELL
        )
    );

    verticalCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::VERTICAL_MIRROR_CELL
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

    applyPropertiesToText(
        context,
        thirdLine
    );

    applyPropertiesToText(
        context,
        horizontalLine
    );

    applyPropertiesToText(
        context,
        verticalLine
    );

    firstLine->setPosition(
        20.f,
        210.f
    );

    secondLine->setPosition(
        20.f,
        230.f
    );

    horizontalCell->setPosition(
        120.f,
        260.f
    );

    verticalCell->setPosition(
        320.f,
        260.f
    );

    horizontalLine->setPosition(
        90.f,
        320.f
    );

    verticalLine->setPosition(
        295.f,
        320.f
    );

    thirdLine->setPosition(
        20.f,
        350.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(horizontalCell));
    insertItem(std::move(verticalCell));
    insertItem(std::move(horizontalLine));
    insertItem(std::move(verticalLine));
    insertItem(std::move(thirdLine));
}

}
}
