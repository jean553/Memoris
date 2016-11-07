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
 * @file window.hpp
 * @brief namespace for SFML window dimensions, resolution and title
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WINDOW_H_
#define MEMORIS_WINDOW_H_

#include <string>

namespace memoris
{
namespace window
{

/* unsigned int because the RenderWindow constructor excepts unsigned int */

constexpr unsigned int WIDTH = 1600;
constexpr unsigned int HEIGHT = 900;
constexpr unsigned int RESOLUTION = 32;

/* extern to be sure that we only declare them one time */

extern const std::string TITLE;

}
}

#endif
