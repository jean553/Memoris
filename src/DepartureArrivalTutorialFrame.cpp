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
        190.f
    )
{
    auto firstLine = std::make_unique<sf::Text>(); // std::unique_ptr<sf::Text>
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto departureCellText = std::make_unique<sf::Text>();

    auto departureCell = std::make_unique<sf::Sprite>();
    // std::unique_ptr<sf::Sprite>

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

    departureCellText->setString("Departure cell");

    departureCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::DEPARTURE_CELL
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

    departureCell->setPosition(
        100.f,
        200.f
    );

    departureCellText->setPosition(
        70.f,
        260.f
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
        departureCellText
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(departureCell));
    insertItem(std::move(departureCellText));
}

}
}
