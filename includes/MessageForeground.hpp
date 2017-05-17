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
 * @file MessageForeground.hpp
 * @brief contains a simple message
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MESSAGEFOREGROUND_H_
#define MEMORIS_MESSAGEFOREGROUND_H_

#include "AbstractForeground.hpp"

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace foregrounds
{

class MessageForeground : public AbstractForeground
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param message the message to display
     */
    MessageForeground(
        const utils::Context& context,
        const std::string&& message
    );

    /**
     * @brief default destructor
     */
    ~MessageForeground();

    /**
     * @brief renders the foreground in front of the controller screen
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    virtual void render() const & override final;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
