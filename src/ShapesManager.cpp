/**
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
 * @file ShapesManager.hpp
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ShapesManager.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"

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
        horizontalSeparator.setPosition(
            400.f, 
            495.f
        );

        verticalSeparator.setPosition(
            798.f,
            98.f
        );

        /* we directly set the color instead of using the colors manager; in
           fact, the context object has not totally finished to build the
           context object when this constructor is executed, so it cannot be
           used */

        sf::Color redColor = sf::Color(
            255.f,
            0.f,
            0.f,
            255.f
        );

        horizontalSeparator.setFillColor(redColor);
        verticalSeparator.setFillColor(redColor);

        horizontalSeparator.setSize(
            sf::Vector2f(
                800.f, 
                4.f
            )
        );

        verticalSeparator.setSize(
            sf::Vector2f(
                4.f,
                800.f
            )
        );
    }

    sf::RectangleShape horizontalSeparator;
    sf::RectangleShape verticalSeparator;
};

/**
 *
 */
ShapesManager::ShapesManager() :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
ShapesManager::~ShapesManager() noexcept = default;

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
