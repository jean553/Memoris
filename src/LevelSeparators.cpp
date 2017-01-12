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
 * @file LevelSeparators.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelSeparators.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{
namespace utils
{

class LevelSeparators::Impl
{

public:

    Impl(const utils::Context& context) :
        window(context.getSfmlWindow())
    {
        constexpr float SEPARATORS_WIDTH {1.f};
        const auto separatorsSize = sf::Vector2f(
            SEPARATORS_WIDTH,
            window::HEIGHT
        );
        left.setSize(separatorsSize);
        right.setSize(separatorsSize);

        constexpr float SEPARATORS_VERTICAL_POSITION {0.f};

        constexpr float LEFT_SEPARATOR_HORIZONTAL_POSITION {290.f};
        left.setPosition(
            LEFT_SEPARATOR_HORIZONTAL_POSITION,
            SEPARATORS_VERTICAL_POSITION
        );

        constexpr float RIGHT_SEPARATOR_HORIZONTAL_POSITION {1308.f};
        right.setPosition(
            RIGHT_SEPARATOR_HORIZONTAL_POSITION,
            SEPARATORS_VERTICAL_POSITION
        );

        const auto& white = context.getColorsManager().getColorWhite();
        left.setFillColor(white);
        right.setFillColor(white);
    }

    sf::RenderWindow& window;

    sf::RectangleShape left;
    sf::RectangleShape right;
};

/**
 *
 */
LevelSeparators::~LevelSeparators() = default;

/**
 *
 */
LevelSeparators::LevelSeparators(
    const utils::Context& context
) : impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
void LevelSeparators::display() const &
{
    auto& window = impl->window;
    window.draw(impl->left);
    window.draw(impl->right);
}

}
}
