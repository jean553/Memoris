/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file musics.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "musics.hpp"
#include "controllers.hpp"

namespace memoris
{
namespace musics
{

/**
 *
 */
const std::string getMusicPathById(const controllers::ControllerId& id)
{
    /* NOTE: directly set the files paths inside the code, without any
       constant declaration; in fact, this code is explicit enough */

    switch(id)
    {
    case controllers::ControllerId::Game:
    {
        /* there is multiple std::string copies here, but we allow it anyway */
        return getRandomGameMusicPath();
    }
    break;
    /* by default, if the controller id does not exist, the main
       menu music is played; it avoids mistakes in screens transitions;
       NOTE: the controllers factory also returns the main menu controller
       if an incorrect controller id is specified */
    default:
    {
        return "res/musics/Zeropage_-_Ambient_Dance.ogg";
    }
    }
}

/**
 *
 */
const std::string getRandomGameMusicPath()
{
    /* we use int because rand() returns an integer */
    constexpr unsigned int MAXIMUM_RANDOM_GAME_MUSIC {2};
    unsigned int randomNumber = rand() % MAXIMUM_RANDOM_GAME_MUSIC;

    if (randomNumber == 0)
    {
        return "res/musics/Zeropage_-_Void_Sensor.ogg";
    }

    return "res/musics/Zeropage_-_Ambiose.ogg";
}

}
}
