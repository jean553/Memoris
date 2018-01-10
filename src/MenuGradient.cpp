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

    Impl(const utils::Context& context) :
        context(context)
    {
        constexpr float BACKGROUND_WIDTH {620.f};
        menuBackground.setSize(
            sf::Vector2f(
                BACKGROUND_WIDTH,
                window::HEIGHT
            )
        );

        constexpr float BACKGROUND_HORIZONTAL_POSITION {480.f};
        menuBackground.setPosition(
            BACKGROUND_HORIZONTAL_POSITION,
            0.f
        );
        menuBackground.setFillColor(
            context.getColorsManager().getColorBlack()
        );
    }

    sf::RectangleShape menuBackground;

    /* we use pointers in order to accelerate the execution (no object copy);
       we could have used move sementics, but SFML does not provides move
       constructors for rectangle shapes */
    std::vector<std::unique_ptr<sf::RectangleShape>> sidesLines;

    const utils::Context& context;
};

/**
 *
 */
MenuGradient::MenuGradient(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    /* this is a complex initialization,
       so it is handled by a dedicated method */
    initializeGradientRectangles();
}

/**
 *
 */
MenuGradient::~MenuGradient() = default;

/**
 *
 */
void MenuGradient::display() const &
{
    auto& window = impl->context.getSfmlWindow();
    window.draw(impl->menuBackground);

    for (const auto& rectangle : impl->sidesLines)
    {
        window.draw(*rectangle);
    }
}

/**
 *
 */
void MenuGradient::initializeGradientRectangles() const &
{
    constexpr float LEFT_SIDE_HORIZONTAL_POSITION {479.f};
    float horizontalPosition {LEFT_SIDE_HORIZONTAL_POSITION};

    sf::Color effectColor
        {impl->context.getColorsManager().getColorBlackCopy()};

    constexpr unsigned short SURFACES_AMOUNT {1020};
    for (
        unsigned short index {SURFACES_AMOUNT};
        index > 0;
        index -= 1
    )
    {
        auto rectangle = std::make_unique<sf::RectangleShape>();

        constexpr float RECTANGLES_COMMON_VERTICAL_POSITION {0.f};
        rectangle->setPosition(
            horizontalPosition,
            RECTANGLES_COMMON_VERTICAL_POSITION
        );

        constexpr float RECTANGLES_COMMON_WIDTH {1.f};
        rectangle->setSize(
            sf::Vector2f(
                RECTANGLES_COMMON_WIDTH,
                window::HEIGHT
            )
        );

        rectangle->setFillColor(effectColor);

        constexpr unsigned short SIDE_SURFACES_AMOUNT {510};
        if(index >= SIDE_SURFACES_AMOUNT)
        {
            horizontalPosition -= 1;
        }
        else
        {
            horizontalPosition += 1;
        }

        if (index == SIDE_SURFACES_AMOUNT)
        {
            constexpr float RIGHT_SIDE_HORIZONTAL_POSITION {1099.f};
            horizontalPosition = RIGHT_SIDE_HORIZONTAL_POSITION;

            constexpr sf::Uint8 DEFAULT_EFFECT_COLOR_ALPHA {255};
            effectColor.a = DEFAULT_EFFECT_COLOR_ALPHA;
        }

        constexpr unsigned short SURFACES_WITH_SAME_ALPHA {2};
        if (index % SURFACES_WITH_SAME_ALPHA == 0)
        {
            effectColor.a -= 1;
        }

        impl->sidesLines.push_back(std::move(rectangle));
    }
}

}
}
