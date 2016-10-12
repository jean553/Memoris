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
 * @file StarsDashboardTutorialFrame.cpp
 *ÜB[MaÚE @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "StarsDashboardTutorialFrame.hpp"

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
StarsDashboardTutorialFrame::StarsDashboardTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        100.f,
        560.f,
        240.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto totalStarsAmount = std::make_unique<sf::Text>();
    auto foundStarsAmount = std::make_unique<sf::Text>();

    auto targetIcon = std::make_unique<sf::Sprite>();
    auto starIcon = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "The total amount of stars on the current level is displayed "
        "next to the target "
    );

    secondLine->setString(
        "icon at the top of the screen. The current found stars "
        "amount is displayed "
    );

    thirdLine->setString(
        "next to the star icon."
    );

    fourthLine->setString(
        "In this level, you have to find four stars in total. The "
        "game starts right after "
    );

    fifthLine->setString(
        "you press Enter."
    );

    totalStarsAmount->setString("4");
    totalStarsAmount->setFont(context.getFontsManager().getTextFont());
    totalStarsAmount->setCharacterSize(fonts::TEXT_SIZE);
    totalStarsAmount->setColor(
        context.getColorsManager().getColorWhite()
    );

    foundStarsAmount->setString("0");
    foundStarsAmount->setFont(context.getFontsManager().getTextFont());
    foundStarsAmount->setCharacterSize(fonts::TEXT_SIZE);
    foundStarsAmount->setColor(
        context.getColorsManager().getColorWhite()
    );

    targetIcon->setTexture(context.getTexturesManager().getTargetTexture());
    starIcon->setTexture(context.getTexturesManager().getStarTexture());

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
        280.f
    );

    fifthLine->setPosition(
        20.f,
        300.f
    );

    totalStarsAmount->setPosition(
        150.f,
        200.f
    );

    foundStarsAmount->setPosition(
        350.f,
        200.f
    );

    targetIcon->setPosition(
        190.f,
        210.f
    );

    starIcon->setPosition(
        390.f,
        210.f
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

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(targetIcon));
    insertItem(std::move(starIcon));
    insertItem(std::move(totalStarsAmount));
    insertItem(std::move(foundStarsAmount));
}

}
}
