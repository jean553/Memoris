/**
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
 * @file TexturesLoader.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TexturesLoader.hpp"

namespace memoris
{
namespace textures
{

/**
 *
 */
void loadTexture(
    sf::Texture& sfmlTexture,
    const std::string& filePath
)
{
    /* try to open the given texture at the given file path; throw an
       exception and terminates the program if the texture cannot be loaded */
    if (!sfmlTexture.loadFromFile(filePath))
    {
        throw std::invalid_argument("Cannot load texture : " + filePath);
    }
}

}
}
