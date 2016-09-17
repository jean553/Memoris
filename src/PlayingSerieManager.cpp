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
#include <string>
#include <queue>

namespace memoris
{
namespace managers
{

class PlayingSerieManager::Impl
{

public:

    /* we use the FIFO (first in first out) method to store the levels names;
       in fact, we add all the levels one by one into the container when we
       load a serie and we pop them one by one in the same order; the queue
       container is directly optimized for that kind of operations */
    std::queue<std::string> levels;

    /* current watching time that will be given for the next level; this time
       is the watching time *per floor*; this value is set to 6 by default
       all the time when a serie starts; we set it here because this value
       has to be transferred from one level to another */
    unsigned short watchingTime {6};
};

/**
 *
 */
PlayingSerieManager::PlayingSerieManager() noexcept :
impl(std::make_unique<Impl>())
{
}

/**
 *
 */
PlayingSerieManager::~PlayingSerieManager() noexcept = default;

/**
 *
 */
const bool PlayingSerieManager::hasNextLevel() const & noexcept
{
    if (impl->levels.empty())
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
    return impl->watchingTime;
}

/**
 *
 */
const size_t PlayingSerieManager::getRemainingLevelsAmount() const & noexcept
{
    return impl->levels.size();
}

/**
 *
 */
const std::string PlayingSerieManager::getNextLevelName() & noexcept
{
    /* get the front item of the queue and delete it from the container */
    std::string level = impl->levels.front();
    impl->levels.pop();

    return level;
}

/**
 *
 */
void PlayingSerieManager::setWatchingTime(const unsigned short& time) &
noexcept
{
    impl->watchingTime = time;
}

/**
 *
 */
void PlayingSerieManager::loadSerieFileContent(const std::string& path) &
{
    /* clear the queue */
    impl->levels = std::queue<std::string>();

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
        impl->levels.push(level);
    }

    /* this is useless to close the std::ifstream object, it is automatically
       destroyed when the object goes out of the scope */
}

}
}
