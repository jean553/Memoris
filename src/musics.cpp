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
std::string getMusicPathById(const unsigned short& id)
{
    switch(id)
    {
    case controllers::EDITOR_LEVEL_CONTROLLER_ID:
    case controllers::EDITOR_SERIE_CONTROLLER_ID:
    case controllers::OPEN_LEVEL_CONTROLLER_ID:
    case controllers::OPEN_SERIE_CONTROLLER_ID:
    {
        return EDITOR_MUSIC;
    }
    break;
    case controllers::GAME_CONTROLLER_ID:
    {
        return GAME_MUSIC;
    }
    break;
    /* by default, if the controller id does not exist, the main
       menu music is played; it avoids mistakes in screens transitions;
       NOTE: the controllers factory also returns the main menu controller
       if an incorrect controller id is specified */
    default:
    {
        return MAIN_MENU_MUSIC;
    }
    }
}

}
}
