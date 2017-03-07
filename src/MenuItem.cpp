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
    )
    {
        text.setString(label);
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(fonts::ITEM_SIZE);

        selectedColor.r = 255;
        selectedColor.g = 0;
        selectedColor.b = 0;
        selectedColor.a = 255;
    }

    sf::Text text;

    bool selected {false};

    sf::Uint32 lastUpdateTime {0};

    sf::Color selectedColor;

    short colorUpdateStep {17}; // (15 steps) 255 / 15 = 17
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
    impl->text.setPosition(
        position == HorizontalPosition::Center ?
            window::getCenteredSfmlSurfaceHorizontalPosition(impl->text) :
            LEFT_HORIZONTAL_POSITION
            ,
        verticalPosition
    );

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
    if (
        !impl->selected or
        context.getClockMillisecondsTime() - 
            impl->lastUpdateTime > ANIMATION_INTERVAL
    )
    {
        display(context);

        return;
    }

    impl->selectedColor.g += impl->colorUpdateStep;
    impl->selectedColor.b += impl->colorUpdateStep;

    if (impl->selectedColor.g == 0 or impl->selectedColor.g == 255)
    {
        impl->colorUpdateStep *= -1;
    }

    impl->text.setColor(impl->selectedColor);

    display(context);

    impl->lastUpdateTime = context.getClockMillisecondsTime();
}

/**
 *
 */
void MenuItem::unselect(const utils::Context& context) const &
{
    impl->text.setColor(context.getColorsManager().getColorWhite());

    impl->selected = false;
}

/**
 *
 */
void MenuItem::select(const utils::Context& context) const &
{
    impl->lastUpdateTime = context.getClockMillisecondsTime();

    impl->selected = true;
}

/**
 *
 */
void MenuItem::display(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->text);
}

}
}
