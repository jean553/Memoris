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
 * Fonts.
 *
 * @file Fonts.hpp
 * @brief path of all the fonts
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_FONTS
#define DEF_FONTS
        
#include <string>

namespace constants {
class Fonts {

    public:

        static constexpr unsigned int SIZE_TITLE_FONT = 140;
        static constexpr unsigned int SIZE_SUB_TITLE_FONT = 70;
        static constexpr unsigned int SIZE_ITEM_FONT = 60;
        static constexpr unsigned int SIZE_TEXT_FONT = 50;

        /**
         * @return string
         */
        static std::string getTitleFontPath(); 

        /**
         * @return string
         */
        static std::string getTextFontPath();
};
}

#endif
