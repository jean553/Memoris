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
 * @file Button.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Button.hpp"

#include "ColorsManager.hpp"

namespace memoris
{
namespace widgets
{

/**
 *
 */
class Button::Impl
{

public:

    Impl(
        const utils::Context& context,
        const float& horizontalPosition,
        const float& verticalPosition
    ) :
        context(context),
        horizontalPosition(horizontalPosition),
        verticalPosition(verticalPosition)
    {
    }

    const utils::Context& context;

    sf::RectangleShape back;
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape bottom;
    sf::RectangleShape top;

    sf::Sprite icon;

    float horizontalPosition;
    float verticalPosition;

    bool mouseHover {false};
};

/**
 *
 */
Button::Button(
    const utils::Context& context,
    const float& hPosition,
    const float& vPosition,
    const sf::Texture& texture
) :
impl(
    std::make_unique<Impl>(
        context,
        hPosition,
        vPosition
    )
)
{
    auto& back = impl->back;
    back.setSize(
        sf::Vector2f(
            BUTTON_DIMENSION,
            BUTTON_DIMENSION
        )
    );
    back.setPosition(
        hPosition,
        vPosition
    );

    constexpr float BUTTON_BORDER_WIDTH {1.f};

    auto& left = impl->left;
    left.setPosition(
        hPosition,
        vPosition
    );
    left.setSize(
        sf::Vector2f(
            BUTTON_BORDER_WIDTH,
            BUTTON_DIMENSION
        )
    );

    auto& top = impl->top;
    top.setPosition(
        hPosition,
        vPosition
    );
    top.setSize(
        sf::Vector2f(
            BUTTON_DIMENSION,
            BUTTON_BORDER_WIDTH
        )
    );

    auto& right = impl->right;
    right.setPosition(
        hPosition + BUTTON_DIMENSION - BUTTON_BORDER_WIDTH,
        vPosition
    );
    right.setSize(
        sf::Vector2f(
            BUTTON_BORDER_WIDTH,
            BUTTON_DIMENSION
        )
    );

    auto& bottom = impl->bottom;
    bottom.setPosition(
        hPosition,
        vPosition + BUTTON_DIMENSION - BUTTON_BORDER_WIDTH
    );
    bottom.setSize(
        sf::Vector2f(
            BUTTON_DIMENSION,
            BUTTON_BORDER_WIDTH
        )
    );

    auto& icon = impl->icon;
    icon.setTexture(texture);

    constexpr float ICON_POSITION_OFFSET {3.f};
    icon.setPosition(
        hPosition + ICON_POSITION_OFFSET,
        vPosition + ICON_POSITION_OFFSET
    );

    const auto& colorsManager = context.getColorsManager();
    back.setFillColor(colorsManager.getColorDarkGrey());

    setBordersColor(colorsManager.getColorDarkGrey());
}

Button::~Button() = default;

/**
 *
 */
void Button::display()
{
    const auto& context = impl->context;
    auto& window = context.getSfmlWindow();

    window.draw(impl->back);
    window.draw(impl->icon);

    sf::Vector2<int> cursorPosition = sf::Mouse::getPosition();

    if (
        cursorPosition.x > impl->horizontalPosition &&
        cursorPosition.x < impl->horizontalPosition + BUTTON_DIMENSION &&
        cursorPosition.y > impl->verticalPosition &&
        cursorPosition.y < impl->verticalPosition + BUTTON_DIMENSION &&
        !impl->mouseHover
    )
    {
        impl->mouseHover = true;

        setBordersColor(context.getColorsManager().getColorRed());
    }
    else if (
        (
            cursorPosition.x < impl->horizontalPosition ||
            cursorPosition.x > impl->horizontalPosition + BUTTON_DIMENSION ||
            cursorPosition.y < impl->verticalPosition ||
            cursorPosition.y > impl->verticalPosition + BUTTON_DIMENSION
        ) &&
        impl->mouseHover
    )
    {
        impl->mouseHover = false;

        setBordersColor(context.getColorsManager().getColorWhite());
    }

    /* draw the button borders */
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->top);
    context.getSfmlWindow().draw(impl->right);
    context.getSfmlWindow().draw(impl->bottom);
}

/**
 *
 */
void Button::setBordersColor(const sf::Color& color)
{
    impl->left.setFillColor(color);
    impl->right.setFillColor(color);
    impl->top.setFillColor(color);
    impl->bottom.setFillColor(color);
}

/**
 *
 */
bool Button::isMouseHover() const
{
    return impl->mouseHover;
}

}
}
