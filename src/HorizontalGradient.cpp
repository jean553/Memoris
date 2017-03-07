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
 * @file HorizontalGradient.cpp
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "HorizontalGradient.hpp"

#include "Context.hpp"
#include "window.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace others
{

class HorizontalGradient::Impl
{

public:

    Impl(const utils::Context& context)
    {
        background.setSize(
            sf::Vector2f(
                window::WIDTH,
                BACKGROUND_HEIGHT
            )
        );

        background.setPosition(
            0.f,
            BACKGROUND_VERTICAL_POSITION
        );

        background.setFillColor(
            context.getColorsManager().getColorBlack()
        );
    }

    sf::RectangleShape background;

    /* we use pointers in order to accelerate the execution (no object copy); 
       we could have used move sementics, but SFML does not provides move 
       constructors for rectangle shapes */
    std::vector<std::unique_ptr<sf::RectangleShape>> sidesLines;
};

/**
 *
 */
HorizontalGradient::HorizontalGradient(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    initializeGradientRectangles(context);
}

/**
 *
 */
HorizontalGradient::~HorizontalGradient() noexcept = default;

/**
 *
 */
void HorizontalGradient::render(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->background);

    // auto -> std::unique_ptr<sf::RectangleShape>&
    for (auto& rectangle : impl->sidesLines)
    {
        context.getSfmlWindow().draw(*rectangle);
    }
}

/**
 *
 */
void HorizontalGradient::initializeGradientRectangles(
    const utils::Context& context
) const &
{
    float verticalPosition = BACKGROUND_VERTICAL_POSITION;
    sf::Color effectColor = context.getColorsManager().getColorBlackCopy();

    for (
        unsigned short index = 0;
        index < SURFACES_AMOUNT;
        index++
    )
    {
        // auto -> std::unique_ptr<sf::RectangleShape>
        auto rectangle = std::make_unique<sf::RectangleShape>();

        rectangle->setPosition(
            0.f,
            verticalPosition
        );

        rectangle->setSize(
            sf::Vector2f(
                window::WIDTH,
                1.f
            )
        );

        rectangle->setFillColor(effectColor);

        if(index < SIDE_SURFACES_AMOUNT)
        {
            verticalPosition--;
        }
        else
        {
            verticalPosition++;
        }

        if (index == SIDE_SURFACES_AMOUNT)
        {
            verticalPosition = 
                BACKGROUND_VERTICAL_POSITION + BACKGROUND_HEIGHT;
            effectColor.a = DEFAULT_EFFECT_COLOR_ALPHA;
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
