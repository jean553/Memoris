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
 * @file LevelEndingScreen.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelEndingScreen.hpp"

#include "window.hpp"
#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{
namespace utils
{

class LevelEndingScreen::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
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

        constexpr unsigned int LABELS_SIZE {140};
        text.setCharacterSize(LABELS_SIZE);
        text.setFont(context.getFontsManager().getTextFont());
    }

    const utils::Context& context;

    sf::Text text;

    sf::RectangleShape filter;
};

/**
 *
 */
LevelEndingScreen::LevelEndingScreen(const Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
LevelEndingScreen::~LevelEndingScreen() noexcept = default;

/**
 *
 */
const utils::Context& LevelEndingScreen::getContext() const & noexcept
{
    return impl->context;
}

/**
 *
 */
sf::Text& LevelEndingScreen::getText() const & noexcept
{
    return impl->text;
}

/**
 *
 */
const sf::RectangleShape& LevelEndingScreen::getFilter() const & noexcept
{
    return impl->filter;
}

/**
 *
 */
void LevelEndingScreen::render() &
{
    auto& window = impl->context.getSfmlWindow();
    window.draw(impl->filter);
    window.draw(impl->text);
}

}
}
