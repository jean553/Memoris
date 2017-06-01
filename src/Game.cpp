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
 * @file Game.cpp
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Game.hpp"

#include <string>
#include <fstream>

namespace memoris
{
namespace entities
{

constexpr char GAMES_FILES_DIRECTORY[] {"data/games/"};
constexpr char GAMES_FILES_EXTENSION[] {".game"};

class Game::Impl
{
public:

    std::string gameName;
};

/**
 *
 */
Game::Game() : impl(std::make_unique<Impl>())
{
}

/**
 *
 */
Game::~Game() = default;

/**
 *
 */
void Game::createGame(const std::string& gameName) const &
{
    impl->gameName = gameName;

    std::ofstream file;

    file.open(
        GAMES_FILES_DIRECTORY + impl->gameName + GAMES_FILES_EXTENSION,
        std::fstream::out
    );
}

/**
 *
 */
void Game::deleteGameFile() const &
{
    std::string filePath =
        GAMES_FILES_DIRECTORY + impl->gameName + GAMES_FILES_EXTENSION;

    /* TODO: #931 check if the file deletion succeeds */
    std::remove(filePath.c_str());
}

/**
 *
 */
const std::string& Game::getName() const & noexcept
{
    return impl->gameName;
}

}
}
