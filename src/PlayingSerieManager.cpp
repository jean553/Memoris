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
 * @file PlayingSerieManager.hpp
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PlayingSerieManager.hpp"

#include <fstream>
#include <stdexcept>

namespace memoris
{
namespace managers
{

/**
 *
 */
const bool PlayingSerieManager::hasNextLevel() const & noexcept
{
    if (levels.empty())
    {
        return false;
    }

    return true;
}

/**
 *
 */
const unsigned short& PlayingSerieManager::getWatchingTime() const & noexcept
{
    return watchingTime;
}

/**
 *
 */
const size_t PlayingSerieManager::getRemainingLevelsAmount() const & noexcept
{
    return levels.size();
}

/**
 *
 */
const std::string PlayingSerieManager::getNextLevelName() & noexcept
{
    /* get the front item of the queue and delete it from the container */
    std::string level = levels.front();
    levels.pop();

    return level;
}

/**
 *
 */
void PlayingSerieManager::setWatchingTime(const unsigned short& time) &
noexcept
{
    watchingTime = time;
}

/**
 *
 */
void PlayingSerieManager::loadSerieFileContent(const std::string& path) &
{
    /* clear the queue */
    levels = std::queue<std::string>();

    std::ifstream file(path);
    if (!file.is_open())
    {
        /* TODO: #561 throw std::invalid_argument if the file cannot be opened;
           we could use file.exception(failbit) to directly throw an exception
           if the file cannot be loaded, but the problem is that it also
           throw an exception when the end of the file is found (eof); for now
           I do not know how to walk-around this problem, but this second
           solution would be better to also handle the file reading safely */
        throw std::invalid_argument("Cannot open the given serie file.");
    }

    /* string buffer */
    std::string level;

    /* read the file one by one and add the levels names into the queue */
    while(std::getline(file, level))
    {
        levels.push(level);
    }

    /* this is useless to close the std::ifstream object, it is automatically
       destroyed when the object goes out of the scope */
}

}
}
