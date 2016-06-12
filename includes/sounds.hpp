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
 * @file sounds.hpp
 * @bried contains all the sound file paths
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SOUNDS_H_
#define MEMORIS_SOUNDS_H_

#include <string>

namespace memoris
{
namespace sounds
{
/* NOTE: the strings cannot be declared as constant expressions */

/* sound to play when the controllers are switched */
const std::string SCREEN_TRANSITION_SOUND = "res/sounds/002.wav";
}
}

#endif
