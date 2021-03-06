/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @file LoseLevelEndingScreen.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LoseLevelEndingScreen.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace utils
{

/**
 *
 */
LoseLevelEndingScreen::LoseLevelEndingScreen(const Context& context) :
    AbstractLevelEndingScreen(context)
{
    auto& text = getText();
    text.setString("You Lose !");
    text.setFillColor(context.getColorsManager().getColorRed());

    constexpr float LOSE_TEXT_VERTICAL_POSITION {200.f};
    text.setPosition(
        window::getCenteredTextHorizontalPosition(text),
        LOSE_TEXT_VERTICAL_POSITION
    );
}

/**
 *
 */
LoseLevelEndingScreen::~LoseLevelEndingScreen() = default;

}
}
