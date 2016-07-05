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
 * @file intervals.hpp
 * @brief contains controllers animations intervals
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_INTERVALS_H_
#define MEMORIS_INTERVALS_H_

#include <SFML/System.hpp>

namespace memoris
{
namespace intervals
{

/* the common interval in milliseconds for almost all the animations of the
   game is 10 milliseconds */
constexpr sf::Uint32 COMMON_ANIMATIONS_MILLISECONDS_INTERVAL = 10;
}
}

#endif
