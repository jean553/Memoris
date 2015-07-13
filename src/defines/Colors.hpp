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
 * Colors.
 *
 * @file Colors.hpp
 * @brief path of all the colors
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_COLORS
#define DEF_COLORS
        
#include <string>

namespace constants {
class Colors {

    public:

        static constexpr unsigned int COLOR_LIGHT_BLUE_RED = 105;
        static constexpr unsigned int COLOR_LIGHT_BLUE_GREEN = 125;
        static constexpr unsigned int COLOR_LIGHT_BLUE_BLUE = 255;

        static constexpr unsigned int COLOR_WHITE_RED = 255;
        static constexpr unsigned int COLOR_WHITE_GREEN = 255;
        static constexpr unsigned int COLOR_WHITE_BLUE = 255;

        static constexpr unsigned int COLOR_RED_RED = 255;
        static constexpr unsigned int COLOR_RED_GREEN = 0;
        static constexpr unsigned int COLOR_RED_BLUE = 0;

        static constexpr unsigned int COLOR_ORANGE_RED = 255;
        static constexpr unsigned int COLOR_ORANGE_GREEN = 128;
        static constexpr unsigned int COLOR_ORANGE_BLUE = 0;

        static constexpr unsigned int COLOR_GRAY_RED = 80;
        static constexpr unsigned int COLOR_GRAY_GREEN = 80;
        static constexpr unsigned int COLOR_GRAY_BLUE = 80;

        static constexpr unsigned int COLOR_DARK_GRAY_RED = 50;
        static constexpr unsigned int COLOR_DARK_GRAY_GREEN = 50;
        static constexpr unsigned int COLOR_DARK_GRAY_BLUE = 50;

        static constexpr unsigned int COLOR_ALPHA_FULL = 255;
};
}

#endif
