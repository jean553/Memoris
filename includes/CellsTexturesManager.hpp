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
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLSTEXTURESMANAGER_H_
#define MEMORIS_CELLSTEXTURESMANAGER_H_

#include "NotCopiable.hpp"

#include <SFML/Graphics.hpp>

#include <string>

namespace memoris
{
namespace textures
{

class CellsTexturesManager : public others::NotCopiable
{
public:

    /**
     * @brief constructor, loads each texture one by one, stop if one texture
     * cannot be loaded
     */
    CellsTexturesManager();

    /**
     * @brief returns a texture reference corresponding to the given cell type
     *
     * @param type the type of the cell to get
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTextureReferenceByCellType(const char& type) const;

    /**
     * @brief returns a texture reference of the hidden cell texture; this cell
     * texture is special and is useless in the cells factory method; that's
     * why we return this texture using a separated dedicated method
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getHiddenCellTexture() const;

private:

    /* the textures of all the cells */
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
};

}
}

#endif
