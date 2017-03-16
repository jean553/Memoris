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
 * @file allocators.hpp
 * @brief dynamic allocation routines
 * @package allocators
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ALLOCATORS_H_
#define MEMORIS_ALLOCATORS_H_

#include <memory>

namespace memoris
{
namespace allocators
{

/* NOTE: different objects in Memoris require dynamic management; that's why
   we refactor the management in those functions */

/**
 * @brief dynamically create an object pointed by the given unique pointer
 *
 * @param pointer unique pointer to use
 */
template<typename T>
void createDynamicObject(std::unique_ptr<T>& pointer);

/**
 * @brief dynamically delete an object pointed by the given unique pointer
 *
 * @param pointer unique pointer to use
 */
template<typename T>
void deleteDynamicObject(std::unique_ptr<T>& pointer);

}
}

#endif
