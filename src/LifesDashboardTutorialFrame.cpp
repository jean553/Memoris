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
 * @file LifesDashboardTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LifesDashboardTutorialFrame.hpp"

#include "TexturesManager.hpp"
#include "Context.hpp"
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
LifesDashboardTutorialFrame::LifesDashboardTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        500.f,
        160.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto lifesAmount = std::make_unique<sf::Text>();

    auto lifesIcon = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "The current amount of lifes you have is displayed "
        "at the top of "
    );

    secondLine->setString(
        "the map next to the lifes icon."
    );

    thirdLine->setString(
        "The level starts when you press Enter."
    );

    lifesAmount->setString("0");
    lifesAmount->setFont(context.getFontsManager().getTextFont());
    lifesAmount->setCharacterSize(fonts::TEXT_SIZE);
    lifesAmount->setColor(
        context.getColorsManager().getColorWhite()
    );

    lifesIcon->setTexture(
        context.getTexturesManager().getLifeTexture()
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
        320.f
    );

    lifesIcon->setPosition(
        250.f,
        260.f
    );

    lifesAmount->setPosition(
        200.f,
        250.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(lifesIcon));
    insertItem(std::move(lifesAmount));
    insertItem(std::move(thirdLine));
}

}
}
