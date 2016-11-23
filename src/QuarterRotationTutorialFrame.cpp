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
 * @file QuarterRotationTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "QuarterRotationTutorialFrame.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
QuarterRotationTutorialFrame::QuarterRotationTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        100.f,
        610.f,
        90.f
    )
{
    auto firstLine = std::make_unique<sf::Text>(); // std::unique_ptr<sf::Text>
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();

    firstLine->setString(
        "One floor is divided in four quarters. Each quarter contains 64 "
        "cells. There are "
    );

    secondLine->setString(
        "the top left quarter (64 cells at the top left corner of the map), "
        "the top right quarter, "
    );

    thirdLine->setString(
        "the bottom left quarter and the bottom right quarter."
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

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
}

}
}
