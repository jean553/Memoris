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
 * @file CellsTexturesManager.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellsTexturesManager.hpp"

#include "TexturesLoader.hpp"
#include "cells.hpp"

namespace memoris
{
namespace textures
{

/**
 *
 */
CellsTexturesManager& CellsTexturesManager::get()
{
    /* create only one time a textures manager instance */
    static CellsTexturesManager singleton;

    /* always return the same textures manager instance */
    return singleton;
}

/**
 *
 */
CellsTexturesManager::CellsTexturesManager()
{
    /* load all the cells pictures one by one; throw an exception and stop
       the game if one load fails */

    loadTexture(emptyCellTexture, "res/cells/empty.png");
    loadTexture(departureCellTexture, "res/cells/departure.png");
    loadTexture(arrivalCellTexture, "res/cells/arrival.png");
    loadTexture(starCellTexture, "res/cells/star.png");
    loadTexture(moreLifeCellTexture, "res/cells/moreLife.png");
    loadTexture(lessLifeCellTexture, "res/cells/lessLife.png");
    loadTexture(moreTimeCellTexture, "res/cells/moreTime.png");
    loadTexture(lessTimeCellTexture, "res/cells/lessTime.png");
    loadTexture(wallCellTexture, "res/cells/wall.png");
    loadTexture(hiddenCellTexture, "res/cells/hidden.png");
}

/**
 *
 */
sf::Texture& CellsTexturesManager::getTextureReferenceByCellType(
    const std::string& type
)
{
    /* NOTE: we do not use switch/case here because this instruction does not
       work with std::string objects */

    if (type == cells::EMPTY_CELL)
    {
        return emptyCellTexture;
    }
    else if (type == cells::DEPARTURE_CELL)
    {
        return departureCellTexture;
    }
    else if (type == cells::ARRIVAL_CELL)
    {
        return arrivalCellTexture;
    }
    else if (type == cells::STAR_CELL)
    {
        return starCellTexture;
    }
    else if (type == cells::MORE_LIFE_CELL)
    {
        return moreLifeCellTexture;
    }
    else if (type == cells::LESS_LIFE_CELL)
    {
        return lessLifeCellTexture;
    }
    else if (type == cells::MORE_TIME_CELL)
    {
        return moreTimeCellTexture;
    }
    else if (type == cells::LESS_TIME_CELL)
    {
        return lessTimeCellTexture;
    }
    else
    {
        return wallCellTexture;
    }
}

/**
 *
 */
sf::Texture& CellsTexturesManager::getHiddenCellTexture()
{
    return hiddenCellTexture;
}

}
}
