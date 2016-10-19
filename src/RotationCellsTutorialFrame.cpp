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
 * @file RotationCellsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "RotationCellsTutorialFrame.hpp"

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
RotationCellsTutorialFrame::RotationCellsTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        550.f,
        200.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto leftRotationLine = std::make_unique<sf::Text>();
    auto rightRotationLine = std::make_unique<sf::Text>();

    auto leftRotationCell = std::make_unique<sf::Sprite>();
    auto rightRotationCell = std::make_unique<sf::Sprite>();

    leftRotationCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::LEFT_ROTATION_CELL
        )
    );

    rightRotationCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::RIGHT_ROTATION_CELL
        )
    );

    firstLine->setString(
        "There are two rotation cells: the one that rotates the "
        "cells on the left, "
    );

    secondLine->setString(
        "the one that rotates the cells on the right. As mirror "
        "cells, only the current "
    );

    thirdLine->setString(
        "floor cells move."
    );

    fourthLine->setString(
        "The game starts when you press the Enter key."
    );

    leftRotationLine->setString("Left rotation");
    rightRotationLine->setString("Right rotation");

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
        leftRotationLine
    );

    applyPropertiesToText(
        context,
        rightRotationLine
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

    leftRotationCell->setPosition(
        120.f,
        280.f
    );

    rightRotationCell->setPosition(
        320.f,
        280.f
    );

    leftRotationLine->setPosition(
        110.f,
        335.f
    );

    rightRotationLine->setPosition(
        310.f,
        335.f
    );

    fourthLine->setPosition(
        20.f,
        360.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(leftRotationLine));
    insertItem(std::move(rightRotationLine));
    insertItem(std::move(leftRotationCell));
    insertItem(std::move(rightRotationCell));
    insertItem(std::move(fourthLine));
}

}
}
