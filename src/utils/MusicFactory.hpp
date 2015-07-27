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
 * Factory which generates the musics.
 *
 * @file MusicFactory.hpp
 * @brief factory to generate the game musics
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_MUSIC_FACTORY
#define DEF_MUSIC_FACTORY

#include <string>

namespace factories {
class MusicFactory {

    static const std::string MAIN_MENU_MUSIC_PATH;

public:

    /**
     * @brief returns the music file
     * path according to the id
     *
     * @param id   id of the music
     *
     * @return string   music file path,
     * main menu music path by default
     */
    static std::string getMusicPathById(unsigned char id);
};
}

#endif
