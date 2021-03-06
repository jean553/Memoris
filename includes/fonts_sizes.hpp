/**
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
 * @file fonts_sizes.hpp
 * @brief contains commons fonts sizes, used by many different texts
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_FONTSSIZE_H_
#define MEMORIS_FONTSSIZE_H_

namespace memoris
{
namespace sizes
{

/* NOTE: we use unsigned int for every size, as this is the data type
   expected by SFML font size function */

constexpr unsigned int SUB_TITLE_SIZE {70};
constexpr unsigned int TEXT_SIZE {50};

}
}

#endif
