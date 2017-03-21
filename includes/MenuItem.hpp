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
 * @file MenuItem.hpp
 * @brief one menu selectable item
 * @package items
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MENUITEM_H_
#define MEMORIS_MENUITEM_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace items
{

class MenuItem
{

public:

    /**
     * @enum MenuItem::HorizontalPosition
     * @brief menu items can be displayed on the left or at the center
     *
     * public because it may be accessed from menus controllers
     */
    enum class HorizontalPosition {
        Center, /** < the position is centered (default) */
        Left /** < the position is left */
    };

    /**
     * @brief constructor
     *
     * @param context the current context
     * @param label displayed text
     * @param verticalPosition text vertical position
     * @param horizontalPosition defined horizontal position
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    MenuItem(
        const utils::Context& context,
        const std::string& label,
        const float& verticalPosition,
        const HorizontalPosition& horizontalPosition =
            HorizontalPosition::Center
    );

    /**
     * @brief default destructor
     */
    ~MenuItem();

    /**
     * @brief displays the menu item
     *
     * not noexcept because it calls SFML window draw() that is not noexcept
     */
    void render() const &;

    /**
     * @brief unselect the menu item, make it white
     *
     * not noexcept because it calls SFML setColor() that is not noexcept
     */
    void unselect() const &;

    /**
     * @brief select the menu item, make it red
     *
     * not noexcept because it calls SFML setColor() that is not noexcept
     */
    void select() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
