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
 * @file MenuItem.hpp
 * @brief represents one menu item in abstract menu controller class
 * @package items
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MENUITEM_H_
#define MEMORIS_MENUITEM_H_

#include <memory>

#include <SFML/Config.hpp>

namespace sf
{
class Text;
}

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
     * @brief used to specify the horizontal position of the menu item, which
     * can be centered or on the left
     *
     * public because it may be accessed from menus controllers
     */
    enum class HorizontalPosition {
        Center, /** < the position is centered (default) */
        Left /** < the position is left */
    };

    /**
     * @brief constructor, generates a SFML text object with the given
     * string label at the specified location; automatically applies the
     * default color, font and font size ( same for all the menu items )
     *
     * @param context reference to the current context
     * @param label the menu item text label
     * @param verticalPosition the vertical position of the text
     * @param position horizontal position of the item (centered by default)
     */
    MenuItem(
        const utils::Context& context,
        const std::string& label,
        const float& verticalPosition,
        const HorizontalPosition& position = HorizontalPosition::Center
    );

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~MenuItem() noexcept;

    /**
     * @brief display the menu item inside the given context; displays the
     * item in the correct color and handles the item animation if selected
     *
     * @param context shared pointer ot the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void render(const utils::Context& context) const &;

    /**
     * @brief unselect the menu item, make it white
     *
     * @param context reference to the current context
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void unselect(const utils::Context& context) const &;

    /**
     * @brief select the menu item, make it red
     *
     * @param context reference to the current context
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void select(const utils::Context& context) const &;

private:

    static constexpr sf::Uint32 ANIMATION_INTERVAL {500};

    static constexpr float LEFT_HORIZONTAL_POSITION {10.f};

    /**
     * @brief display the menu item on the SFML window; this action is
     * required multiple times, so, it is refactored into this private method
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void display(const utils::Context& context) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
