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
 * @file separators.hpp
 * @brief renders the level separators of the animations; we use separated
 * functions because not all the animations need separators, so this is
 * superfluous to put them into a parent class
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Context.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{
namespace utils
{

/**
 * @brief takes a reference to a rectangle shape and initializes it as a
 * horizontal separator of the level
 *
 * @param context shared pointer to the context to use
 * @param separator reference to the separator SFML surface to initialize
 */
void initializeHorizontalSeparator(
    utils::Context& context,
    sf::RectangleShape& separator
);

/**
 * @brief takes a reference to a rectangle shape and initializes it as a
 * vertical separator of the level
 *
 * @param context shared pointer to the context to use
 * @param separator reference to the separator SFML surface to initialize
 */
void initializeVerticalSeparator(
    utils::Context& context,
    sf::RectangleShape& separator
);

}
}
