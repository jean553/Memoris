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
 * @file window.hpp
 * @brief provides window dimension and common method to center text
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WINDOW_H_
#define MEMORIS_WINDOW_H_

namespace sf
{
class Text;
}

namespace memoris
{
namespace window
{

/* unsigned integers because the RenderWindow constructor gets unsigned int;
   we prevent unsigned int to float conversion everytime we get
   the horizontal position of a centered text; in fact, the SFML window
   controller takes an unsigned integer and the texts positions
   are set with floats */

constexpr float WIDTH {1600.f};

constexpr unsigned int HEIGHT {900};

/**
 * @brief returns the expected horizontal position
 * when a surface must be centered
 *
 * @param text the text surface to center
 *
 * @return const float
 *
 * not noexcept because it calls SFML functions that are not noexcept
 *
 * this function is declared here because the provided feature is required
 * by many different classes without any relationship between each others
 */
const float getCenteredTextHorizontalPosition(const sf::Text& text);

}
}

#endif
