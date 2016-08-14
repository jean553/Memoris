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
 * @file MenuItem.cpp
 * @package items
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MenuItem.hpp"

#include "fonts.hpp"
#include "Context.hpp"

namespace memoris
{
namespace items
{

/**
 *
 */
MenuItem::MenuItem(
    const std::shared_ptr<utils::Context>& context,
    const std::string& label,
    const float& horizontalPosition,
    const float& verticalPosition
)
{
    /* the displayed text of the item is the given label */
    text.setString(label);

    /* set the common menu item font */
    text.setFont(context->getFontsManager().getTextFont());

    /* common font size for all the menu items */
    text.setCharacterSize(fonts::ITEM_SIZE);

    /* the position of the text is the given one */
    text.setPosition(
        horizontalPosition,
        verticalPosition
    );

    /* the default color when the item is unselected is white */
    unselect(context);
}

/**
 *
 */
void MenuItem::render(const std::shared_ptr<utils::Context>& context)
{
    context->getSfmlWindow().draw(text);
}

/**
 *
 */
void MenuItem::unselect(const std::shared_ptr<utils::Context>& context)
{
    /* the menu item is white when unselected */
    text.setColor(context->getColorsManager().getColorWhite());
}

/**
 *
 */
void MenuItem::select(const std::shared_ptr<utils::Context>& context)
{
    /* the menu item is red when selected */
    text.setColor(context->getColorsManager().getColorRed());
}

}
}
