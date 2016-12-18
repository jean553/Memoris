/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

    Impl(
        const utils::Context& context,
        const float& originHorizontalPosition
    ) :
        horizontalPosition(originHorizontalPosition),
        window(context.getSfmlWindow())
    {
        top.setPosition(
            horizontalPosition,
            VERTICAL_POSITION
        );
        left.setPosition(
            horizontalPosition,
            VERTICAL_POSITION
        );
        right.setPosition(
            horizontalPosition + WIDTH,
            VERTICAL_POSITION
        );
        bottom.setPosition(
            horizontalPosition,
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

        float horizontalPositionBase = horizontalPosition + WIDTH / 2;

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

    /* signed because equals to -1 when nothing is selected */
    short selectorIndex {0};

    /* first index to display in the list; changes when the arrows are
       clicked */
    unsigned short offset {0};

    bool mouseHoverLeftArrow {false};
    bool mouseHoverRightArrow {false};

    float leftArrowHorizontalPosition {0.f};
    float rightArrowHorizontalPosition {0.f};
    float verticalPositionBase {0.f};
    float horizontalPosition;

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

    sf::RenderWindow& window;
};

/**
 *
 */
SelectionListWidget::SelectionListWidget(
    const utils::Context& context,
    const float& horizontalPosition
) :
    impl(
        std::make_unique<Impl>(
            context,
            horizontalPosition
        )
    )
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
    impl->window.draw(impl->top);
    impl->window.draw(impl->left);
    impl->window.draw(impl->right);
    impl->window.draw(impl->bottom);
    impl->window.draw(impl->arrowUp);
    impl->window.draw(impl->arrowDown);

    displaySelector(context);

    for (
        std::vector<sf::Text>::const_iterator iterator = impl->texts.begin();
        iterator < impl->texts.end();
        ++iterator
    )
    {
        const float& itemVerticalPosition = iterator->getPosition().y;

        if (
            itemVerticalPosition < VERTICAL_POSITION or
            itemVerticalPosition >= VERTICAL_POSITION + HEIGHT
        )
        {
            continue;
        }

        impl->window.draw(*iterator);
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
            impl->horizontalPosition,
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
        mouseHorizontalPosition < impl->horizontalPosition or
        mouseHorizontalPosition > impl->horizontalPosition + WIDTH or
        mouseVerticalPosition < VERTICAL_POSITION or
        mouseVerticalPosition > VERTICAL_POSITION + HEIGHT - 1.f
    )
    {
        impl->selectorIndex = NO_SELECTION_INDEX;

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
        impl->horizontalPosition + 1.f,
        VERTICAL_POSITION + 1.f +
        static_cast<float>(impl->selectorIndex) * ITEMS_SEPARATION
    );

    impl->window.draw(impl->selector);
}

/**
 *
 */
const std::string SelectionListWidget::getCurrentItem() const & noexcept
{
    if (
        impl->selectorIndex >= impl->texts.size() or
        impl->selectorIndex == NO_SELECTION_INDEX
    )
    {
        return "";
    }

    return impl->texts[impl->selectorIndex + impl->offset].getString();
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

/**
 *
 */
void SelectionListWidget::updateList() const &
{
    constexpr float DISPLAY_NEXT_ITEM_STEP {-1.f};
    constexpr float DISPLAY_PREVIOUS_ITEM_STEP {1.f};

    if (
        impl->mouseHoverLeftArrow and
        impl->offset != 0
    )
    {
        impl->offset--;

        updateAllItemsPosition(DISPLAY_PREVIOUS_ITEM_STEP);
    }
    else if (
        impl->mouseHoverRightArrow and
        impl->offset + VISIBLE_ITEMS != impl->texts.size()
    )
    {
        impl->offset++;

        updateAllItemsPosition(DISPLAY_NEXT_ITEM_STEP);
    }
}

/**
 *
 */
void SelectionListWidget::updateAllItemsPosition(const float& movement) const &
{
    for (sf::Text& text : impl->texts)
    {
        text.setPosition(
            impl->horizontalPosition,
            text.getPosition().y + ITEMS_SEPARATION * movement
        );
    }
}

/**
 *
 */
void SelectionListWidget::deleteSelectedItem() const &
{
    // std::vector<sf::Text>&
    auto& texts = impl->texts;

    /* we can use the operator + here between
       integers and iterator because it is a random access iterator; we
       explicitly declare the type to prevent oversights */
    const std::vector<sf::Text>::iterator offsetIndex =
        texts.begin() + impl->selectorIndex + impl->offset;

    /* erase guarantees no exception */
    texts.erase(offsetIndex);

    // const float&
    const auto& horizontalPosition = impl->horizontalPosition;

    /* not a const_iterator because setPosition
       modifies the iterated objects */
    for (
        auto it = offsetIndex; // std::vector<sf::Text>::iterator
        it != texts.end();
        ++it
    )
    {
        it->setPosition(
            horizontalPosition,
            it->getPosition().y - ITEMS_SEPARATION
        );
    }
}

}
}
