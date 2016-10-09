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
 * @file GoalTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GoalTutorialFrame.hpp"

#include "Context.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{

namespace widgets
{

/**
 *
 */
GoalTutorialFrame::GoalTutorialFrame(const utils::Context& context) :
    TutorialFrame(
        100.f,
        650.f,
        110.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();

    firstLine->setString(
        "The game is divided into series. There are two types of series :"
        "the officials and"
    );

    secondLine->setString(
        "the personal series. The official series are the default ones "
        "available in the"
    );

    thirdLine->setString(
        "game by default. The personal series are the ones created by "
        "you. Yes, you can"
    );

    fourthLine->setString(
        "create you own series/levels and play to it..."
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
        170.f
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
}

}
}
