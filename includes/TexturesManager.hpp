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
 * @file TexturesManager.hpp
 * @brief loads and provides the textures assets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TEXTURESMANAGER_H_
#define MEMORIS_TEXTURESMANAGER_H_

#include "NotCopiable.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace textures
{

class TexturesManager : public others::NotCopiable
{
public:

    /**
     * @brief make the textures manager a singleton class;
     * creates a static singleton object, call the private
     * constructor only one time; as the object is static,
     * this unique object is returned everytime and we never
     * create it again
     *
     * @return static TexturesManager&
     */
    static TexturesManager& get();

    /**
     * @brief getter for the github texture
     *
     * @return sf::Texture&
     */
    sf::Texture& getGithubTexture();

private:

    /**
     * @brief constructor, loads each texture one by one, stop if one texture
     * cannot be loaded
     */
    TexturesManager();

    /**
     * @brief loads one texture by file path, throw
     * an exception if the file cannot be loaded
     *
     * @param sfmlTexture SFML texture object
     * @param filePath path of the file to open
     */
    void loadTexture(
        sf::Texture& sfmlTexture,
        const std::string& filePath
    );

    /* message to display in the console if one file cannot be loaded */
    static const std::string LOAD_TEXTURE_FILE_ERROR;

    /* paths of the textures files */

    static const std::string GITHUB_TEXTURE_PATH;

    /* github texture displayed on the main menu */
    sf::Texture githubTexture;
};

}
}

#endif
