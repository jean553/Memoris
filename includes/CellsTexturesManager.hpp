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
 * @file CellsTexturesManager.hpp
 * @brief loads the cells textures
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLSTEXTURESMANAGER_H_
#define MEMORIS_CELLSTEXTURESMANAGER_H_

#include "AbstractTexturesManager.hpp"

namespace memoris
{
namespace managers
{

class CellsTexturesManager : public AbstractTexturesManager
{

public:

    /**
     * @brief constructor, loads each texture one by one, stop if one texture
     * cannot be loaded
     *
     * @throw std::invalid_argument if one of the image cannot be loaded, an
     * exception is thrown and never caught to let the program stops
     *
     * not 'noexcept' because it throws an exception if one file cannot be
     * loaded
     */
    CellsTexturesManager();

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

    sf::Texture emptyCellTexture;
    sf::Texture departureCellTexture;
    sf::Texture arrivalCellTexture;
    sf::Texture starCellTexture;
    sf::Texture moreLifeCellTexture;
    sf::Texture lessLifeCellTexture;
    sf::Texture moreTimeCellTexture;
    sf::Texture lessTimeCellTexture;
    sf::Texture wallCellTexture;
    sf::Texture hiddenCellTexture;
    sf::Texture stairsUpCellTexture;
    sf::Texture stairsDownCellTexture;
    sf::Texture horizontalMirrorCellTexture;
    sf::Texture verticalMirrorCellTexture;
    sf::Texture diagonalCellTexture;
    sf::Texture leftRotationCellTexture;
    sf::Texture rightRotationCellTexture;
};

}
}

#endif
