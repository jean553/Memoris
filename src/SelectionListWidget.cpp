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

        constexpr float BORDERS_WIDTH {1.f};
        top.setSize(
            sf::Vector2f(
                WIDTH,
                BORDERS_WIDTH
            )
        );
        left.setSize(
            sf::Vector2f(
                BORDERS_WIDTH,
                HEIGHT
            )
        );
        right.setSize(
            sf::Vector2f(
                BORDERS_WIDTH,
                HEIGHT
            )
        );
        bottom.setSize(
            sf::Vector2f(
                WIDTH,
                BORDERS_WIDTH
            )
        );

        const auto& colorsManager = context.getColorsManager();

        const auto& lightBlue = colorsManager.getColorLightBlue();
        top.setFillColor(lightBlue);
        left.setFillColor(lightBlue);
        right.setFillColor(lightBlue);
        bottom.setFillColor(lightBlue);

        /* the selector position is directly calculated
           into the render() method according to the cursor position */

        selector.setSize(
            sf::Vector2f(
                WIDTH - BORDERS_WIDTH,
                ITEMS_SEPARATION
            )
        );
        selector.setFillColor(colorsManager.getColorPartialDarkGrey());

        const auto& texturesManager = context.getTexturesManager();
        arrowUp.setTexture(texturesManager.getScrollArrowUpTexture());
        arrowDown.setTexture(texturesManager.getScrollArrowDownTexture());

        const float horizontalPositionCenter =
            horizontalPosition + WIDTH / 2.f;

        constexpr float ARROW_WIDTH {64.f};
        constexpr float ARROWS_SEPARATION {ARROW_WIDTH * 2.f};

        leftArrowHorizontalPosition =
            horizontalPositionCenter - ARROWS_SEPARATION;
        rightArrowHorizontalPosition = horizontalPositionCenter + ARROW_WIDTH;
        verticalPositionBase = VERTICAL_POSITION + HEIGHT;

        arrowUp.setPosition(
            horizontalPositionCenter - ARROWS_SEPARATION,
            verticalPositionBase
        );

        arrowDown.setPosition(
            horizontalPositionCenter + ARROW_WIDTH,
            verticalPositionBase
        );
    }

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

    unsigned short offset {0};

    bool mouseHoverLeftArrow {false};
    bool mouseHoverRightArrow {false};

    float leftArrowHorizontalPosition {0.f};
    float rightArrowHorizontalPosition {0.f};
    float verticalPositionBase {0.f};
    float horizontalPosition;

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
SelectionListWidget::~SelectionListWidget() = default;

/**
 *
 */
void SelectionListWidget::display(
    const utils::Context& context,
    const sf::Vector2<float>& cursorPosition
) const &
{
    auto& window = impl->window;
    window.draw(impl->top);
    window.draw(impl->left);
    window.draw(impl->right);
    window.draw(impl->bottom);
    window.draw(impl->arrowUp);
    window.draw(impl->arrowDown);

    const auto& texts = impl->texts;

    if (texts.size() == 0)
    {
        return;
    }

    auto& selectorIndex = impl->selectorIndex;
    if(isMouseOverItem(cursorPosition))
    {
        const float selectorPosition =
            (cursorPosition.y - VERTICAL_POSITION) / ITEMS_SEPARATION;

        selectorIndex = static_cast<short>(selectorPosition);

        displaySelector(context);
    }
    else
    {
        selectorIndex = NO_SELECTION_INDEX;
    }

    std::for_each(
        texts.cbegin(),
        texts.cend(),
        [&window] (const auto& text)
        {
            const float& itemVerticalPosition = text.getPosition().y;

            if (
                itemVerticalPosition < VERTICAL_POSITION or
                itemVerticalPosition >= VERTICAL_POSITION + HEIGHT
            )
            {
                return;
            }

            window.draw(text);
        }
    );

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
void SelectionListWidget::displaySelector(
    const utils::Context& context
) const &
{
    auto& selector = impl->selector;

    constexpr float MARGER_BETWEEN_BORDER_AND_SELECTOR {1.f};
    selector.setPosition(
        impl->horizontalPosition + MARGER_BETWEEN_BORDER_AND_SELECTOR,
        VERTICAL_POSITION + MARGER_BETWEEN_BORDER_AND_SELECTOR +
        static_cast<float>(impl->selectorIndex) * ITEMS_SEPARATION
    );

    impl->window.draw(selector);
}

/**
 *
 */
const bool SelectionListWidget::isMouseOverItem(
    const sf::Vector2<float>& cursorPosition
) const &
{
    const auto& cursorHorizontalPosition = cursorPosition.x;
    const auto& cursorVerticalPosition = cursorPosition.y;

    const auto& rightBorderHorizontalPosition =
        impl->horizontalPosition + WIDTH;
    const auto& lastItemVerticalBottom =
        impl->texts.back().getPosition().y + ITEMS_SEPARATION;

    if (
        cursorHorizontalPosition < impl->horizontalPosition or
        cursorHorizontalPosition > rightBorderHorizontalPosition or
        cursorVerticalPosition < VERTICAL_POSITION or
        cursorVerticalPosition > lastItemVerticalBottom
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
const std::string SelectionListWidget::getCurrentItem() const &
{
    return impl->texts[impl->selectorIndex + impl->offset].getString();
}

/**
 *
 */
const bool SelectionListWidget::isAnyItemSelected() const & noexcept
{
    const auto& index = impl->selectorIndex;
    if (
        index >= impl->texts.size() or
        index == NO_SELECTION_INDEX
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
std::vector<sf::Text>& SelectionListWidget::getList() const & noexcept
{
    return impl->texts;
}

/**
 *
 */
const float& SelectionListWidget::getHorizontalPosition() const & noexcept
{
    return impl->horizontalPosition;
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

    const auto& colorsManager = context.getColorsManager();

    if (
        mousePosition.x > horizontalPosition and
        mousePosition.x < horizontalPosition + ARROW_DIMENSION and
        mousePosition.y > impl->verticalPositionBase and
        mousePosition.y < impl->verticalPositionBase + ARROW_DIMENSION and
        not selected
    )
    {
        arrowSprite.setColor(colorsManager.getColorWhiteLowAlpha());

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
        arrowSprite.setColor(colorsManager.getColorWhite());

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

/**
 *
 */
void SelectionListWidget::addItem(
    const utils::Context& context,
    const std::string& item
) const &
{
    sf::Text text(
        item,
        context.getFontsManager().getTextFont(),
        fonts::TEXT_SIZE
    );

    text.setColor(context.getColorsManager().getColorWhite());

    // std::vector<sf::Text>&
    auto& texts = impl->texts;

    text.setPosition(
        impl->horizontalPosition,
        VERTICAL_POSITION + ITEMS_SEPARATION * texts.size()
    );

    texts.push_back(text);
}

/**
 *
 */
const std::vector<sf::Text>& SelectionListWidget::getTexts() const & noexcept
{
    return impl->texts;
}

/**
 *
 */
void SelectionListWidget::deleteAllItems() const & noexcept
{
    impl->texts.clear();
}

}
}
