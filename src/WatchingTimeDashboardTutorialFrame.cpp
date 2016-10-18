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
 * @file WatchingTimeDashboardTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WatchingTimeDashboardTutorialFrame.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "TexturesManager.hpp"
#include "fonts.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
WatchingTimeDashboardTutorialFrame::WatchingTimeDashboardTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        650.f,
        150.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto secondsAmount = std::make_unique<sf::Text>();

    auto clockIcon = std::make_unique<sf::Sprite>();

    clockIcon->setTexture(
        context.getTexturesManager().getTimeTexture()
    );

    firstLine->setString(
        "The current watching time (in seconds), is displayed at the "
        "top of the screen "
    );

    secondLine->setString(
        "next to the clock icon."
    );

    thirdLine->setString(
        "The game starts when you press Enter."
    );

    secondsAmount->setString("6");
    secondsAmount->setCharacterSize(fonts::TEXT_SIZE);
    secondsAmount->setFont(context.getFontsManager().getTextFont());
    secondsAmount->setColor(context.getColorsManager().getColorWhite());

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
        310.f
    );

    secondsAmount->setPosition(
        300.f,
        240.f
    );

    clockIcon->setPosition(
        350.f,
        250.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(clockIcon));
    insertItem(std::move(secondsAmount));
}

}
}
