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
 * @file WelcomeTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WelcomeTutorialFrame.hpp"

#include "Context.hpp"
#include "fonts.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
WelcomeTutorialFrame::WelcomeTutorialFrame(const utils::Context& context) :
    TutorialFrame(
        100.f,
        650.f,
        150.f
    )
{
    auto title = std::make_unique<sf::Text>(); // std::unique_ptr<sf::Text>
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();

    title->setString("Welcome in Memoris !");
    firstLine->setString(
        "This first serie is a set of tutorials teaching you how to play to "
        "Memoris"
    );
    secondLine->setString(
        "This popup displays the tutorial instruction. Press Enter to switch "
        "to the next instruction."
    );

    title->setColor(context.getColorsManager().getColorWhite());
    title->setCharacterSize(fonts::INFORMATION_SIZE);
    title->setFont(context.getFontsManager().getTutorialFont());

    applyPropertiesToText(
        context,
        firstLine
    );

    applyPropertiesToText(
        context,
        secondLine
    );

    title->setPosition(
        200.f,
        110.f
    );

    firstLine->setPosition(
        20.f,
        180.f
    );

    secondLine->setPosition(
        20.f,
        200.f
    );

    title->setColor(context.getColorsManager().getColorWhite());

    insertItem(std::move(title));
    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
}

}
}
