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
constexpr unsigned int TITLE_SIZE = 140;

/* used for editors titles, sub-menus titles */
constexpr unsigned int SUB_TITLE_SIZE = 70;

/* used for all the lists and menus selectable items */
constexpr unsigned int ITEM_SIZE = 60;

/* used for explanations, game screen items, error screen
   messages and some specific items in the editors */
constexpr unsigned int TEXT_SIZE = 50;

/* used for the input text widget */
constexpr unsigned int INPUT_TEXT_SIZE = 45;

/* used for small information messages displayed inside
   the editors ( files errors, names errors... ) */
constexpr unsigned int INFORMATION_SIZE = 30;

/* used to display the left levels amount in the serie
   when the player wins */
constexpr unsigned int LEVELS_COUNTDOWN_SIZE = 400;

};
}

#endif
