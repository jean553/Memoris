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

#include "Level.hpp"

#include <string>
#include <vector>

namespace utils
{
class FileWriter
{

public:

    /**
     * @brief copy a string in a given file
     *
     * @param fileName path and name of the file
     * @param content string to write
     *
     * @return bool
     */
    static bool writeFile(
        std::string fileName,
        std::string content = ""
    );

    /**
     * @brief get file content into one string ( one shot )
     *
     * @param fileName name of the file to read
     *
     * @return string file content
     */
    static std::string readFile(const std::string& fileName);

    /**
     * @brief get file content and store it inside a vector of strings,
     * the considered separator is the pipe
     *
     * @param filePath path of the file to open
     *
     * @return std::vector<std::string>
     */
    static std::vector<std::string> readFileWithSprt(const std::string& filePath);
};
}

#endif
