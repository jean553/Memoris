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
 * Sounds.
 *
 * @file Sounds.hpp
 * @brief path of all the sounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SOUNDS
#define DEF_SOUNDS

#include <string>

namespace constants {
class Sounds {

public:

    static const std::string MOVE_SELECTOR_SOUND_PATH;
    static const std::string SCREEN_TRANSITION_SOUND_PATH;
    static const std::string CELL_SELECTOR_SELECTION_SOUND_PATH;
};
}

#endif
