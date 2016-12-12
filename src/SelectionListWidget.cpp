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
#include "TexturesManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

namespace memoris
{
namespace widgets
{

class SelectionListWidget::Impl
{

public:

    Impl(const utils::Context& context)
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

        /* we do not set the position of the selector here; it is directly
           calculated according to the cursor position */
        selector.setSize(
            sf::Vector2f(
                WIDTH - 1.f,
                ITEMS_SEPARATION
            )
        );
        selector.setFillColor(
            context.getColorsManager().getColorPartialDarkGrey()
        );

        arrowUp.setTexture(
            context.getTexturesManager().getScrollArrowUpTexture()
        );

        arrowDown.setTexture(
            context.getTexturesManager().getScrollArrowDownTexture()
        );

        float horizontalPositionBase = HORIZONTAL_POSITION + WIDTH / 2;

        leftArrowHorizontalPosition = horizontalPositionBase - 2 * ARROW_SPACE;
        rightArrowHorizontalPosition = horizontalPositionBase + ARROW_SPACE;

        verticalPositionBase = VERTICAL_POSITION + HEIGHT;

        arrowUp.setPosition(
            horizontalPositionBase - 2 * ARROW_SPACE,
            verticalPositionBase
        );

        arrowDown.setPosition(
            horizontalPositionBase + ARROW_SPACE,
            verticalPositionBase
        );
    }

    static constexpr float ARROW_SPACE {64.f};

    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape selector;

    sf::Sprite arrowUp;
    sf::Sprite arrowDown;

    std::vector<sf::Text> texts;

    unsigned short selectorIndex {0};

    bool mouseHoverLeftArrow {false};
    bool mouseHoverRightArrow {false};

    float leftArrowHorizontalPosition {0.f};
    float rightArrowHorizontalPosition {0.f};
    float verticalPositionBase {0.f};

    sf::Color selectedArrowColor {
        255,
        255,
        255,
        128
    };

    sf::Color unselectedArrowColor {
        255,
        255,
        255,
        255
    };
};

/**
 *
 */
SelectionListWidget::SelectionListWidget(const utils::Context& context) :
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
void SelectionListWidget::display(const utils::Context& context) &
{
    context.getSfmlWindow().draw(impl->top);
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->right);
    context.getSfmlWindow().draw(impl->bottom);
    context.getSfmlWindow().draw(impl->arrowUp);
    context.getSfmlWindow().draw(impl->arrowDown);

    displaySelector(context);

    for (
        std::vector<sf::Text>::const_iterator iterator = impl->texts.begin();
        iterator < impl->texts.end();
        ++iterator
    )
    {
        if (iterator - impl->texts.begin() == VISIBLE_ITEMS)
        {
            break;
        }

        context.getSfmlWindow().draw(*iterator);
    }

    selectArrowWhenMouseHover(
        context,
        impl->leftArrowHorizontalPosition,
        impl->arrowUp,
        impl->mouseHoverLeftArrow
    );

    selectArrowWhenMouseHover(
        context,
        impl->rightArrowHorizontalPosition,
        impl->arrowDown,
        impl->mouseHoverRightArrow
    );
}

/**
 *
 */
void SelectionListWidget::setList(
    const utils::Context& context,
    const std::vector<std::string>& list
) &
noexcept
{
    float verticalPosition {VERTICAL_POSITION};

    /* we capture 'this' because a lambda function does not capture anything
       and we want access the 'impl' attribute */

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
            HORIZONTAL_POSITION,
            verticalPosition
        );

        impl->texts.push_back(text);

        verticalPosition += ITEMS_SEPARATION;
    }
    );
}

/**
 *
 */
void SelectionListWidget::displaySelector(const utils::Context& context) &
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition();

    /* explicit cast because sf::Mouse::getPosition() returns integers */
    float mouseHorizontalPosition = static_cast<float>(mousePosition.x);
    float mouseVerticalPosition = static_cast<float>(mousePosition.y);

    if (
        mouseHorizontalPosition < HORIZONTAL_POSITION ||
        mouseHorizontalPosition > HORIZONTAL_POSITION + WIDTH ||
        mouseVerticalPosition < VERTICAL_POSITION ||
        mouseVerticalPosition > VERTICAL_POSITION + HEIGHT - 1.f
    )
    {
        return;
    }

    /* explicit cast to only work with integers in the division; it prevents
       to get decimal results */
    impl->selectorIndex =
        (mousePosition.y - static_cast<int>(VERTICAL_POSITION)) /
        static_cast<int>(ITEMS_SEPARATION);

    /* do not display the selection surface if there is no item under the
       cursor; implicit cast from size_t and int */
    if (impl->selectorIndex >= impl->texts.size())
    {
        return;
    }

    /* set the selector position */
    impl->selector.setPosition(
        HORIZONTAL_POSITION + 1.f,
        VERTICAL_POSITION + 1.f +
        static_cast<float>(impl->selectorIndex) * ITEMS_SEPARATION
    );

    context.getSfmlWindow().draw(impl->selector);
}

/**
 *
 */
const std::string SelectionListWidget::getCurrentItem() const & noexcept
{
    if (impl->selectorIndex >= impl->texts.size())
    {
        return "";
    }

    return impl->texts[impl->selectorIndex].getString();
}

/**
 *
 */
void SelectionListWidget::selectArrowWhenMouseHover(
    const utils::Context& context,
    const unsigned short& horizontalPosition,
    sf::Sprite& arrowSprite,
    bool& selected
) const &
{
    sf::Vector2<int> mousePosition = sf::Mouse::getPosition();

    if (
        mousePosition.x > horizontalPosition and
        mousePosition.x < horizontalPosition + ARROW_DIMENSION and
        mousePosition.y > impl->verticalPositionBase and
        mousePosition.y < impl->verticalPositionBase + ARROW_DIMENSION and
        not selected
    )
    {
        arrowSprite.setColor(impl->selectedArrowColor);

        selected = true;
    }
    else if (
        (
            mousePosition.x < horizontalPosition or
            mousePosition.x > horizontalPosition + ARROW_DIMENSION or
            mousePosition.y < impl->verticalPositionBase or
            mousePosition.y > impl->verticalPositionBase + ARROW_DIMENSION
        ) and selected
    )
    {
        arrowSprite.setColor(impl->unselectedArrowColor);

        selected = false;
    }
}

}
}
