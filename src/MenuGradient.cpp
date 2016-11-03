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
 * @file MenuGradient.cpp
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MenuGradient.hpp"

#include "Context.hpp"
#include "window.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace others
{

class MenuGradient::Impl
{

public:

    Impl(utils::Context& context)
    {
        menuBackground.setSize(
            sf::Vector2f(
                620.f,
                window::HEIGHT
            )
        );

        menuBackground.setPosition(480.f, 0);
        menuBackground.setFillColor(
            context.getColorsManager().getColorBlack()
        );
    }

    sf::RectangleShape menuBackground;

    std::vector<std::unique_ptr<sf::RectangleShape>> sidesLines;
};

/**
 *
 */
MenuGradient::MenuGradient(utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    /** the creation of the rectangles can be done directly inside the
     * constructor of the class; in fact, there are many local variables
     * to use to create these surfaces; in order to improve the code
     * organization and clarity, we create these surfaces into a dedicated
     * function. */
    initializeGradientRectangles(context);
}

/**
 *
 */
MenuGradient::~MenuGradient() noexcept = default;

/**
 *
 */
void MenuGradient::display(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->menuBackground);

    // auto -> std::unique_ptr<sf::RectangleShape>&
    for (auto& rectangle : impl->sidesLines)
    {
        context.getSfmlWindow().draw(*rectangle);
    }
}

/**
 *
 */
void MenuGradient::initializeGradientRectangles(utils::Context& context) &
{
    float horizontalPosition = LEFT_SIDE_HORIZONTAL_POSITION;

    /* we make a copy of the black color in order to apply a different alpha
       composant during each loop iteration */
    sf::Color effectColor = context.getColorsManager().getColorBlackCopy();

    for (unsigned short index = SURFACES_AMOUNT; index > 0; index--)
    {
        // auto -> std::unique_ptr<sf::RectangleShape>
        auto rectangle = std::make_unique<sf::RectangleShape>();

        rectangle->setPosition(horizontalPosition, 0);

        rectangle->setSize(
            sf::Vector2f(
                1,
                window::HEIGHT
            )
        );

        rectangle->setFillColor(effectColor);

        if(index >= SIDE_SURFACES_AMOUNT)
        {
            horizontalPosition--;
        }
        else
        {
            horizontalPosition++;
        }

        if (index == SIDE_SURFACES_AMOUNT)
        {
            horizontalPosition = RIGHT_SIDE_HORIZONTAL_POSITION;
            effectColor.a = 255;
        }

        if (index % 2 == 0)
        {
            effectColor.a--;
        }

        impl->sidesLines.push_back(std::move(rectangle));
    }
}

}
}
