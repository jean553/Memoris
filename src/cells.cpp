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
 * @file cells.hpp
 * @package cells
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "cells.hpp"

namespace memoris
{
namespace cells
{

/**
 *
 */
template<typename T>
std::unique_ptr<entities::Cell> getCellByType(
    const std::shared_ptr<utils::Context>& context,
    const T& horizontalPosition,
    const T& verticalPosition,
    const char type
)
{
    /* create an unique pointer to a cell object; the horizontal position
       of a cell is equal to 400 (horizontal position of the grid) + 50
       (cell width including separator) * the horizontal position cursor;
       the vertical position of a cell is equal to 98 (vertical position of
       the grid) + 50 (cell height including separator) * the vertical
       position cursor; the data type expected by the Cell constructor for
       the position is a float; this is faster to calculate positions with
       unsigned shorts, and cast them to float at the end when setting
       the data; this is not a problem to cast as we always manipulate
       integer values anyway */
    return std::make_unique<entities::Cell>(
        context,
        400.f + 50.f * static_cast<float>(horizontalPosition),
        98.f + 50.f * static_cast<float>(verticalPosition),
        type
    );
}

/* declared here because not specified into the header */

template std::unique_ptr<entities::Cell> getCellByType(
    const std::shared_ptr<utils::Context>& context,
    const unsigned short& horizontalPosition,
    const unsigned short& verticalPosition,
    const char type
);

}
}
