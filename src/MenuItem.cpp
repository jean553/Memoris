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
 * @file MenuItem.cpp
 * @package items
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MenuItem.hpp"

#include "fonts.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"

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
        const float& verticalPosition
    ) :
        context(context)
    {
        text.setString(label);
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(fonts::ITEM_SIZE);
    }

    sf::Text text;

    const utils::Context& context;
};

/**
 *
 */
MenuItem::MenuItem(
    const utils::Context& context,
    const std::string& label,
    const float& verticalPosition,
    const HorizontalPosition& position
) :
    impl(
        std::make_unique<Impl>(
            context,
            label,
            verticalPosition
        )
    )
{
    constexpr float LEFT_HORIZONTAL_POSITION {10.f};
    impl->text.setPosition(
        position == HorizontalPosition::Center ?
            window::getCenteredSfmlSurfaceHorizontalPosition(impl->text) :
                LEFT_HORIZONTAL_POSITION,
        verticalPosition
    );

    unselect();
}

/**
 *
 */
MenuItem::~MenuItem() = default;

/**
 *
 */
void MenuItem::render() const &
{
    impl->context.getSfmlWindow().draw(impl->text);
}

/**
 *
 */
void MenuItem::unselect() const &
{
    impl->text.setColor(impl->context.getColorsManager().getColorWhite());
}

/**
 *
 */
void MenuItem::select() const &
{
    impl->text.setColor(impl->context.getColorsManager().getColorRed());
}

}
}
