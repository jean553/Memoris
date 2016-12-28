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
 * @file OpenFileForeground.hpp
 * @brief contains one selection list widget
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_OPENFILEFOREGROUND_H_
#define MEMORIS_OPENFILEFOREGROUND_H_

#include "AbstractForeground.hpp"

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{
class SelectionListWidget;
}

namespace foregrounds
{

class OpenFileForeground : public AbstractForeground
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the context to use
     * @param path constant rvalue reference to the directory of the files
     * to list
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    OpenFileForeground(
        const utils::Context& context,
        const std::string&& path
    );

    /**
     * @brief default destructor, declared in order to use forwarding
     * declaration
     */
    ~OpenFileForeground() noexcept;

    /**
     * @brief renders the foreground in front of the controller screen
     *
     * @param context constant reference to the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    virtual void render(const utils::Context& context) const & override final;

    /**
     * @brief getter of a constant reference to the list widget
     *
     * @return const widgets::SelectionListWidget&
     */
    const widgets::SelectionListWidget& getList() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
