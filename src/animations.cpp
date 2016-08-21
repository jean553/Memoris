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
 * @file animations.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "animations.hpp"

#include "HorizontalMirrorAnimation.hpp"
#include "VerticalMirrorAnimation.hpp"
#include "StairsAnimation.hpp"
#include "cells.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
std::unique_ptr<LevelAnimation> getAnimationByCellType(
    const std::shared_ptr<utils::Context>& context,
    const char& cellType
)
{
    /* creates the animation according to the given cell type */
    switch(cellType)
    {
    case cells::VERTICAL_MIRROR_CELL:
    {
        return std::make_unique<VerticalMirrorAnimation>(context);
    }
    case cells::STAIRS_UP_CELL:
    {
        return std::make_unique<StairsAnimation>(
                   context,
                   1
               );
    }
    case cells::STAIRS_DOWN_CELL:
    {
        return std::make_unique<StairsAnimation>(
                   context,
                   -1
               );
    }
    default:
    {
        /* by default, the horizontal mirror animation is created */

        return std::make_unique<HorizontalMirrorAnimation>(context);
    }
    }
}

}
}
