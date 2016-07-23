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
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PlayingSerieManager.hpp"

#include <fstream>
#include <stdexcept>

namespace memoris
{
namespace series
{

/**
 *
 */
PlayingSerieManager& PlayingSerieManager::get()
{
    /* creates the static single instance of the playing serie manager */
    static PlayingSerieManager singleton;

    /* return the unique instance of the playing serie manager */
    return singleton;
}

/**
 *
 */
void PlayingSerieManager::loadSerieFileContent(const std::string& path)
{
    /* creates an object to read the file and pass the given path */
    std::ifstream file(path);

    /* check if the file has been opened correctly */
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

    /* this string is a buffer used to store each line of the file one by
       one */
    std::string level;

    /* read the file line by line */
    while(std::getline(file, level))
    {
        /* insert each level string into the container */
        levels.push(level);
    }

    /* this is useless to close the std::ifstream object, it is automatically
       destroyed when the object goes out of the scope */
}

}
}
