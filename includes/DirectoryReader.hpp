/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file DirectoryReader.hpp
 * @brief reads the content of a directory
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DIRECTORYREADER_H_
#define MEMORIS_DIRECTORYREADER_H_

#include <dirent.h>
#include <vector>
#include <string>

namespace memoris
{
namespace utils
{

/**
 * @brief returns a constant container with the name of all the files inside
 * the given directory; automatically delete the file type from the name
 *
 * @param directory path/name of the given directory
 *
 * @return const std::vector<std::string>
 *
 * @throws std::invalid_argument throws an exception if the directory cannot
 * be open or if an error occures (no matter what the error is); this
 * exception is never caught and the program just stops
 *
 * the returned container is returned by copy and not by reference: this
 * function is not a method and does not store the generated data; this method
 * is only used in order to refactor the logic used to find the files of a
 * directory
 */
const std::vector<std::string> getFilesFromDirectory(const char* directory);

}
}

#endif
