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
 * @file StairsCellsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "StairsCellsTutorialFrame.hpp"

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
StairsCellsTutorialFrame::StairsCellsTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        580.f,
        270.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto moveUp = std::make_unique<sf::Text>();
    auto moveDown = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();

    auto moveUpCell = std::make_unique<sf::Sprite>();
    auto moveDownCell = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "While playing, you can move from one floor to another using "
        "the stairs cells."
    );

    secondLine->setString(
        "There are two stairs cells: the one that moves you up and the "
        "one that moves "
    );

    thirdLine->setString(
        "you down."
    );

    fourthLine->setString(
        "The move up cell and move down cell always come together on "
        "a map. There is "
    );

    fifthLine->setString(
        "always a move up cell under a move down cell."
    );

    moveUp->setString("Move up cell");
    moveDown->setString("Move down cell");

    moveUpCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::STAIRS_UP_CELL
        )
    );

    moveDownCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::STAIRS_DOWN_CELL
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
        fourthLine
    );

    applyPropertiesToText(
        context,
        fifthLine
    );

    applyPropertiesToText(
        context,
        moveUp
    );

    applyPropertiesToText(
        context,
        moveDown
    );

    firstLine->setPosition(
        20.f,
        210.f
    );

    secondLine->setPosition(
        20.f,
        230.f
    );

    thirdLine->setPosition(
        20.f,
        250.f
    );

    fourthLine->setPosition(
        20.f,
        400.f
    );

    fifthLine->setPosition(
        20.f,
        420.f
    );

    moveUp->setPosition(
        110.f,
        360.f
    );

    moveDown->setPosition(
        310.f,
        360.f
    );

    moveUpCell->setPosition(
        130.f,
        300.f
    );

    moveDownCell->setPosition(
        335.f,
        300.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(moveUp));
    insertItem(std::move(moveDown));
    insertItem(std::move(moveUpCell));
    insertItem(std::move(moveDownCell));
}

}
}
