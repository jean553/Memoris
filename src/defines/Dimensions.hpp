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

namespace constants {
class Dimensions {

public:

    static const unsigned int SCREEN_WIDTH = 1600;
    static const unsigned int SCREEN_HEIGHT = 900;

    static const unsigned int EDITOR_BUTTONS_WIDTH = 200;

    static const int LEVEL_CELLS_HEIGHT = 16;
    static const int LEVEL_CELLS_WIDTH = 20;
    static const int CELL_PIXELS_DIMENSIONS = 49;
    static const int CELLS_PIXELS_SEPARATION = 1;
};
}

#endif
