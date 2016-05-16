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
 * @file MusicFactory.cpp
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MusicFactory.hpp"

#include "ControllerFactory.hpp"

using namespace factories;

const std::string MusicFactory::MAIN_MENU_MUSIC_PATH = "res/musics/pokki-dj-made-in-italy.ogg";
const std::string MusicFactory::EDITOR_MUSIC_PATH = "res/musics/bigmanboo-back-to-the-90s-nostalgia.ogg";
const std::string MusicFactory::GAME_MUSIC_PATH = "res/musics/J.O.R.B.I_-_2.Dancing_of_the_Night.ogg";

/**
 *
 */
std::string MusicFactory::getMusicPathById(
    unsigned short id
)
{
    /**
     * NOTE: I could use a switch/case here instead of if/else, but the
     * constants are not constant expressions ( case only accept constant
     * expressions ),as they are declared as const at the ControllerFactory
     * class level. I might declare them as constexpr but I will have to
     * initialize them in the header, and I prefer to initialize them in
     * the source for compilation purposes.
     */
    if (
        id == ControllerFactory::EDITOR_LEVEL_CONTROLLER_ID ||
        id == ControllerFactory::EDITOR_SERIE_CONTROLLER_ID ||
        id == ControllerFactory::OPEN_LEVEL_CONTROLLER_ID ||
        id == ControllerFactory::OPEN_SERIE_CONTROLLER_ID
    )
    {
        return EDITOR_MUSIC_PATH;
    }
    else if (id == ControllerFactory::GAME_CONTROLLER_ID)
    {
        return GAME_MUSIC_PATH;
    }

    return MAIN_MENU_MUSIC_PATH;
}
