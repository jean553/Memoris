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
 * @file Cursor.hpp
 * @brief graphical cursor displayed into the editor
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CURSOR_H_
#define MEMORIS_CURSOR_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class Cursor
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the current context
     */
    Cursor(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~Cursor() noexcept;

    /**
     * @brief render the cursor on the screen
     *
     * @param context reference to the current context
     */
    void render(const utils::Context& context);

private:

    /**
     * @brief updates position of the cursor SFML surface according to the
     * real cursor position; this function has been created for organization
     * purposes as it is called from two different locations in the code
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateCursorPosition() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
