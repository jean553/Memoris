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
 * @file DirReader.hpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_DIRREADER
#define DEF_DIRREADER

#include <string>
#include <vector>
#include <dirent.h>

namespace utils {
class DirReader {

public:

    /**
     * @brief returns a list of all the files in a directory,
     * returns an empty array if an error occured
     *
     * @param directory     characters pointer, directory to open
     *
     * @return vector<string>
     */
    std::vector<std::string> getAllFiles(const char* directory);
};
}

#endif
