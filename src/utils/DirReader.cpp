/**
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
 * @file DirReader.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DirReader.hpp"

using namespace utils;

/**
 *
 */
std::vector<std::string> DirReader::getAllFiles(const char* directory)
{
    DIR *dir;
    struct dirent *file;
    std::vector<std::string> list;

    dir = opendir(directory);

    // returns an empty array if error
    if (dir == NULL) {
        return list;
    }

    while((file = readdir(dir)) != NULL) {
        std::string name(file->d_name);

        // exclude Linux parent and current folder
        if(name == ".." || name == ".") {
            continue;
        }

        list.push_back(name);
    }

    closedir(dir);
    return list;
}
