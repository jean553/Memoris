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

#include "cells.hpp"

namespace memoris
{
namespace managers
{

/**
 *
 */
CellsTexturesManager::CellsTexturesManager()
{
    const std::string directoryPath = "res/cells/";

    loadTexture(
        emptyCellTexture,
        directoryPath + "empty.png"
    );

    loadTexture(
        departureCellTexture,
        directoryPath + "departure.png"
    );

    loadTexture(
        arrivalCellTexture,
        directoryPath + "arrival.png"
    );

    loadTexture(
        starCellTexture,
        directoryPath + "star.png"
    );

    loadTexture(
        moreLifeCellTexture,
        directoryPath + "moreLife.png"
    );

    loadTexture(
        lessLifeCellTexture,
        directoryPath + "lessLife.png"
    );

    loadTexture(
        moreTimeCellTexture,
        directoryPath + "moreTime.png"
    );

    loadTexture(
        lessTimeCellTexture,
        directoryPath + "lessTime.png"
    );

    loadTexture(
        wallCellTexture,
        directoryPath + "wall.png"
    );

    loadTexture(
        hiddenCellTexture,
        directoryPath + "hidden.png"
    );

    loadTexture(
        stairsUpCellTexture,
        directoryPath + "stairs_up.png"
    );

    loadTexture(
        stairsDownCellTexture,
        directoryPath + "stairs_down.png"
    );

    loadTexture(
        horizontalMirrorCellTexture,
        directoryPath + "horizontal_mirror.png"
    );

    loadTexture(
        verticalMirrorCellTexture,
        directoryPath + "vertical_mirror.png"
    );

    loadTexture(
        diagonalCellTexture,
        directoryPath + "diagonal.png"
    );

    loadTexture(
        leftRotationCellTexture,
        directoryPath + "rotate_left.png"
    );

    loadTexture(
        rightRotationCellTexture,
        directoryPath + "rotate_right.png"
    );
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
}
}
