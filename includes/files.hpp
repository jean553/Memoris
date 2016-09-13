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
 * @file files.hpp
 * @brief routines to apply on many STD files objects
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_FILES_H_
#define MEMORIS_FILES_H_

#include <fstream>

namespace memoris
{
namespace utils
{

/**
 * @brief set an exception policy on a given std::ofstream reference; applies
 * the failbit and badbit
 *
 * @param file std::ofstream object on which one the exceptions policy must
 * be applied
 */
void applyFailbitAndBadbitExceptions(std::ofstream& file);

}
}

#endif
