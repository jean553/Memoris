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
 * @file FloorDashboardTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FloorDashboardTutorialFrame.hpp"

#include "Context.hpp"
#include "TexturesManager.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
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
FloorDashboardTutorialFrame::FloorDashboardTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        580.f,
        170.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto currentFloor = std::make_unique<sf::Text>();

    auto floorIcon = std::make_unique<sf::Sprite>();

    firstLine->setString(
        "Both during the watching period and the playing "
        "period, the current "
    );

    secondLine->setString(
        "displayed floor is displayed at the top of the screen, "
        "next to the elevator icon."
    );

    thirdLine->setString(
        "The game starts when you press Enter."
    );

    floorIcon->setTexture(context.getTexturesManager().getFloorTexture());

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

    floorIcon->setPosition(
        270.f,
        260.f
    );

    thirdLine->setPosition(
        20.f,
        320.f
    );

    currentFloor->setPosition(
        225.f,
        245.f
    );

    currentFloor->setString("1");
    currentFloor->setFont(context.getFontsManager().getTextFont());
    currentFloor->setCharacterSize(fonts::TEXT_SIZE);
    currentFloor->setColor(
        context.getColorsManager().getColorWhite()
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(floorIcon));
    insertItem(std::move(currentFloor));
}

}
}
