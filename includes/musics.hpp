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
 * @file musics.hpp
 * @brief contains the musics files paths and one function
 * to get each path by controller id
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MUSICFACTORY_H_
#define MEMORIS_MUSICFACTORY_H_

#include <string>

namespace memoris
{
namespace musics
{
/* NOTE: the strings cannot be declared as constant expressions */

/* music played in all the menus of the game */
const std::string MAIN_MENU_MUSIC =
    "res/musics/pokki-dj-made-in-italy.ogg";

/* music played in the level editor of the game */
const std::string EDITOR_MUSIC =
    "res/musics/bigmanboo-back-to-the-90s-nostalgia.ogg";

/* music played during the game */
const std::string GAME_MUSIC =
    "res/musics/J.O.R.B.I_-_2.Dancing_of_the_Night.ogg";

/**
 * @brief returns the path of the music according to the controller id;
 * each controller has a specific music, this music is found using
 * this factory function
 *
 * @param id the id of the controller
 *
 * @return std::string
 */
std::string getMusicPathById(const unsigned short& id);
}
}

#endif
