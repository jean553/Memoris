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
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace items
{

class MenuItem::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::string& label,
        const float& horizontalPosition,
        const float& verticalPosition
    )
    {
        text.setString(label);
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(fonts::ITEM_SIZE);
        text.setPosition(
            horizontalPosition,
            verticalPosition
        );
    }

    sf::Text text;
};

/**
 *
 */
MenuItem::MenuItem(
    const utils::Context& context,
    const std::string& label,
    const float& horizontalPosition,
    const float& verticalPosition
) :
    impl(
        std::make_unique<Impl>(
            context,
            label,
            horizontalPosition,
            verticalPosition
        )
    )
{
    unselect(context);
}

/**
 *
 */
MenuItem::~MenuItem() noexcept = default;

/**
 *
 */
void MenuItem::render(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->text);
}

/**
 *
 */
void MenuItem::unselect(const utils::Context& context) &
{
    impl->text.setColor(context.getColorsManager().getColorWhite());
}

/**
 *
 */
void MenuItem::select(const utils::Context& context) &
{
    impl->text.setColor(context.getColorsManager().getColorRed());
}

}
}
