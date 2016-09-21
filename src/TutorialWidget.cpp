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
        background.setSize(
            sf::Vector2f(
                WIDTH,
                HEIGHT
            )
        );

        background.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );

        background.setFillColor(
            context.getColorsManager().getColorLightBlue()
        );
    }

    sf::RectangleShape background;
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
    context.getSfmlWindow().draw(impl->background);
}

}
}
