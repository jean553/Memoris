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
 * @file TexturesManager.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TexturesManager.hpp"

namespace memoris
{
namespace textures
{

const std::string TexturesManager::LOAD_TEXTURE_FILE_ERROR =
    "Cannot load the texture : ";
const std::string TexturesManager::GITHUB_TEXTURE_PATH =
    "res/images/fork-me.png";

/**
 *
 */
TexturesManager& TexturesManager::get()
{
    /* create only one time a textures manager instance */
    static TexturesManager singleton;

    /* always return the same textures manager instance */
    return singleton;
}

/**
 *
 */
TexturesManager::TexturesManager()
{
    /* load all the textures one by one; an exception is throw
       and the program stop if one texture cannot be loaded */

    loadTexture(githubTexture, GITHUB_TEXTURE_PATH);
}

/**
 *
 */
sf::Texture& TexturesManager::getGithubTexture()
{
    return githubTexture;
}

/**
 *
 */
void TexturesManager::loadTexture(
    sf::Texture& sfmlTexture,
    const std::string& filePath
)
{
    /* try to open the given texture at the given file path; throw an
       exception and terminates the program if the texture cannot be loaded */
    if (!sfmlTexture.loadFromFile(filePath))
    {
        throw std::invalid_argument(LOAD_TEXTURE_FILE_ERROR + filePath);
    }
}

}
}
