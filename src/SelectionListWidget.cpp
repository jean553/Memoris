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
 * @file SelectionListWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SelectionListWidget.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

class SelectionListWidget::Impl
{

public:

    Impl(utils::Context& context)
    {
        top.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );
        left.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );
        right.setPosition(
            HORIZONTAL_POSITION + WIDTH,
            VERTICAL_POSITION
        );
        bottom.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION + HEIGHT
        );

        top.setSize(
            sf::Vector2f(
                WIDTH,
                1.f
            )
        );
        left.setSize(
            sf::Vector2f(
                1.f,
                HEIGHT
            )
        );
        right.setSize(
            sf::Vector2f(
                1.f,
                HEIGHT
            )
        );
        bottom.setSize(
            sf::Vector2f(
                WIDTH,
                1.f
            )
        );

        top.setFillColor(context.getColorsManager().getColorLightBlue());
        left.setFillColor(context.getColorsManager().getColorLightBlue());
        right.setFillColor(context.getColorsManager().getColorLightBlue());
        bottom.setFillColor(context.getColorsManager().getColorLightBlue());
    }

    static constexpr float HORIZONTAL_POSITION {500.f};
    static constexpr float VERTICAL_POSITION {200.f};
    static constexpr float WIDTH {600.f};
    static constexpr float HEIGHT {610.f};

    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    std::vector<sf::Text> texts;
};

/**
 *
 */
SelectionListWidget::SelectionListWidget(utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
SelectionListWidget::~SelectionListWidget() noexcept = default;

/**
 *
 */
void SelectionListWidget::display(utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->top);
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->right);
    context.getSfmlWindow().draw(impl->bottom);

    std::for_each(
        impl->texts.begin(),
        impl->texts.end(),
        [&context](const sf::Text& text)
        {
            context.getSfmlWindow().draw(text);
        }
    );
}

/**
 *
 */
void SelectionListWidget::setList(
    utils::Context& context,
    const std::vector<std::string>& list
) &
    noexcept
{
    /* we capture 'this' because a lambda function does not capture anything 
       and we want access the 'impl' attribute */

    float verticalPosition {200.f};

    std::for_each(
        list.begin(),
        list.end(),
        [this, &context, &verticalPosition](const std::string& item)
        {
            sf::Text text(
                item,
                context.getFontsManager().getTextFont(),
                fonts::TEXT_SIZE
            );

            text.setColor(context.getColorsManager().getColorWhite());
            text.setPosition(
                520.f,
                verticalPosition
            );

            impl->texts.push_back(text);

            verticalPosition += 50.f;
        }
    );
}

}
}
