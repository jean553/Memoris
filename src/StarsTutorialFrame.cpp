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
 * @file StarsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "StarsTutorialFrame.hpp"

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
StarsTutorialFrame::StarsTutorialFrame(const utils::Context& context) : 
    TutorialFrame(
        100.f,
        560.f,
        280.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto sixthLine = std::make_unique<sf::Text>();
    auto seventhLine = std::make_unique<sf::Text>();

    auto starCell = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "Good ! You have just won the first Memoris level. "
    );

    secondLine->setString(
        "Your goal is not only going from the departure cell "
        "to the arrival one."
    );

    thirdLine->setString(
        "Before going to the arrival, you have to take all the stars "
        "on the map."
    );

    fourthLine->setString(
        "Each time you go on a star cell, you pick the star on this "
        "cell. You have to "
    );

    fifthLine->setString(
        "take all the stars to finish the level. If you go on the "
        "arrival call without "
    );

    sixthLine->setString(
        "having them all, nothing will happen and you will have to "
        "continue to play."
    );

    seventhLine->setString("Star cell");

    starCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::STAR_CELL
        )
    );

    firstLine->setPosition(
        20.f,
        120.f
    );

    secondLine->setPosition(
        20.f,
        160.f
    );

    thirdLine->setPosition(
        20.f,
        180.f
    );

    fourthLine->setPosition(
        20.f,
        200.f
    );

    fifthLine->setPosition(
        20.f,
        220.f
    );

    sixthLine->setPosition(
        20.f,
        240.f
    );

    seventhLine->setPosition(
        270.f,
        340.f
    );

    starCell->setPosition(
        275.f,
        280.f
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
        seventhLine
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(sixthLine));
    insertItem(std::move(seventhLine));
    insertItem(std::move(starCell));
}

}
}
