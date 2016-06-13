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
 * @package musics
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "musics.hpp"
#include "ControllerFactory.hpp"

using namespace factories;

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
    case ControllerFactory::EDITOR_LEVEL_CONTROLLER_ID:
    case ControllerFactory::EDITOR_SERIE_CONTROLLER_ID:
    case ControllerFactory::OPEN_LEVEL_CONTROLLER_ID:
    case ControllerFactory::OPEN_SERIE_CONTROLLER_ID:
    {
        return EDITOR_MUSIC;
    }
    case ControllerFactory::GAME_CONTROLLER_ID:
    {
        return GAME_MUSIC;
    }
    }

    return MAIN_MENU_MUSIC;
}

}
}
