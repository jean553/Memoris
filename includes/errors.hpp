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
 * @file errors.hpp
 * @brief contains error messages
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ERRORS_H_
#define MEMORIS_ERRORS_H_

#include <SFML/System/String.hpp>

namespace memoris
{
namespace errors
{

/* SFML strings objects cannot be declared as constant expressions */

const sf::String UNLOCKED_SERIE = "This serie is locked. \
    Finish the previous series first.";

const sf::String CANNOT_OPEN_LEVEL = "Cannot open level file.";

}
}

#endif
