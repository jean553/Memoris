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
 * @file window.cpp
 * @brief namespace for SFML window dimensions, resolution and title
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "window.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace window
{

const std::string TITLE = "Memoris";

/**
 *
 */
const float getCenteredSfmlSurfaceHorizontalPosition(const sf::Text& text)
{
    /* the window::WIDTH variable is an unsigned int and this is not
       guarantee that getLocalBounds().width returns a float */
    return static_cast<float>(WIDTH) / 2 -
        static_cast<float>(text.getLocalBounds().width) / 2;
}

}
}
