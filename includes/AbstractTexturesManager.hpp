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
 * @path AbstractTexturesManager.hpp
 * @brief contains a common static method for both the cells textures manager
 * and the simple textures manager
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTTEXTURESMANAGER_H_
#define MEMORIS_ABSTRACTTEXTURESMANAGER_H_

#include "NotCopiable.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <stdexcept>

namespace memoris
{
namespace textures
{

class AbstractTexturesManager : public utils::NotCopiable
{

protected:

    /**
     * @brief, pre virtual destructor to make the class abstract; we use that
     * pattern because the implementation of loadTexture() is the same, no
     * matter the child object, and because it makes no sense to simply
     * creates an object of the current class
     *
     * noexcept, any child destructor can throw exceptions; nowehere in the
     * code we handle exceptions that happen in textures managers destructor
     */
    virtual ~AbstractTexturesManager() noexcept = 0;

    /**
     * @brief try to load the image at the given path into a SFML texture
     *
     * @param texture SFML texture reference where the image has to be loaded
     * @param path string containing the file path to load
     *
     * @throw std::invalid_argument if the image file cannot be loaded,
     * this exception is never caught, the program is directly stopped if
     * at least one texture cannot be loaded
     *
     * 'texture' parameter is not constant because we actually modify the
     * texture at the given reference
     *
     * the method is not const because static a member cannot be constant
     */
    static void loadTexture(
        sf::Texture& texture,
        const std::string& path
    );
};

}
}

#endif
