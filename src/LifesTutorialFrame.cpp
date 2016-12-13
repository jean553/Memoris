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
 * @file LifesTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LifesTutorialFrame.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

LifesTutorialFrame::LifesTutorialFrame(const utils::Context& context) :
    TutorialFrame(
        200.f,
        600.f,
        110.f
    )
{
    auto firstLine = std::make_unique<sf::Text>(); // std::unique_ptr<sf::Text>
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();

    firstLine->setString(
        "When a serie starts, you get a specific amount of lifes. This "
        "default amount "
    );

    secondLine->setString(
        "of lifes depends of the serie and can be different from one serie "
        "to another one."
    );

    thirdLine->setString(
        "Throughout the levels, your amount of lifes change if you take "
        "life cells or "
    );

    fourthLine->setString(
        "dead cells."
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
