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
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace memoris
{
namespace widgets
{

constexpr float BUTTON_DIMENSION {70.f};

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

    setBordersColor(colorsManager.getColorWhite());
}

/**
 *
 */
Button::~Button() = default;

/**
 *
 */
void Button::display(const sf::Vector2f& cursorPosition) &
{
    const auto& context = impl->context;
    auto& window = context.getSfmlWindow();

    window.draw(impl->back);
    window.draw(impl->icon);

    const auto& cursorHorizontalPosition = cursorPosition.x;
    const auto& cursorVerticalPosition = cursorPosition.y;
    const auto& horizontalPosition = impl->horizontalPosition;
    const auto& verticalPosition = impl->verticalPosition;

    const auto isCursorHoverButton = (
        cursorHorizontalPosition > horizontalPosition and
        cursorHorizontalPosition < horizontalPosition + BUTTON_DIMENSION and
        cursorVerticalPosition > verticalPosition and
        cursorVerticalPosition < verticalPosition + BUTTON_DIMENSION
    );

    const auto& colorsManager = context.getColorsManager();
    auto& isMouseHover = impl->mouseHover;

    /* we use a second boolean impl->isMouseHover in order to prevent
       identical color updates if the mouse is still over the button */

    if (isCursorHoverButton and not isMouseHover)
    {
        isMouseHover = true;

        setBordersColor(colorsManager.getColorRed());
    }
    else if (not isCursorHoverButton and isMouseHover)
    {
        isMouseHover = false;

        setBordersColor(colorsManager.getColorWhite());
    }

    window.draw(impl->left);
    window.draw(impl->top);
    window.draw(impl->right);
    window.draw(impl->bottom);
}

/**
 *
 */
const bool Button::isMouseHover() const & noexcept
{
    return impl->mouseHover;
}

/**
 *
 */
void Button::setBordersColor(const sf::Color& color) &
{
    impl->left.setFillColor(color);
    impl->right.setFillColor(color);
    impl->top.setFillColor(color);
    impl->bottom.setFillColor(color);
}

}
}
