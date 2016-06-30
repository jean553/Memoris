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
 * @file NotCopiable.hpp
 * @brief declare copy constructor and overload copy operator
 * without any definition, just to prevent their definitions;
 * disallow the class objects copy; used for singletons
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_NOTCOPIABLE_H_
#define MEMORIS_NOTCOPIABLE_H_

namespace memoris
{
namespace others
{

class NotCopiable
{

protected:

    /**
     * @brief default constructor
     */
    NotCopiable();

    /**
     * @brief copy constructor declaration, blocks
     * definition by a child class
     */
    NotCopiable(const NotCopiable& foo);

    /**
     * @brief copy operator overload, blocks definition
     * by a child class
     */
    NotCopiable& operator=(const NotCopiable& foo);
};

}
}

#endif
