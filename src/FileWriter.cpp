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
 * @file FileWriter.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FileWriter.hpp"
#include "Cell.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace utils;

/**
 *
 */
bool FileWriter::writeFile(
    std::string fileName,
    std::string content
)
{
    std::ofstream file(fileName, std::ofstream::out);

    if (!file.is_open())
    {
        return false;
    }

    file << content;

    file.close();

    return true;
}

/**
 *
 */
std::string FileWriter::readFile(const std::string& fileName)
{
    std::ifstream file;
    std::string cellsString;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(fileName);

        cellsString.assign(
            (std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>())
        );

        file.close();
    }
    catch (const std::ifstream::failure& f)
    {
        throw std::invalid_argument("Cannot open the level " + fileName);
    }

    return cellsString;
}
