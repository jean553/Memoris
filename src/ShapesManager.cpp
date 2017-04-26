/**
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
 * @file ShapesManager.hpp
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ShapesManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{
namespace managers
{

class ShapesManager::Impl
{

public:

    Impl()
    {
        constexpr float HORIZONTAL_SEPARATOR_HORIZONTAL_POSITION {400.f};
        constexpr float HORIZONTAL_SEPARATOR_VERTICAL_POSITION {495.f};
        horizontalSeparator.setPosition(
            HORIZONTAL_SEPARATOR_HORIZONTAL_POSITION,
            HORIZONTAL_SEPARATOR_VERTICAL_POSITION
        );

        constexpr float VERTICAL_SEPARATOR_HORIZONTAL_POSITION {798.f};
        constexpr float VERTICAL_SEPARATOR_VERTICAL_POSITION {98.f};
        verticalSeparator.setPosition(
            VERTICAL_SEPARATOR_HORIZONTAL_POSITION,
            VERTICAL_SEPARATOR_VERTICAL_POSITION
        );

        /* we do not load the color from the colors manager 
           because we do not pass the context to only load one color */

        sf::Color redColor = sf::Color(
            255.f,
            0.f,
            0.f,
            255.f
        );

        horizontalSeparator.setFillColor(redColor);
        verticalSeparator.setFillColor(redColor);

        constexpr float LEVEL_WIDTH_AND_HEIGHT {800.f};
        constexpr float SEPARATORS_WIDTH {4.f};

        horizontalSeparator.setSize(
            sf::Vector2f(
                LEVEL_WIDTH_AND_HEIGHT,
                SEPARATORS_WIDTH
            )
        );

        verticalSeparator.setSize(
            sf::Vector2f(
                SEPARATORS_WIDTH,
                LEVEL_WIDTH_AND_HEIGHT
            )
        );
    }

    sf::RectangleShape horizontalSeparator;
    sf::RectangleShape verticalSeparator;
};

/**
 *
 */
ShapesManager::ShapesManager() : impl(std::make_unique<Impl>())
{
}

/**
 *
 */
ShapesManager::~ShapesManager() = default;

/**
 *
 */
const sf::RectangleShape& ShapesManager::getHorizontalSeparator() const &
noexcept
{
    return impl->horizontalSeparator;
}

/**
 *
 */
const sf::RectangleShape& ShapesManager::getVerticalSeparator() const &
noexcept
{
    return impl->verticalSeparator;
}

}
}
