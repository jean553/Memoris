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
 * @file LimitTimeTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LimitTimeTutorialFrame.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
LimitTimeTutorialFrame::LimitTimeTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        100.f,
        650.f,
        200.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto sixthLine = std::make_unique<sf::Text>();
    auto seventhLine = std::make_unique<sf::Text>();

    firstLine->setString(
        "Your goal is now to go from the departure to the "
        "arrival. But the time "
    );

    secondLine->setString(
        "to finish the level is limited. The time left is "
        "displayed at the top "
    );

    thirdLine->setString(
        "left corner of the screen. During the watching period, "
        "this value does not "
    );

    fourthLine->setString(
        "change and you can take not of the allowed time you have "
        "to finish the level."
    );

    fifthLine->setString(
        "As you can see for this first level, you will see the "
        "cells during 6 seconds "
    );

    sixthLine->setString(
        "and you have to finish the level in 10 minutes. Easy, "
        "isn't it ? :)"
    );

    seventhLine->setString(
        "The level starts immediately after you press the Enter "
        "key. Good luck !"
    );

    firstLine->setPosition(
        20.f,
        120.f
    );

    secondLine->setPosition(
        20.f,
        140.f
    );

    thirdLine->setPosition(
        20.f,
        160.f
    );

    fourthLine->setPosition(
        20.f,
        180.f
    );

    fifthLine->setPosition(
        20.f,
        200.f
    );

    sixthLine->setPosition(
        20.f,
        220.f
    );

    seventhLine->setPosition(
        20.f,
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
}

}
}
