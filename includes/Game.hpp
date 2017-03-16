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
 * @brief contains the current loaded game and game file information
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAME_H_
#define MEMORIS_GAME_H_

#include <memory>

#include <string>

namespace memoris
{
namespace entities
{

class Game
{

public:

    /**
     * @brief game entity constructor
     */
    Game();

    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    /**
     * @brief game loader function, loads all the parameters in memory
     *
     * @param constant reference to a string containing the file name (not
     * the full path)
     */
    void loadGameFromFile(const std::string& fileName) const & noexcept;

    /**
     * @brief deletes the game file
     */
    void deleteGameFile() const &;

    /**
     * @brief creates a new file for a new game
     *
     * @param gameName universal reference to the name of the game string
     *
     * @throw std::ios_base::failure the file cannot be written; the exception
     * is never caught and the program stops
     *
     * not defined inside the source file as it is a function template that
     * has universal references as parameters
     */
    template<typename T>
    void createGame(T&& gameName) const &
    {
        /* call std::string& operator=(std::string&&) or
           std::string& operator=(std::string&) */
        impl->gameName = std::forward<T>(gameName);

        createFile();
    }

    /**
     * @brief getter of the game name
     *
     * @return the name of the current loaded game
     */
    const std::string& getName() const & noexcept;

private:

    /**
     * @brief open the file using the given file name; only used internally
     * by the two definitions of createGame()
     *
     * @throw std::ios_base::failure the file cannot be written; the exception
     * is never caught and the program stops
     */
    void createFile() const &;

    static constexpr char GAMES_FILES_DIRECTORY[] {"data/games/"};
    static constexpr char GAMES_FILES_EXTENSION[] {".game"};

    /* the implementation definition is inside the header instead of the
       source file because createGame() needs it and createGame() cannot
       be defined inside the source file */
    class Impl
    {
    public:

        std::string gameName;
    };

    std::unique_ptr<Impl> impl;
};

}
}

#endif
