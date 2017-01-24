/**
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
 * @file InputTextWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "InputTextWidget.hpp"

#include "fonts.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{
namespace widgets
{

class InputTextWidget::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
    {
        displayedText.setFont(context.getFontsManager().getTextFont());
        displayedText.setCharacterSize(fonts::INPUT_TEXT_SIZE);

        cursor.setPosition(
            HORIZONTAL_POSITION + CURSOR_AND_BORDER_DISTANCE,
            VERTICAL_POSITION + CURSOR_AND_BORDER_DISTANCE
        );

        constexpr float CURSOR_WIDTH {25.f}, CURSOR_HEIGHT {50.f};
        cursor.setSize(
            sf::Vector2f(
                CURSOR_WIDTH,
                CURSOR_HEIGHT
            )
        );

        displayedText.setPosition(
            HORIZONTAL_POSITION + CURSOR_AND_BORDER_DISTANCE,
            VERTICAL_POSITION
        );

        boxTop.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );

        constexpr float BOX_HEIGHT {60.f};
        boxBottom.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION + BOX_HEIGHT
        );

        boxLeft.setPosition(
            HORIZONTAL_POSITION,
            VERTICAL_POSITION
        );

        constexpr float WIDGET_WIDTH {600.f};

        boxRight.setPosition(
            HORIZONTAL_POSITION + WIDGET_WIDTH,
            VERTICAL_POSITION
        );

        constexpr float BORDER_WIDTH {1.f};

        boxTop.setSize(
            sf::Vector2f(
                WIDGET_WIDTH,
                BORDER_WIDTH
            )
        );

        boxBottom.setSize(
            sf::Vector2f(
                WIDGET_WIDTH,
                BORDER_WIDTH
            )
        );

        boxLeft.setSize(
            sf::Vector2f(
                BORDER_WIDTH,
                BOX_HEIGHT
            )
        );

        boxRight.setSize(
            sf::Vector2f(
                BORDER_WIDTH,
                BOX_HEIGHT
            )
        );

        const auto& lightBlue = context.getColorsManager().getColorLightBlue();
        displayedText.setColor(lightBlue);
        cursor.setFillColor(lightBlue);
        boxRight.setFillColor(lightBlue);
        boxTop.setFillColor(lightBlue);
        boxBottom.setFillColor(lightBlue);
        boxLeft.setFillColor(lightBlue);
    }

    sf::Int32 cursorLastFlashAnimation {0};

    bool displayCursor {true};

    sf::Text displayedText;

    sf::RectangleShape boxTop;
    sf::RectangleShape boxBottom;
    sf::RectangleShape boxLeft;
    sf::RectangleShape boxRight;
    sf::RectangleShape cursor;

    const utils::Context& context;
};

/**
 *
 */
InputTextWidget::InputTextWidget(const utils::Context& context)
    : impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
InputTextWidget::~InputTextWidget() = default;

/**
 *
 */
void InputTextWidget::display() const &
{
    const auto& context = impl->context;

    auto& window = context.getSfmlWindow();
    window.draw(impl->boxTop);
    window.draw(impl->boxBottom);
    window.draw(impl->boxLeft);
    window.draw(impl->boxRight);
    window.draw(impl->displayedText);

    auto& displayCursor = impl->displayCursor;

    if(displayCursor)
    {
        window.draw(impl->cursor);
    }

    const auto& currentTime = context.getClockMillisecondsTime();
    auto& lastTime = impl->cursorLastFlashAnimation;

    constexpr sf::Int32 CURSOR_ANIMATION_INTERVAL {200};
    if (currentTime - lastTime > CURSOR_ANIMATION_INTERVAL)
    {
        displayCursor = !displayCursor;
        lastTime = currentTime;
    }
}

/**
 *
 */
void InputTextWidget::update(const sf::Event& event) const &
{
    auto& text = impl->displayedText;

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        text.setString("");

        updateCursorPosition();

        return;
    }

    const char newCharacter {getInputLetter(event)};
    if (newCharacter == 0)
    {
        return;
    }

    const sf::String newString {newCharacter};
    text.setString(text.getString() + newString);

    updateCursorPosition();
}

/**
 *
 */
const sf::String& InputTextWidget::getText() const &
{
    return impl->displayedText.getString();
}

/**
 *
 */
const char InputTextWidget::getInputLetter(const sf::Event& event) const &
    noexcept
{
    switch(event.key.code)
    {
    case sf::Keyboard::A:
    {
        return 'a';
        break;
    }
    case sf::Keyboard::B:
    {
        return 'b';
        break;
    }
    case sf::Keyboard::C:
    {
        return 'c';
        break;
    }
    case sf::Keyboard::D:
    {
        return 'd';
        break;
    }
    case sf::Keyboard::E:
    {
        return 'e';
        break;
    }
    case sf::Keyboard::F:
    {
        return 'f';
        break;
    }
    case sf::Keyboard::G:
    {
        return 'g';
        break;
    }
    case sf::Keyboard::H:
    {
        return 'h';
        break;
    }
    case sf::Keyboard::I:
    {
        return 'i';
        break;
    }
    case sf::Keyboard::J:
    {
        return 'j';
        break;
    }
    case sf::Keyboard::K:
    {
        return 'k';
        break;
    }
    case sf::Keyboard::L:
    {
        return 'l';
        break;
    }
    case sf::Keyboard::M:
    {
        return 'm';
        break;
    }
    case sf::Keyboard::N:
    {
        return 'n';
        break;
    }
    case sf::Keyboard::O:
    {
        return 'o';
        break;
    }
    case sf::Keyboard::P:
    {
        return 'p';
        break;
    }
    case sf::Keyboard::Q:
    {
        return 'q';
        break;
    }
    case sf::Keyboard::R:
    {
        return 'r';
        break;
    }
    case sf::Keyboard::S:
    {
        return 's';
        break;
    }
    case sf::Keyboard::T:
    {
        return 't';
        break;
    }
    case sf::Keyboard::U:
    {
        return 'u';
        break;
    }
    case sf::Keyboard::V:
    {
        return 'v';
        break;
    }
    case sf::Keyboard::W:
    {
        return 'w';
        break;
    }
    case sf::Keyboard::X:
    {
        return 'x';
        break;
    }
    case sf::Keyboard::Y:
    {
        return 'y';
        break;
    }
    case sf::Keyboard::Z:
    {
        return 'z';
        break;
    }
    default:
    {
        return 0;
        break;
    }
    }
}

/**
 *
 */
void InputTextWidget::updateCursorPosition() const &
{
    impl->cursor.setPosition(
        HORIZONTAL_POSITION + CURSOR_AND_BORDER_DISTANCE +
        impl->displayedText.getLocalBounds().width,
        VERTICAL_POSITION + CURSOR_AND_BORDER_DISTANCE
    );
}

/**
 *
 */
const bool InputTextWidget::isInputTextLineFull() const &
{
    constexpr size_t MAXIMUM_CHARACTERS_AMOUNT {15};
    return impl->displayedText.getString().getSize() ==
        MAXIMUM_CHARACTERS_AMOUNT;
}

}
}
