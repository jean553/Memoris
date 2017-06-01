/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @file Game.hpp
 * @package entities
 * @brief handles game file creation and deletion
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAME_H_
#define MEMORIS_GAME_H_

#include <memory>

namespace memoris
{
namespace entities
{

class Game
{

public:

    /**
     * @brief constructor
     */
    Game();

    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    /**
     * @brief default destructor
     */
    ~Game();

    /**
     * @brief deletes the game file
     */
    void deleteGameFile() const &;

    /**
     * @brief getter of the game name
     *
     * @return const std::string&
     */
    const std::string& getName() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
