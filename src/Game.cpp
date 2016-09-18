/*
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
 * @file Game.cpp
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Game.hpp"

#include <fstream>

namespace memoris
{
namespace entities
{

/**
 *
 */
Game::Game(const std::string& gameName) :
    name(gameName)
{
    std::ofstream file;

    /* throw exception if IO error */
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    file.open(
        "data/games/" + name + ".game",
        std::fstream::out
    );

    /* manually close the file is not necessary as std::ofstream is
       automatically destroyed when it leaves the current scope */
}

}
}