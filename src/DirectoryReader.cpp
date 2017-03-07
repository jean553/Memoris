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
 * @file DirectoryReader.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DirectoryReader.hpp"

#include <cstring>
#include <stdexcept>

namespace memoris
{
namespace utils
{

/**
 *
 */
const std::vector<std::string> getFilesFromDirectory(
    const char* directory
)
{
    std::vector<std::string> list;

    /* this function uses a C library (dirent.h), so it also uses old-C++
       coding style (no smart pointer) */

    /* pointer to a custom type of dirent.h used for reading steps */
    struct dirent* reader = NULL;

    /* pointer to the object managing the directory reading */
    DIR* dir = opendir(directory);

    if (dir == NULL)
    {
        throw std::invalid_argument("Cannot open the given directory");
    }

    while((reader = readdir(dir)) != NULL)
    {
        /* std::string operator= accepts const char* types */
        std::string item = reader->d_name;

        /* remove the file extension from the file name */
        size_t extensionPosition = item.find_last_of(".");
        item = item.substr(0, extensionPosition);

        /* do not considere special returned values as the current folder and
           the parent folder */
        if (
            item == ".." ||
            item == "." ||
            item == ""
        )
        {
            continue;
        }

        list.push_back(item);
    }

    closedir(dir);

    return list;
}

}
}
