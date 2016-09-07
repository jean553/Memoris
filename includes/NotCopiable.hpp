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
 * @path NotCopiable.hpp
 * @brief abstract parent class for all non copiable objects classes
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_NOTCOPIABLE_H_
#define MEMORIS_NOTCOPIABLE_H_

namespace memoris
{
namespace utils
{

class NotCopiable
{

public:

    /* the deleted methods are public because any part of the program could
       try to perform a copy of a NotCopiable object */

    /**
     * @brief makes the copy constructor a deleted function: no children class
     * is able to copy the object by this way
     *
     * @param other constant reference to the object to copy
     */
    NotCopiable(const NotCopiable& other) = delete;

    /**
     * @brief makes the assignment operator a deleted function: no children
     * class is able to copy the object by this way
     *
     * @param other constant reference to the object to copy
     *
     * @return NotCopiable&
     */
    NotCopiable& operator=(const NotCopiable& other) = delete;

protected:

    /**
     * @brief pure virtual destructor to make the class abstract; we use that
     * pattern because there is no other method that can be declared as pure
     * virtual functions in this class
     *
     * not 'noexcept', NotCopiable can be applied to any class, so we do not
     * guarantee in the current sementic that all the destructors in
     * NotCopiable children won't throw any exception
     */
    virtual ~NotCopiable() = 0;

    /* the default constructor is protected, because no instance of the
       current class can be created if the children cannot access their parent
       default constructor; the virtual destructor is also protected because
       it also has to be accessible from the children objects, as it has to
       be redefined there in the purpose of ensuring abstraction mechanism */

    /**
     * @brief default constructor, must be explicitly declared with 'default'
     * because it is not automatically added when the class contains at least
     * one deleted method
     */
    NotCopiable() = default;
};

}
}

#endif
