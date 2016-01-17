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
 * @file FileWriter.hpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_FILEWRITER
#define DEF_FILEWRITER

#include <string>
#include <vector>

namespace utils {
class FileWriter {

public:

    /**
     * @brief write a strings list into a file and separate
     * each strings by a break line into the file
     *
     * TODO: #162 - define the content of the method
     */
    static void writeStringsListIntoFile();

    /**
     * @brief create a new file with the given name
     *
     * @param fileName path and name of the file starting from data directory
     *
     * @return bool
     */
    static bool createFile(std::string fileName);
};
}

#endif
