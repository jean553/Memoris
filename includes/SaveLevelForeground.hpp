/*
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
 * @file SaveLevelForeground.hpp
 * @brief contains one text line widget to let the user inputs one level name
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SAVELEVELFOREGROUND_H_
#define MEMORIS_SAVELEVELFOREGROUND_H_

#include "AbstractForeground.hpp"

#include <memory>

namespace memoris
{
namespace foregrounds
{

class SaveLevelForeground : public AbstractForeground
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    SaveLevelForeground(const utils::Context& context);

    /**
     * @brief default destructor, declared in order to use forwarding
     * declaration
     */
    ~SaveLevelForeground() noexcept;

    /**
     * @brief renders the foreground in front of the controller screen
     *
     * @param context constant reference to the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void render(const utils::Context& context) const & override final;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
