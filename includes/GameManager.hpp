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
 * @file GameManager.hpp
 * @brief handles creation and loading of game files
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAMEMANAGER_H_
#define MEMORIS_GAMEMANAGER_H_

#include <memory>

namespace memoris
{

namespace entities
{
    class Game;
}

namespace managers
{

class GameManager
{

public:

    /**
     * @brief constructor, empty, just declared to set the default value of
     * the game unique pointer to nullptr; this is an incomplete type, so it
     * cannot be initialized directly in the header
     */
    GameManager() noexcept;

    /**
     * @brief default destructor, only declared in this class in order to use
     * the forwarding declaration of entities::Game
     */
    ~GameManager() noexcept;

    /**
     * @brief creates a new game file on disk with the given name; loads the
     * game unique pointer with the created game
     *
     * @throw std::ios_base::failure thrown if the file manipulation failed;
     * this exception is never caught by the program and the game directly
     * stops
     *
     * the method is not constant because it modifies the Game unique pointer
     */
    void createGame(const std::string& name) &;

private:

    /* unique pointer to the current loaded game; this pointed object is
       initialized when a new game is created or when an existing game is
       loaded; if there is no need to have a game loaded at the moment,
       the pointer is just null; when the context is created, the main menu
       is rendered, at this moment, the game has no reason to be loaded */
    std::unique_ptr<entities::Game> game;

};

}
}

#endif
