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
 * @file WatchingTimeTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WatchingTimeTutorialFrame.hpp"

#include "Context.hpp"
#include "TexturesManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
WatchingTimeTutorialFrame::WatchingTimeTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        100.f,
        650.f,
        340.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto sixthLine = std::make_unique<sf::Text>();
    auto seventhLine = std::make_unique<sf::Text>();
    auto heigthLine = std::make_unique<sf::Text>();
    auto clockIcon = std::make_unique<sf::Sprite>();
    auto watchingTime = std::make_unique<sf::Text>();

    firstLine->setString(
        "When the level starts, you can see all the cells during a short "
        "time. This short time "
    );

    secondLine->setString(
        "is called the watching time. During this period, the player does "
        "not move and only has "
    );

    thirdLine->setString(
        "to remember the cells disposition."
    );

    fourthLine->setString(
        "The watching time can be different between each level. For the "
        "current level, the amount "
    );

    fifthLine->setString(
        "of watching time seconds is displayed at the top of the screen, "
        "next to the clock icon."
    );

    sixthLine->setString(
        "During the watching time, the left amount of seconds is displayed "
        "on both sides of the "
    );

    seventhLine->setString(
        "map. When the watching time is elapsed, all the cells are "
        "suddenly hidden and "
    );

    heigthLine->setString(
        "you can start to move the pin."
    );

    watchingTime->setString("6");
    watchingTime->setFont(context.getFontsManager().getTextFont());
    watchingTime->setCharacterSize(fonts::TEXT_SIZE);
    watchingTime->setColor(
        context.getColorsManager().getColorWhite()
    );

    clockIcon->setTexture(context.getTexturesManager().getTimeTexture());

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
        200.f
    );

    fifthLine->setPosition(
        20.f,
        220.f
    );

    sixthLine->setPosition(
        20.f,
        340.f
    );

    seventhLine->setPosition(
        20.f,
        360.f
    );

    heigthLine->setPosition(
        20.f,
        380.f
    );

    clockIcon->setPosition(
        330.f,
        270.f
    );

    watchingTime->setPosition(
        280.f,
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

    applyPropertiesToText(
        context,
        heigthLine
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(sixthLine));
    insertItem(std::move(seventhLine));
    insertItem(std::move(heigthLine));
    insertItem(std::move(clockIcon));
    insertItem(std::move(watchingTime));
}

}
}
