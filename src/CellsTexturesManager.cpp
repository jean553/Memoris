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
    loadTexture(stairsUpCellTexture, "res/cells/stairs_up.png");
    loadTexture(stairsDownCellTexture, "res/cells/stairs_down.png");
}

/**
 *
 */
sf::Texture& CellsTexturesManager::getTextureReferenceByCellType(
    const char& type
)
{
    /* returns the correct cell texture reference according to the type */
    switch(type)
    {
    case cells::WALL_CELL:
    {
        return wallCellTexture;
    }
    case cells::DEPARTURE_CELL:
    {
        return departureCellTexture;
    }
    case cells::ARRIVAL_CELL:
    {
        return arrivalCellTexture;
    }
    case cells::STAR_CELL:
    {
        return starCellTexture;
    }
    case cells::MORE_LIFE_CELL:
    {
        return moreLifeCellTexture;
    }
    case cells::LESS_LIFE_CELL:
    {
        return lessLifeCellTexture;
    }
    case cells::MORE_TIME_CELL:
    {
        return moreTimeCellTexture;
    }
    case cells::LESS_TIME_CELL:
    {
        return lessTimeCellTexture;
    }
    case cells::STAIRS_UP_CELL:
    {
        return stairsUpCellTexture;
    }
    case cells::STAIRS_DOWN_CELL:
    {
        return stairsDownCellTexture;
    }
    }

    /* by default, an empty cell texture reference is returned if the type
       cannot be found; using this default way, we will return a reference
       whatever the type character value; the process is safe and will never
       file in a 'unknown' status */
    return emptyCellTexture;
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
