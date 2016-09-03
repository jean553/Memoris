/*
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
 * @file CellsSelector.hpp
 * @brief the selector of cells into the level editor
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLSSELECTOR_H_
#define MEMORIS_CELLSSELECTOR_H_

#include "Context.hpp"

namespace memoris
{
namespace utils
{

class CellsSelector
{

public:

    /**
     * @brief constructor, loads the textures from the textures manager to
     * create the sprites
     *
     * @param context shared pointer to the current context to use
     */
    CellsSelector(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief displays the cells selector
     *
     * @param context shared pointer to the current context to use
     */
    void display(const std::shared_ptr<utils::Context>& context);

private:

    /* sprites of the cells */

    sf::Sprite emptyCell;
    sf::Sprite departureCell;
    sf::Sprite arrivalCell;
    sf::Sprite starCell;
    sf::Sprite moreLifeCell;
    sf::Sprite lessLifeCell;
    sf::Sprite moreTimeCell;
    sf::Sprite lessTimeCell;
    sf::Sprite wallCell;
    sf::Sprite stairsUpCell;
    sf::Sprite stairsDownCell;
    sf::Sprite horizontalMirrorCell;
    sf::Sprite verticalMirrorCell;
    sf::Sprite leftRotationCell;
    sf::Sprite rightRotationCell;
};

}
}

#endif