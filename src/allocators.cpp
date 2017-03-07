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
 * @file allocators.hpp
 * @package allocators
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "allocators.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace allocators
{

/**
 *
 */
template<typename T>
void createDynamicObject(std::unique_ptr<T>& pointer)
{
    pointer.reset(new T);
}

/**
 *
 */
template<typename T>
void deleteDynamicObject(std::unique_ptr<T>& pointer)
{
    pointer.reset();
}

/* explicit instanciation because not defined directly into the header */

template void createDynamicObject(std::unique_ptr<sf::Transform>& pointer);
template void deleteDynamicObject(std::unique_ptr<sf::Transform>& pointer);

}
}
