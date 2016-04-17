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
 * Dimensions.
 *
 * @file Dimensions.hpp
 * @brief contains defined and fixed dimensions
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_DIMENSIONS
#define DEF_DIMENSIONS

namespace constants
{
class Dimensions
{

public:

    static const unsigned short EDITOR_BUTTONS_WIDTH;
    static const unsigned short LEVEL_CELLS_PER_FLOOR;
    static const unsigned short CELLS_PER_COLUMN;
    static const unsigned short LEVEL_FLOORS;
    static const unsigned short POSITION_NAME_LABEL_Y;
    static const unsigned short LEVEL_MAX_FLOOR_NUMBER;

    static const float CELL_PIXELS_DIMENSIONS;
    static const float CELLS_PIXELS_SEPARATION;
    static const float SELECTED_CELLS_BORDER_WIDTH;
    static const float SELECTOR_CELLS_PIXELS_SEPARATION;
};
}

#endif
