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
 * @file AbstractForeground.cpp
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractForeground.hpp"

namespace memoris
{
namespace foregrounds
{

class AbstractForeground::Impl
{

public:

    Impl(sf::RenderWindow& window) :
        window(window)
    {
    }

    sf::RenderWindow& window;
};

/**
 *
 */
AbstractForeground::AbstractForeground(sf::RenderWindow& window) :
    impl(std::make_unique<Impl>(window))
{
}

/**
 *
 */
AbstractForeground::~AbstractForeground() = default;

/**
 *
 */
sf::RenderWindow& AbstractForeground::getWindow() const & noexcept
{
    return impl->window;
}

}
}
