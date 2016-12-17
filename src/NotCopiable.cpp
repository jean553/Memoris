/**
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
 * @path NotCopiable.hpp
 * @brief abstract parent class for all non copiable objects classes
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "NotCopiable.hpp"

namespace memoris
{
namespace utils
{

/**
 * we separate the definition from the declaration; there
 * is no other way to declare a default pure virtual destructor
 */
NotCopiable::~NotCopiable() = default;

}
}
