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

    Impl(const utils::Context& context) :
        context(context)
    {
        constexpr float BACKGROUND_HEIGHT {300.f};
        background.setSize(
            sf::Vector2f(
                window::WIDTH,
                BACKGROUND_HEIGHT
            )
        );

        constexpr float BACKGROUND_HORIZONTAL_POSITION {0.f};
        constexpr float BACKGROUND_VERTICAL_POSITION {250.f};
        background.setPosition(
            BACKGROUND_HORIZONTAL_POSITION,
            BACKGROUND_VERTICAL_POSITION
        );

        const auto& colorsManager = context.getColorsManager();

        background.setFillColor(colorsManager.getColorBlack());

        float verticalPosition = BACKGROUND_VERTICAL_POSITION;
        auto effectColor = colorsManager.getColorBlackCopy();

        float verticalPositionDirection {-1.f};

        constexpr unsigned short LINES_AMOUNT {1020};
        for (
            unsigned short index = 0;
            index < LINES_AMOUNT;
            index += 1
        )
        {
            auto rectangle = std::make_unique<sf::RectangleShape>();

            rectangle->setPosition(
                BACKGROUND_HORIZONTAL_POSITION,
                verticalPosition
            );

            constexpr float GRADIENT_LINE_HEIGHT {1.f};
            rectangle->setSize(
                sf::Vector2f(
                    window::WIDTH,
                    GRADIENT_LINE_HEIGHT
                )
            );

            rectangle->setFillColor(effectColor);

            lines.push_back(std::move(rectangle));

            verticalPosition += verticalPositionDirection;

            constexpr unsigned short LINES_PER_SIDE {510};
            if (index == LINES_PER_SIDE)
            {
                verticalPosition =
                    BACKGROUND_VERTICAL_POSITION + BACKGROUND_HEIGHT;

                constexpr sf::Uint8 DEFAULT_EFFECT_COLOR_ALPHA {255};
                effectColor.a = DEFAULT_EFFECT_COLOR_ALPHA;

                verticalPositionDirection = 1;
            }

            if (index % 2 == 0)
            {
                effectColor.a -= 1;
            }
        }
    }

    const utils::Context& context;

    sf::RectangleShape background;

    /* we use pointers in order to accelerate the execution (no object copy); 
       we could have used move sementics, but SFML does not provides move 
       constructors for rectangle shapes */
    std::vector<std::unique_ptr<sf::RectangleShape>> lines;
};

/**
 *
 */
HorizontalGradient::HorizontalGradient(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
HorizontalGradient::~HorizontalGradient() = default;

/**
 *
 */
void HorizontalGradient::render() const &
{
    auto& window = impl->context.getSfmlWindow();

    window.draw(impl->background);

    for (const auto& line : impl->lines)
    {
        window.draw(*line);
    }
}

}
}
