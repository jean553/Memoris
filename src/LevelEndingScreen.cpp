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
 * @file LevelEndingScreen.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelEndingScreen.hpp"

#include "window.hpp"
#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace utils
{

/**
 *
 */
LevelEndingScreen::LevelEndingScreen(const Context& context)
{
    filter.setSize(
        sf::Vector2f(
            window::WIDTH,
            window::HEIGHT
        )
    );
    filter.setFillColor(
        context.getColorsManager().getColorPartialDarkGrey()
    );

    text.setCharacterSize(fonts::TITLE_SIZE);
    text.setFont(context.getFontsManager().getTextFont());
}

/**
 *
 */
LevelEndingScreen::~LevelEndingScreen() noexcept = default;

/**
 *
 */
void LevelEndingScreen::render(const Context& context) &
{
    context.getSfmlWindow().draw(filter);
    context.getSfmlWindow().draw(text);
}

}
}
