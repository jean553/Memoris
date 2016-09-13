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

namespace memoris
{
namespace popups
{

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
)
{
    /* set the SFML surfaces of the dialog widget */

    background.setSize(
        sf::Vector2f(
            hSize,
            vSize
        )
    );

    top.setSize(
        sf::Vector2f(
            hSize,
            1.f
        )
    );

    bottom.setSize(
        sf::Vector2f(
            hSize,
            1.f
        )
    );

    left.setSize(
        sf::Vector2f(
            1.f,
            vSize
        )
    );

    right.setSize(
        sf::Vector2f(
            1.f,
            vSize
        )
    );

    titleBackground.setSize(
        sf::Vector2f(
            hSize,
            50.f
        )
    );

    titleSeparator.setSize(
        sf::Vector2f(
            hSize,
            1.f
        )
    );

    /* set the positions of the SFML surfaces */

    background.setPosition(
        hPosition,
        vPosition
    );

    top.setPosition(
        hPosition,
        vPosition
    );

    bottom.setPosition(
        hPosition,
        vPosition + vSize
    );

    left.setPosition(
        hPosition,
        vPosition
    );

    right.setPosition(
        hPosition + hSize,
        vPosition
    );

    titleBackground.setPosition(
        hPosition,
        vPosition
    );

    titleSeparator.setPosition(
        hPosition,
        vPosition + 50.f
    );

    /* set the colors of the SFML surfaces */

    background.setFillColor(context.getColorsManager().getColorDarkGrey());

    titleBackground.setFillColor(
        context.getColorsManager().getColorLightBlue()
    );

    titleSeparator.setFillColor(
        context.getColorsManager().getColorWhite()
    );

    /* set the dialog title */

    title.setString(text);
    title.setCharacterSize(fonts::TEXT_SIZE);
    title.setFont(context.getFontsManager().getTextFont());
    title.setColor(context.getColorsManager().getColorWhite());
    title.setPosition(
        hPosition,
        vPosition - 10.f
    );
}

/**
 *
 */
void Dialog::displayParentContent(
    utils::Context& context
) const
{
    context.getSfmlWindow().draw(background);

    context.getSfmlWindow().draw(titleBackground);
    context.getSfmlWindow().draw(titleSeparator);

    context.getSfmlWindow().draw(top);
    context.getSfmlWindow().draw(bottom);
    context.getSfmlWindow().draw(left);
    context.getSfmlWindow().draw(right);

    context.getSfmlWindow().draw(title);
}

}
}
