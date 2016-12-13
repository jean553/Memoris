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
 * @file FloorsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FloorsTutorialFrame.hpp"

#include "Context.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
FloorsTutorialFrame::FloorsTutorialFrame(const utils::Context& context) :
    TutorialFrame(
        200.f,
        650.f,
        100.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();

    firstLine->setString(
        "One level can contain many floors. Each floor is on cells "
        "map. You have to "
    );

    secondLine->setString(
        "use the stairs cells to go up (or go down), between the "
        "floors. During the "
    );

    thirdLine->setString(
        "watching period, every floors are displayed one by one."
        "The floors are displayed "
    );

    fourthLine->setString(
        "from the first one to the highest one."
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

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
}

}
}
