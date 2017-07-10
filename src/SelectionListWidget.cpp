/*
 * Memoris
 * Copyright (C) 2017 Jean LELIEVRE
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
#include "fonts_sizes.hpp"
#include "TexturesManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace widgets
{

constexpr float VERTICAL_POSITION {200.f};
constexpr float WIDTH {600.f};
constexpr float HEIGHT {600.f};
constexpr float ITEMS_SEPARATION {50.f};
constexpr float ARROWS_VERTICAL_POSITION {800.f};

class SelectionListWidget::Impl
{

public:

    Impl(
        const utils::Context& context,
        const float& originHorizontalPosition
    ) :
        context(context),
        horizontalPosition(originHorizontalPosition)
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

        arrowUp.setPosition(
            horizontalPositionCenter - ARROWS_SEPARATION,
            ARROWS_VERTICAL_POSITION
        );

        arrowDown.setPosition(
            horizontalPositionCenter + ARROW_WIDTH,
            ARROWS_VERTICAL_POSITION
        );
    }

    const utils::Context& context;

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
    short offset {0};

    bool mouseHoverLeftArrow {false};
    bool mouseHoverRightArrow {false};

    float leftArrowHorizontalPosition {0.f};
    float rightArrowHorizontalPosition {0.f};
    float horizontalPosition;
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
    const sf::Vector2<float>& cursorPosition
) const &
{
    const auto& context = impl->context;

    auto& window = context.getSfmlWindow();
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
    if(isMouseHoverItem(cursorPosition))
    {
        const float selectorPosition =
            (cursorPosition.y - VERTICAL_POSITION) / ITEMS_SEPARATION;

        selectorIndex = static_cast<short>(selectorPosition);

        displaySelector();
    }
    else
    {
        constexpr short NO_SELECTION_INDEX {-1};
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
        impl->leftArrowHorizontalPosition,
        cursorPosition,
        impl->arrowUp,
        impl->mouseHoverLeftArrow
    );

    selectArrowWhenMouseHover(
        impl->rightArrowHorizontalPosition,
        cursorPosition,
        impl->arrowDown,
        impl->mouseHoverRightArrow
    );
}

/**
 *
 */
std::string SelectionListWidget::getCurrentItem() const &
{
    return impl->texts[impl->selectorIndex + impl->offset * -1].getString();
}

/**
 *
 */
const unsigned short SelectionListWidget::getItemsAmount() const & noexcept
{
    /* everywhere this value is required,
       a comparison with unsigned variable is performed */
    return static_cast<unsigned short>(impl->texts.size());
}

/**
 *
 */
const short& SelectionListWidget::getCurrentIndex() const & noexcept
{
    return impl->selectorIndex;
}

/**
 *
 */
const bool SelectionListWidget::canScrollUp() const & noexcept
{
    constexpr unsigned short MIN_OFFSET {0};
    return impl->mouseHoverLeftArrow and impl->offset != MIN_OFFSET;
}

/**
 *
 */
const bool SelectionListWidget::canScrollDown() const & noexcept
{
    constexpr unsigned short VISIBLE_ITEMS_AMOUNT {12};

    /* prevent comparison between signed and unsigned variables */
    const auto& itemsAmount = static_cast<unsigned short>(impl->texts.size());

    return (
        impl->mouseHoverRightArrow and
        itemsAmount >= VISIBLE_ITEMS_AMOUNT and
        impl->offset * -1 + VISIBLE_ITEMS_AMOUNT != itemsAmount
    );
}

/**
 *
 */
void SelectionListWidget::updateAllItemsPosition(const ListMovement& movement)
    const &
{
    short listMovement {-1};

    if (movement == ListMovement::Up)
    {
        listMovement = 1;
    }

    impl->offset += listMovement;

    const auto positionUpdate =
        ITEMS_SEPARATION * static_cast<float>(listMovement);

    for (sf::Text& text : impl->texts)
    {
        text.setPosition(
            impl->horizontalPosition,
            text.getPosition().y + positionUpdate
        );
    }
}

/**
 *
 */
void SelectionListWidget::deleteSelectedItem() const &
{
    auto& texts = impl->texts;

    /* we can use the operator plus here between integers and iterator
       because it is a random access iterator; we explicitly declare
       the type to prevent oversights */
    const std::vector<sf::Text>::iterator offsetIndex =
        texts.begin() + impl->selectorIndex + impl->offset;

    texts.erase(offsetIndex);

    const auto& horizontalPosition = impl->horizontalPosition;

    /* not a const_iterator as setPosition() modifies the iterated objects */
    for (
        auto it = offsetIndex;
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
void SelectionListWidget::addItem(std::string&& text) const &
{
    const auto& context = impl->context;

    sf::Text surface(
        text,
        context.getFontsManager().getTextFont(),
        sizes::TEXT_SIZE
    );

    surface.setFillColor(context.getColorsManager().getColorWhite());

    auto& texts = impl->texts;

    const auto& verticalPosition = VERTICAL_POSITION +
        ITEMS_SEPARATION * static_cast<float>(texts.size());

    surface.setPosition(
        impl->horizontalPosition,
        verticalPosition
    );

    texts.push_back(surface);
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
void SelectionListWidget::displaySelector() const &
{
    auto& selector = impl->selector;

    constexpr float MARGER_BETWEEN_BORDER_AND_SELECTOR {1.f};
    selector.setPosition(
        impl->horizontalPosition + MARGER_BETWEEN_BORDER_AND_SELECTOR,
        VERTICAL_POSITION + MARGER_BETWEEN_BORDER_AND_SELECTOR +
        static_cast<float>(impl->selectorIndex) * ITEMS_SEPARATION
    );

    impl->context.getSfmlWindow().draw(selector);
}

/**
 *
 */
const bool SelectionListWidget::isMouseHoverItem(
    const sf::Vector2<float>& cursorPosition
) const &
{
    const auto& cursorHorizontalPosition = cursorPosition.x;
    const auto& cursorVerticalPosition = cursorPosition.y + 1.f;

    const auto& rightBorderHorizontalPosition =
        impl->horizontalPosition + WIDTH;
    constexpr float BOTTOM_BORDER_VERTICAL_POSITION =
        VERTICAL_POSITION + HEIGHT;

    if (
        cursorHorizontalPosition < impl->horizontalPosition or
        cursorHorizontalPosition > rightBorderHorizontalPosition or
        cursorVerticalPosition < VERTICAL_POSITION or
        cursorVerticalPosition > BOTTOM_BORDER_VERTICAL_POSITION
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
void SelectionListWidget::selectArrowWhenMouseHover(
    const unsigned short& arrowHorizontalPosition,
    const sf::Vector2<float>& cursorPosition,
    sf::Sprite& arrowSprite,
    bool& selected
) const &
{
    const auto& context = impl->context;

    const auto& colorsManager = context.getColorsManager();

    constexpr float ARROW_DIMENSION {64.f};

    if (
        cursorPosition.x > arrowHorizontalPosition and
        cursorPosition.x < arrowHorizontalPosition + ARROW_DIMENSION and
        cursorPosition.y > ARROWS_VERTICAL_POSITION and
        cursorPosition.y < ARROWS_VERTICAL_POSITION + ARROW_DIMENSION and
        not selected
    )
    {
        arrowSprite.setColor(colorsManager.getColorWhiteLowAlpha());

        selected = true;
    }
    else if (
        (
            cursorPosition.x < arrowHorizontalPosition or
            cursorPosition.x > arrowHorizontalPosition + ARROW_DIMENSION or
            cursorPosition.y < ARROWS_VERTICAL_POSITION or
            cursorPosition.y > ARROWS_VERTICAL_POSITION + ARROW_DIMENSION
        ) and selected
    )
    {
        arrowSprite.setColor(colorsManager.getColorWhite());

        selected = false;
    }
}

}
}
