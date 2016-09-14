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
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellsTexturesManager.hpp"

#include "cells.hpp"

#include <string>

namespace memoris
{
namespace managers
{

/**
 *
 */
CellsTexturesManager::CellsTexturesManager()
{
    loadTexture(emptyCellTexture, "empty");
    loadTexture(departureCellTexture, "departure");
    loadTexture(arrivalCellTexture, "arrival");
    loadTexture(starCellTexture, "star");
    loadTexture(moreLifeCellTexture, "moreLife");
    loadTexture(lessLifeCellTexture, "lessLife");
    loadTexture(moreTimeCellTexture, "moreTime");
    loadTexture(lessTimeCellTexture, "lessTime");
    loadTexture(wallCellTexture, "wall");
    loadTexture(hiddenCellTexture, "hidden");
    loadTexture(stairsUpCellTexture, "stairs_up");
    loadTexture(stairsDownCellTexture, "stairs_down");
    loadTexture(horizontalMirrorCellTexture, "horizontal_mirror");
    loadTexture(verticalMirrorCellTexture, "vertical_mirror");
    loadTexture(diagonalCellTexture, "diagonal");
    loadTexture(leftRotationCellTexture, "rotate_left");
    loadTexture(rightRotationCellTexture, "rotate_right");
}

/**
 *
 */
const sf::Texture& CellsTexturesManager::getTextureReferenceByCellType(
    const char& type
) const & noexcept
{
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
    case cells::HORIZONTAL_MIRROR_CELL:
    {
        return horizontalMirrorCellTexture;
    }
    case cells::VERTICAL_MIRROR_CELL:
    {
        return verticalMirrorCellTexture;
    }
    case cells::DIAGONAL_CELL:
    {
        return diagonalCellTexture;
    }
    case cells::LEFT_ROTATION_CELL:
    {
        return leftRotationCellTexture;
    }
    case cells::RIGHT_ROTATION_CELL:
    {
        return rightRotationCellTexture;
    }
    case cells::HIDDEN_CELL:
    {
        return hiddenCellTexture;
    }
    }

    return emptyCellTexture;
}

/**
 *
 */
void CellsTexturesManager::loadTexture(
    sf::Texture& texture,
    const std::string& path
) &
{
    if (!texture.loadFromFile("res/cells/" + path + ".png"))
    {
        throw std::invalid_argument("Cannot load texture : " + path);
    }
}

}
}
