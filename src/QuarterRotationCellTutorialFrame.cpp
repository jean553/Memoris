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
 * @file QuarterRotationCellTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "QuarterRotationCellTutorialFrame.hpp"

#include "Context.hpp"
#include "cells.hpp"
#include "CellsTexturesManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
QuarterRotationCellTutorialFrame::QuarterRotationCellTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        100.f,
        560.f,
        180.f
    )
{
    auto firstLine = std::make_unique<sf::Text>(); // std::unique_ptr<sf::Text>
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();

    auto quarterRotationCell = std::make_unique<sf::Sprite>();
    auto invertedQuarterRotationCell = std::make_unique<sf::Sprite>();

    quarterRotationCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::QUARTER_ROTATION_CELL
        )
    );

    invertedQuarterRotationCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::INVERTED_QUARTER_ROTATION_CELL
        )
    );

    firstLine->setString(
        "The two following cells are used to change the disposition of each "
        "quarter."
    );

    secondLine->setString(
        "During a clockwise rotation, the top left quarter becomes the top "
        "right one, "
    );

    thirdLine->setString(
        "the top right one becomes the bottom right one... etc..."
    );

    fourthLine->setString(
        "Press Enter to start the game."
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
        240.f
    );

    quarterRotationCell->setPosition(
        140.f,
        180.f
    );

    invertedQuarterRotationCell->setPosition(
        340.f,
        180.f
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

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(quarterRotationCell));
    insertItem(std::move(invertedQuarterRotationCell));
}

}
}
