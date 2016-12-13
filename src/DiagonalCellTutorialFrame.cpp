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
 * @file DiagonalCellTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DiagonalCellTutorialFrame.hpp"

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
DiagonalCellTutorialFrame::DiagonalCellTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        600.f,
        150.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto sixthLine = std::make_unique<sf::Text>();

    firstLine->setString(
        "Another event is the diagonal cell. When you find this event, "
        "the position of "
    );

    secondLine->setString(
        "every cells change. The 64 cells of the top left corner comes "
        "to the bottom right "
    );

    thirdLine->setString(
        "corner. That means the cell that was at the top left corner is "
        "now part of the center's "
    );

    fourthLine->setString(
        "four cells. Conversely, the 64 cells that were at the bottom "
        "right corner are now at "
    );

    fifthLine->setString(
        "top left one. The same for the top right corner cells : their "
        "positions are inverted "
    );

    sixthLine->setString(
        "with the 64 cells at the bottom left side of the map."
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
        270.f
    );

    fifthLine->setPosition(
        20.f,
        290.f
    );

    sixthLine->setPosition(
        20.f,
        310.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(sixthLine));
}

}
}
