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
 * @file AbstractForeground.hpp
 * @brief parent interface for foregrounds
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTFOREGROUND_H_
#define MEMORIS_ABSTRACTFOREGROUND_H_

namespace memoris
{

namespace utils
{
class Context;
}

namespace foregrounds
{

class AbstractForeground
{

protected:

    /**
     * @brief default destructor
     */
    virtual ~AbstractForeground() = default;

    /**
     * @brief renders the foreground in front of the controller screen
     *
     * @param context the context to use
     *
     * not noexcept because children will use SFML methods for sure
     */
    virtual void render(const utils::Context& context) const & = 0;
};

}
}

#endif
