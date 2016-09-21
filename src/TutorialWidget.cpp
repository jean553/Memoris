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
 * @file TutorialWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TutorialWidget.hpp"

#include "Context.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{
namespace widgets
{

class TutorialWidget::Impl
{

public:

    Impl(utils::Context& context)
    {
        back.setSize(
            sf::Vector2f(
                WIDTH,
                HEIGHT
            )
        );
        top.setSize(
            sf::Vector2f(
                WIDTH,
                BORDER_WIDTH
            )
        );
        bottom.setSize(
            sf::Vector2f(
                WIDTH,
                BORDER_WIDTH
            )
        );
        left.setSize(
            sf::Vector2f(
                BORDER_WIDTH,
                HEIGHT
            )
        );
        right.setSize(
            sf::Vector2f(
                BORDER_WIDTH,
                HEIGHT
            )
        );

        back.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );
        top.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );
        left.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );
        right.setPosition(
            HORIZONTAL_POSITION + WIDTH - 1.f,
            VERTICAL_POSITION
        );
        bottom.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION + HEIGHT
        );

        back.setFillColor(context.getColorsManager().getColorLightBlue());
        top.setFillColor(context.getColorsManager().getColorWhite());
        left.setFillColor(context.getColorsManager().getColorWhite());
        right.setFillColor(context.getColorsManager().getColorWhite());
        bottom.setFillColor(context.getColorsManager().getColorWhite());
    }

    sf::RectangleShape back;
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;
};

/**
 *
 */
TutorialWidget::TutorialWidget(utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
TutorialWidget::~TutorialWidget() noexcept = default;

/**
 *
 */
void TutorialWidget::display(utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->back);
    context.getSfmlWindow().draw(impl->top);
    context.getSfmlWindow().draw(impl->bottom);
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->right);
}

}
}
