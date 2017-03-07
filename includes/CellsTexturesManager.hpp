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
 * @file CellsTexturesManager.hpp
 * @brief loads and provides the cells textures
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLSTEXTURESMANAGER_H_
#define MEMORIS_CELLSTEXTURESMANAGER_H_

#include <memory>

namespace sf
{
class Texture;
};

namespace memoris
{
namespace managers
{

class CellsTexturesManager
{

public:

    /**
     * @brief constructor, loads each texture one by one,
     * throws an exception if the texture cannot be loaded
     *
     * @throw std::invalid_argument if one of the image cannot be loaded, an
     * exception is thrown and never caught to let the program stops
     */
    CellsTexturesManager();

    CellsTexturesManager(const CellsTexturesManager& other) = delete;

    CellsTexturesManager& operator=(
        const CellsTexturesManager& other
    ) = delete;

    /**
     * @brief default destructor
     */
    ~CellsTexturesManager();

    /**
     * @brief returns a texture reference corresponding to the given cell type
     *
     * @param type the type of the cell to get
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTextureReferenceByCellType(const char& type) const &
    noexcept ;

private:

    /**
     * @brief load a texture from the textures folder
     *
     * @param texture the SFML texture object that has to be set
     * @param path file path of the *.png picture to load
     *
     * @throw std::invalid_argument the given file cannot be opened; the
     * exception is not caught in order to close the program directly if at
     * least one texture cannot be loaded
     *
     * not const because modifies the textures of the object
     */
    void loadTexture(
        sf::Texture& texture,
        const std::string& path
    ) &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
