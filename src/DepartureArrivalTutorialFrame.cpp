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
 * @file DepartureArrivalTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DepartureArrivalTutorialFrame.hpp"

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
DepartureArrivalTutorialFrame::DepartureArrivalTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        100.f,
        610.f,
        400.f
    )
{
    auto firstLine = std::make_unique<sf::Text>(); // std::unique_ptr<sf::Text>
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto sixthLine = std::make_unique<sf::Text>();
    auto departureCellText = std::make_unique<sf::Text>();
    auto arrivalCellText = std::make_unique<sf::Text>();
    auto emptyCellText = std::make_unique<sf::Text>();
    auto wallCellText = std::make_unique<sf::Text>();

    auto departureCell = std::make_unique<sf::Sprite>();
    // std::unique_ptr<sf::Sprite>
    auto arrivalCell = std::make_unique<sf::Sprite>();
    auto emptyCell = std::make_unique<sf::Sprite>();
    auto wallCell = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "Your goal during one level is to move a pin from the departure "
        "cell to the "
    );

    secondLine->setString(
        "arrival cell. When the level starts, the player pin position "
        "is set on the "
    );

    thirdLine->setString(
        "departure cell."
    );

    fourthLine->setString(
        "Use the keyboard arrows keys to move from one cell to another."
        "You can move up, "
    );

    fifthLine->setString(
        "downm, on the left and on the right. You can move on any cell "
        "that is empty."
    );

    sixthLine->setString(
        "Of course, you cannot move on a wall cell."
    );

    departureCellText->setString("Departure cell");
    arrivalCellText->setString("Arrival cell");
    emptyCellText->setString("Empty cell");
    wallCellText->setString("Wall cell");

    departureCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::DEPARTURE_CELL
        )
    );

    arrivalCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::ARRIVAL_CELL
        )
    );

    emptyCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::EMPTY_CELL
        )
    );

    wallCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::WALL_CELL
        )
    );

    firstLine->setPosition(
        20.f,
        110.f
    );

    secondLine->setPosition(
        20.f,
        130.f
    );

    thirdLine->setPosition(
        20.f,
        150.f
    );

    fourthLine->setPosition(
        20.f,
        300.f
    );

    fifthLine->setPosition(
        20.f,
        320.f
    );

    sixthLine->setPosition(
        20.f,
        340.f
    );

    departureCell->setPosition(
        100.f,
        200.f
    );

    arrivalCell->setPosition(
        450.f,
        200.f
    );

    emptyCell->setPosition(
        100.f,
        390.f
    );

    wallCell->setPosition(
        450.f,
        390.f
    );

    departureCellText->setPosition(
        70.f,
        260.f
    );

    arrivalCellText->setPosition(
        435.f,
        260.f
    );

    emptyCellText->setPosition(
        85.f,
        450.f
    );

    wallCellText->setPosition(
        445.f,
        450.f
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
        sixthLine
    );

    applyPropertiesToText(
        context,
        departureCellText
    );

    applyPropertiesToText(
        context,
        arrivalCellText
    );

    applyPropertiesToText(
        context,
        emptyCellText
    );

    applyPropertiesToText(
        context,
        wallCellText
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(sixthLine));
    insertItem(std::move(departureCell));
    insertItem(std::move(arrivalCell));
    insertItem(std::move(emptyCell));
    insertItem(std::move(wallCell));
    insertItem(std::move(departureCellText));
    insertItem(std::move(arrivalCellText));
    insertItem(std::move(emptyCellText));
    insertItem(std::move(wallCellText));
}

}
}
