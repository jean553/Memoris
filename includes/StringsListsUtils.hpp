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
 * @file StringsListsUtils.hpp
 * @brief routines for strings lists
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_STRINGS_LISTS_UTILS
#define DEF_STRINGS_LISTS_UTILS

#include <vector>
#include <string>

namespace utils
{
class StringsListsUtils
{

public:

    /**
     * @brief checks if a string is contained
     * inside a strings lists
     *
     * @param list contains all the strings for checking
     * @param value the string to search in the given list
     *
     * @return true if the value is in the list, false if
     * the value is not in the given list
     */
    static bool stringsListContainsString(
        std::vector<std::string> list,
        std::string value
    );

    /**
     * @brief returns the amount of sub string inside a parent string
     *
     * @param mainString parent string
     * @param subString sub-string to find in the parent one
     *
     * @return amount of sub-string inside parent string
     */
    static unsigned int getSubStringAmountInString(
        std::string mainString,
        std::string subString
    );
};
}

#endif
