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
 * @brief class that stores the properties of one game
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAME_H_
#define MEMORIS_GAME_H_

#include <string>

namespace memoris
{
namespace entities
{

class Game
{

public:

    /**
     * @brief constructor, creates the new game file
     *
     * @param gameName string that represents the name of the game; the user
     * uses this name to find an existing game or to create a new one
     *
     * @throw std::ios_base::failure thrown if the file manipulation failed;
     * this exception is never caught by the program and the game directly
     * stops
     *
     */
    Game(const std::string& gameName);

private:

    /* PIMPL is not used here: <string> is included in <memory> */

    std::string name;
};

}
}

#endif
