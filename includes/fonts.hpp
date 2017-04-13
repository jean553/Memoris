/**
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @file fonts.hpp
 * @brief contains fonts paths and sizes
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_FONTS_H_
#define MEMORIS_FONTS_H_

#include <string>

namespace memoris
{
namespace fonts
{

/* NOTE: we use unsigned int for all the fonts sizes because it is the one
   SFML requires when we set the font size of a text surface */

/* used for the unique main title in the main menu */
constexpr unsigned int SUB_TITLE_SIZE = 70;
constexpr unsigned int ITEM_SIZE = 60;
constexpr unsigned int TEXT_SIZE = 50;
constexpr unsigned int INPUT_TEXT_SIZE = 45;
constexpr unsigned int INFORMATION_SIZE = 30;
constexpr unsigned int TUTORIAL_SIZE = 16;
constexpr unsigned int LEVELS_COUNTDOWN_SIZE = 400;

};
}

#endif
