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
 * @file musics.hpp
 * @brief contains the musics files paths and one function
 * to get each path by controller id
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MUSICFACTORY_H_
#define MEMORIS_MUSICFACTORY_H_

#include <string>

namespace memoris
{

namespace controllers
{
enum class ControllerId;
}

namespace musics
{

/**
 * @brief returns the path of the music according to the controller id;
 * each controller has a specific music, this music is found using
 * this factory function
 *
 * @param id controller id
 *
 * @return const std::string
 */
const std::string getMusicPathById(const controllers::ControllerId& id);

}
}

#endif
