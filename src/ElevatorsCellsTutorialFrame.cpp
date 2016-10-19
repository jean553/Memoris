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
 * @file ElevatorsCellsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ElevatorsCellsTutorialFrame.hpp"

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
ElevatorsCellsTutorialFrame::ElevatorsCellsTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        500.f,
        190.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto moveUpLine = std::make_unique<sf::Text>();
    auto moveDownLine = std::make_unique<sf::Text>();

    auto moveUpCell = std::make_unique<sf::Sprite>();
    auto moveDownCell = std::make_unique<sf::Sprite>();

    moveUpCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::ELEVATOR_UP_CELL
        )
    );

    moveDownCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::ELEVATOR_DOWN_CELL
        )
    );

    firstLine->setString(
        "The two elevators cells :"
    );

    secondLine->setString(
        "The game starts when you press Enter."
    );

    moveUpLine->setString("Move up cell");
    moveDownLine->setString("Move down cell");

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
        moveUpLine
    );

    applyPropertiesToText(
        context,
        moveDownLine
    );

    firstLine->setPosition(
        20.f,
        210.f
    );

    secondLine->setPosition(
        20.f,
        350.f
    );

    moveUpCell->setPosition(
        120.f,
        260.f
    );

    moveDownCell->setPosition(
        320.f,
        260.f
    );

    moveUpLine->setPosition(
        100.f,
        320.f
    );

    moveDownLine->setPosition(
        290.f,
        320.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(moveUpLine));
    insertItem(std::move(moveDownLine));
    insertItem(std::move(moveUpCell));
    insertItem(std::move(moveDownCell));
}

}
}
