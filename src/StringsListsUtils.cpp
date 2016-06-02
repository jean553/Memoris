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
 * @file StringsListsUtils.cpp
 * @brief routines for strings lists
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "StringsListsUtils.hpp"

#include <algorithm>
#include <sstream>
#include <string>

using namespace utils;

const std::string StringsListsUtils::LVLS_DIR = "data/levels/";
const std::string StringsListsUtils::LVLS_EXT = ".level";

/**
 *
 */
bool StringsListsUtils::stringsListContainsString(std::vector<std::string> list, std::string value)
{
    if (find(list.begin(), list.end(), value) != list.end())
    {
        return true;
    }

    return false;
}

/**
 *
 */
unsigned int StringsListsUtils::getSubStringAmountInString(
    std::string mainString,
    std::string subString
)
{
    const size_t step = subString.size();
    size_t currentPosition = 0;
    unsigned int counter = 0;

    while ((currentPosition = mainString.find(subString, currentPosition)) != std::string::npos)
    {
        currentPosition += step;
        ++counter;
    }

    return counter;
}

/**
 *
 */
std::vector<std::string> StringsListsUtils::splitString(
    std::string strToSplt,
    const char& sprt
)
{
    std::vector<std::string> arr;

    /* replace separator by blank spaces */
    for (uint8_t i = 0; i < strToSplt.length(); i++)
    {
        if (strToSplt[i] == sprt)
        {
            strToSplt[i] = ' ';
        }
    }

    /* stringstream can 'see' the strings separated by blank space */
    std::stringstream stream(strToSplt);
    std::string tmp;

    /* each string can now be accessed by iterating the string stream */
    while (stream >> tmp)
    {
        arr.push_back(LVLS_DIR + tmp + LVLS_EXT);
    }

    return arr;
}
