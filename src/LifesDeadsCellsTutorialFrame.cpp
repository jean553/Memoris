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
 * @file LifesDeadsCellsTutorialFrame.hpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LifesDeadsCellsTutorialFrame.hpp"

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
LifesDeadsCellsTutorialFrame::LifesDeadsCellsTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        500.f,
        230.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    // auto -> std::unique_ptr<sf::Text>
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto lifeCellLine = std::make_unique<sf::Text>();
    auto deadCellLine = std::make_unique<sf::Text>();

    auto lifeCell = std::make_unique<sf::Sprite>();
    auto deadCell = std::make_unique<sf::Sprite>();

    lifeCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::MORE_LIFE_CELL
        )
    );

    deadCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::LESS_LIFE_CELL
        )
    );

    firstLine->setString(
        "When you go on a life cell, you get one cell more."
        "When you go "
    );

    secondLine->setString(
        "a dead cell, you lose one life. You lose the whole "
        "serie when you "
    );

    thirdLine->setString(
        "lose all your lifes. In the same serie, the lifes "
        "amount is transfered "
    );

    fourthLine->setString(
        "from one level to another."
    );

    lifeCellLine->setString("Life cell");
    deadCellLine->setString("Dead cell");

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
        lifeCellLine
    );

    applyPropertiesToText(
        context,
        deadCellLine
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

    lifeCell->setPosition(
        120.f,
        320.f
    );

    deadCell->setPosition(
        320.f,
        320.f
    );

    lifeCellLine->setPosition(
        110.f,
        375.f
    );

    deadCellLine->setPosition(
        310.f,
        375.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(lifeCell));
    insertItem(std::move(deadCell));
    insertItem(std::move(lifeCellLine));
    insertItem(std::move(deadCellLine));
}

}
}
