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
Button::Button(
    utils::Context& context,
    const float& hPosition,
    const float& vPosition,
    const sf::Texture& texture
) :
/* integers are saved, but float are applied to the SFML setPosition()
   functions, as required; check header to know why we save integers */
    horizontalPosition(static_cast<int>(hPosition)),
    verticalPosition(static_cast<int>(vPosition))
{
    back.setSize(
        sf::Vector2f(
            BUTTON_DIMENSION,
            BUTTON_DIMENSION
        )
    );

    back.setFillColor(
        context.getColorsManager().getColorDarkGrey()
    );

    back.setPosition(
        hPosition,
        vPosition
    );

    left.setPosition(
        hPosition,
        vPosition
    );
    top.setPosition(
        hPosition,
        vPosition
    );
    right.setPosition(
        hPosition + BUTTON_DIMENSION - 1.f,
        vPosition
    );
    bottom.setPosition(
        hPosition,
        vPosition + BUTTON_DIMENSION - 1.f
    );

    left.setSize(
        sf::Vector2f(
            1.f,
            BUTTON_DIMENSION
        )
    );
    top.setSize(
        sf::Vector2f(
            BUTTON_DIMENSION,
            1.f
        )
    );
    right.setSize(
        sf::Vector2f(
            1.f,
            BUTTON_DIMENSION
        )
    );
    bottom.setSize(
        sf::Vector2f(
            BUTTON_DIMENSION,
            1.f
        )
    );

    icon.setTexture(texture);
    icon.setPosition(
        hPosition + ICON_POSITION_OFFSET,
        vPosition + ICON_POSITION_OFFSET
    );

    setBordersColor(context.getColorsManager().getColorWhite());
}

/**
 *
 */
void Button::display(utils::Context& context)
{
    /* draw the button background */
    context.getSfmlWindow().draw(back);

    /* draw the button icon */
    context.getSfmlWindow().draw(icon);

    /* get the current cursor position */
    sf::Vector2<int> cursorPosition = sf::Mouse::getPosition();

    /* change the color of the border if the mouse is hover the button */
    if (
        cursorPosition.x > horizontalPosition &&
        cursorPosition.x < horizontalPosition + BUTTON_DIMENSION &&
        cursorPosition.y > verticalPosition &&
        cursorPosition.y < verticalPosition + BUTTON_DIMENSION &&
        !mouseHover
    )
    {
        mouseHover = true;

        setBordersColor(context.getColorsManager().getColorRed());
    }
    else if (
        (
            cursorPosition.x < horizontalPosition ||
            cursorPosition.x > horizontalPosition + BUTTON_DIMENSION ||
            cursorPosition.y < verticalPosition ||
            cursorPosition.y > verticalPosition + BUTTON_DIMENSION
        ) &&
        mouseHover
    )
    {
        mouseHover = false;

        setBordersColor(context.getColorsManager().getColorWhite());
    }

    /* draw the button borders */
    context.getSfmlWindow().draw(left);
    context.getSfmlWindow().draw(top);
    context.getSfmlWindow().draw(right);
    context.getSfmlWindow().draw(bottom);
}

/**
 *
 */
void Button::setBordersColor(const sf::Color& color)
{
    left.setFillColor(color);
    right.setFillColor(color);
    top.setFillColor(color);
    bottom.setFillColor(color);
}

/**
 *
 */
bool Button::isMouseHover() const
{
    return mouseHover;
}

}
}
