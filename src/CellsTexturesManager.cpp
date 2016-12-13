/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

#include <SFML/Graphics/Texture.hpp>

namespace memoris
{
namespace managers
{

class CellsTexturesManager::Impl
{

public:

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
    sf::Texture elevatorUpCellTexture;
    sf::Texture elevatorDownCellTexture;
    sf::Texture quarterRotationCellTexture;
    sf::Texture invertedQuarterRotationCellTexture;
};

/**
 *
 */
CellsTexturesManager::CellsTexturesManager() :
    impl(std::make_unique<Impl>())
{
    loadTexture(impl->emptyCellTexture, "empty");
    loadTexture(impl->departureCellTexture, "departure");
    loadTexture(impl->arrivalCellTexture, "arrival");
    loadTexture(impl->starCellTexture, "star");
    loadTexture(impl->moreLifeCellTexture, "moreLife");
    loadTexture(impl->lessLifeCellTexture, "lessLife");
    loadTexture(impl->moreTimeCellTexture, "moreTime");
    loadTexture(impl->lessTimeCellTexture, "lessTime");
    loadTexture(impl->wallCellTexture, "wall");
    loadTexture(impl->hiddenCellTexture, "hidden");
    loadTexture(impl->stairsUpCellTexture, "stairs_up");
    loadTexture(impl->stairsDownCellTexture, "stairs_down");
    loadTexture(impl->horizontalMirrorCellTexture, "horizontal_mirror");
    loadTexture(impl->verticalMirrorCellTexture, "vertical_mirror");
    loadTexture(impl->diagonalCellTexture, "diagonal");
    loadTexture(impl->leftRotationCellTexture, "rotate_left");
    loadTexture(impl->rightRotationCellTexture, "rotate_right");
    loadTexture(impl->elevatorUpCellTexture, "elevator_up");
    loadTexture(impl->elevatorDownCellTexture, "elevator_down");
    loadTexture(impl->quarterRotationCellTexture, "quarter_rotation");
    loadTexture(
        impl->invertedQuarterRotationCellTexture,
        "inverted_quarter_rotation"
    );
}

/**
 *
 */
CellsTexturesManager::~CellsTexturesManager() noexcept = default;

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
        return impl->wallCellTexture;
    }
    case cells::DEPARTURE_CELL:
    {
        return impl->departureCellTexture;
    }
    case cells::ARRIVAL_CELL:
    {
        return impl->arrivalCellTexture;
    }
    case cells::STAR_CELL:
    {
        return impl->starCellTexture;
    }
    case cells::MORE_LIFE_CELL:
    {
        return impl->moreLifeCellTexture;
    }
    case cells::LESS_LIFE_CELL:
    {
        return impl->lessLifeCellTexture;
    }
    case cells::MORE_TIME_CELL:
    {
        return impl->moreTimeCellTexture;
    }
    case cells::LESS_TIME_CELL:
    {
        return impl->lessTimeCellTexture;
    }
    case cells::STAIRS_UP_CELL:
    {
        return impl->stairsUpCellTexture;
    }
    case cells::STAIRS_DOWN_CELL:
    {
        return impl->stairsDownCellTexture;
    }
    case cells::HORIZONTAL_MIRROR_CELL:
    {
        return impl->horizontalMirrorCellTexture;
    }
    case cells::VERTICAL_MIRROR_CELL:
    {
        return impl->verticalMirrorCellTexture;
    }
    case cells::DIAGONAL_CELL:
    {
        return impl->diagonalCellTexture;
    }
    case cells::LEFT_ROTATION_CELL:
    {
        return impl->leftRotationCellTexture;
    }
    case cells::RIGHT_ROTATION_CELL:
    {
        return impl->rightRotationCellTexture;
    }
    case cells::HIDDEN_CELL:
    {
        return impl->hiddenCellTexture;
    }
    case cells::ELEVATOR_UP_CELL:
    {
        return impl->elevatorUpCellTexture;
    }
    case cells::ELEVATOR_DOWN_CELL:
    {
        return impl->elevatorDownCellTexture;
    }
    case cells::QUARTER_ROTATION_CELL:
    {
        return impl->quarterRotationCellTexture;
    }
    case cells::INVERTED_QUARTER_ROTATION_CELL:
    {
        return impl->invertedQuarterRotationCellTexture;
    }
    }

    return impl->emptyCellTexture;
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
