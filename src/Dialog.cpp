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
 * @file Dialog.cpp
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Dialog.hpp"

#include "fonts.hpp"
#include "InputTextWidget.hpp"
#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace popups
{

class Dialog::Impl
{

public:

    sf::RectangleShape background;
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape titleBackground;
    sf::RectangleShape titleSeparator;

    sf::Text title;
};

/**
 *
 */
Dialog::Dialog(
    utils::Context& context,
    const float& hSize,
    const float& vSize,
    const float& hPosition,
    const float& vPosition,
    const std::string& text
) : impl(std::make_unique<Impl>())
{
    impl->background.setSize(
        sf::Vector2f(
            hSize,
            vSize
        )
    );

    impl->top.setSize(
        sf::Vector2f(
            hSize,
            1.f
        )
    );

    impl->bottom.setSize(
        sf::Vector2f(
            hSize,
            1.f
        )
    );

    impl->left.setSize(
        sf::Vector2f(
            1.f,
            vSize
        )
    );

    impl->right.setSize(
        sf::Vector2f(
            1.f,
            vSize
        )
    );

    impl->titleBackground.setSize(
        sf::Vector2f(
            hSize,
            50.f
        )
    );

    impl->titleSeparator.setSize(
        sf::Vector2f(
            hSize,
            1.f
        )
    );

    /* set the positions of the SFML surfaces */

    impl->background.setPosition(
        hPosition,
        vPosition
    );

    impl->top.setPosition(
        hPosition,
        vPosition
    );

    impl->bottom.setPosition(
        hPosition,
        vPosition + vSize
    );

    impl->left.setPosition(
        hPosition,
        vPosition
    );

    impl->right.setPosition(
        hPosition + hSize,
        vPosition
    );

    impl->titleBackground.setPosition(
        hPosition,
        vPosition
    );

    impl->titleSeparator.setPosition(
        hPosition,
        vPosition + 50.f
    );

    impl->background.setFillColor(
        context.getColorsManager().getColorDarkGrey()
    );

    impl->titleBackground.setFillColor(
        context.getColorsManager().getColorLightBlue()
    );

    impl->titleSeparator.setFillColor(
        context.getColorsManager().getColorWhite()
    );

    impl->title.setString(text);
    impl->title.setCharacterSize(fonts::TEXT_SIZE);
    impl->title.setFont(context.getFontsManager().getTextFont());
    impl->title.setColor(context.getColorsManager().getColorWhite());
    impl->title.setPosition(
        hPosition,
        vPosition - 10.f
    );
}

/**
 *
 */
Dialog::~Dialog() noexcept = default;

/**
 *
 */
void Dialog::displayParentContent(
    utils::Context& context
) const &
{
    context.getSfmlWindow().draw(impl->background);

    context.getSfmlWindow().draw(impl->titleBackground);
    context.getSfmlWindow().draw(impl->titleSeparator);

    context.getSfmlWindow().draw(impl->top);
    context.getSfmlWindow().draw(impl->bottom);
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->right);

    context.getSfmlWindow().draw(impl->title);
}

}
}
