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

#include "Context.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace items
{

class MenuItem
{

public:

    /**
     * @brief constructor, generates a SFML text object with the given
     * string label at the specified location; automatically applies the
     * default color, font and font size ( same for all the menu items )
     *
     * @param context shared pointer to the current context
     * @param label the menu item text label
     * @param horizontalPosition the horizontal position of the text
     * @param verticalPosition the vertical position of the text
     */
    MenuItem(
        const std::shared_ptr<utils::Context>& context,
        const std::string& label,
        const float& horizontalPosition,
        const float& verticalPosition
    );

    /**
     * @brief display the menu item inside the given context; displays the
     * item in the correct color
     *
     * @param context shared pointer ot the current context to use
     */
    void render(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief unselect the menu item, make it white
     *
     * @param context shared pointer to the current context
     */
    void unselect(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief select the menu item, make it red
     *
     * @param context shared pointer to the current context
     */
    void select(const std::shared_ptr<utils::Context>& context);

private:

    /* the SFML text object; a menu item is a SFML text with specific
       properties */
    sf::Text text;
};

}
}

#endif
