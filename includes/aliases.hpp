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
 * @file aliases.hpp
 * @brief contains the types aliases
 * @package aliases
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ALIASES_H_
#define MEMORIS_ALIASES_H_

#include <memory>
#include <vector>

namespace sf
{
class Transform;
}

namespace memoris
{

namespace entities
{
class Cell;
}

namespace aliases
{

/* reference of an unique pointer to a SFML transform object */
using ConstTransformUniquePtrRef = const std::unique_ptr<sf::Transform>&;

/* constant reference to a container of unique pointers on Cell objects */
using ConstUniquePtrCellsContainerRef =
    const std::vector<std::unique_ptr<entities::Cell>>&;

}
}

#endif
