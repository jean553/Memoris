/**
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

    Impl(
        utils::Context& context,
        const float& hPosition,
        const float& vPosition,
        const float& lineWidth,
        const size_t& maxCharacters
    ) :
        maximumCharacters(maxCharacters),
        horizontalPosition(hPosition),
        verticalPosition(vPosition),
        width(lineWidth)
    {
        displayedText.setFont(context.getFontsManager().getTextFont());
        displayedText.setCharacterSize(fonts::INPUT_TEXT_SIZE);
        displayedText.setColor(context.getColorsManager().getColorLightBlue());

        cursor.setFillColor(context.getColorsManager().getColorLightBlue());
        cursor.setPosition(
            horizontalPosition + 5,
            verticalPosition + 5
        );
        cursor.setSize(
            sf::Vector2f(
                25,
                50
            )
        );

        displayedText.setPosition(
            horizontalPosition + 5,
            verticalPosition
        );

        boxTop.setPosition(
            horizontalPosition,
            verticalPosition
        );

        boxBottom.setPosition(
            horizontalPosition,
            verticalPosition + 60
        );

        boxLeft.setPosition(
            horizontalPosition,
            verticalPosition
        );

        boxRight.setPosition(
            horizontalPosition + width,
            verticalPosition
        );

        boxTop.setSize(
            sf::Vector2f(
                width,
                1
            )
        );

        boxBottom.setSize(
            sf::Vector2f(
                width,
                1
            )
        );

        boxLeft.setSize(
            sf::Vector2f(
                1,
                60
            )
        );

        boxRight.setSize(
            sf::Vector2f(
                1,
                60
            )
        );

        boxRight.setFillColor(context.getColorsManager().getColorLightBlue());
        boxTop.setFillColor(context.getColorsManager().getColorLightBlue());
        boxBottom.setFillColor(context.getColorsManager().getColorLightBlue());
        boxLeft.setFillColor(context.getColorsManager().getColorLightBlue());
    }

    sf::Int32 cursorLastFlashAnimation {0};

    bool displayCursor {true};

    size_t maximumCharacters;

    float horizontalPosition;
    float verticalPosition;
    float width;

    sf::Text displayedText;

    sf::RectangleShape boxTop;
    sf::RectangleShape boxBottom;
    sf::RectangleShape boxLeft;
    sf::RectangleShape boxRight;
    sf::RectangleShape cursor;
};

/**
 *
 */
InputTextWidget::InputTextWidget(
    utils::Context& context,
    const float& hPosition,
    const float& vPosition,
    const float& lineWidth,
    const size_t& maxCharacters
) noexcept :
impl(
    std::make_unique<Impl>(
        context,
        hPosition,
        vPosition,
        lineWidth,
        maxCharacters
    )
)
{
}

/**
 *
 */
InputTextWidget::~InputTextWidget() noexcept = default;

/**
 *
 */
void InputTextWidget::setDisplayedText(const sf::String& inputTextData) &
{
    impl->displayedText.setString(inputTextData);
}

/**
 *
 */
void InputTextWidget::display(const utils::Context& context) &
{
    context.getSfmlWindow().draw(impl->boxTop);
    context.getSfmlWindow().draw(impl->boxBottom);
    context.getSfmlWindow().draw(impl->boxLeft);
    context.getSfmlWindow().draw(impl->boxRight);
    context.getSfmlWindow().draw(impl->displayedText);

    if(impl->displayCursor)
    {
        context.getSfmlWindow().draw(impl->cursor);
    }

    if(
        (
            context.getClockMillisecondsTime() -
            impl->cursorLastFlashAnimation
        ) > 200
    )
    {
        impl->displayCursor = !impl->displayCursor;

        impl->cursorLastFlashAnimation = context.getClockMillisecondsTime();
    }
}

/**
 *
 */
void InputTextWidget::update(const sf::Event& event) &
{
    if (backspaceIsPressedDown(event))
    {
        impl->displayedText.setString("");

        updateCursorPosition();

        return;
    }

    if ((impl->displayedText.getString()).getSize() == impl->maximumCharacters)
    {
        return;
    }

    impl->displayedText.setString(
        impl->displayedText.getString() + getInputLetter(event)
    );

    updateCursorPosition();
}

/**
 *
 */
const sf::String& InputTextWidget::getText() const
{
    return impl->displayedText.getString();
}

/**
 *
 */
const bool InputTextWidget::isEmpty() const &
{
    return impl->displayedText.getString().isEmpty();
}

/**
 *
 */
const sf::String InputTextWidget::getInputLetter(const sf::Event& event) &
{
    sf::String character;

    switch(event.key.code)
    {
    case sf::Keyboard::A:
    {
        character = 'a';
        break;
    }
    case sf::Keyboard::B:
    {
        character = 'b';
        break;
    }
    case sf::Keyboard::C:
    {
        character = 'c';
        break;
    }
    case sf::Keyboard::D:
    {
        character = 'd';
        break;
    }
    case sf::Keyboard::E:
    {
        character = 'e';
        break;
    }
    case sf::Keyboard::F:
    {
        character = 'f';
        break;
    }
    case sf::Keyboard::G:
    {
        character = 'g';
        break;
    }
    case sf::Keyboard::H:
    {
        character = 'h';
        break;
    }
    case sf::Keyboard::I:
    {
        character = 'i';
        break;
    }
    case sf::Keyboard::J:
    {
        character = 'j';
        break;
    }
    case sf::Keyboard::K:
    {
        character = 'k';
        break;
    }
    case sf::Keyboard::L:
    {
        character = 'l';
        break;
    }
    case sf::Keyboard::M:
    {
        character = 'm';
        break;
    }
    case sf::Keyboard::N:
    {
        character = 'n';
        break;
    }
    case sf::Keyboard::O:
    {
        character = 'o';
        break;
    }
    case sf::Keyboard::P:
    {
        character = 'p';
        break;
    }
    case sf::Keyboard::Q:
    {
        character = 'q';
        break;
    }
    case sf::Keyboard::R:
    {
        character = 'r';
        break;
    }
    case sf::Keyboard::S:
    {
        character = 's';
        break;
    }
    case sf::Keyboard::T:
    {
        character = 't';
        break;
    }
    case sf::Keyboard::U:
    {
        character = 'u';
        break;
    }
    case sf::Keyboard::V:
    {
        character = 'v';
        break;
    }
    case sf::Keyboard::W:
    {
        character = 'w';
        break;
    }
    case sf::Keyboard::X:
    {
        character = 'x';
        break;
    }
    case sf::Keyboard::Y:
    {
        character = 'y';
        break;
    }
    case sf::Keyboard::Z:
    {
        character = 'z';
        break;
    }
    default:
    {
        break;
    }
    }

    return character;
}

/**
 *
 */
const bool InputTextWidget::backspaceIsPressedDown(const sf::Event& event) &
noexcept
{
    return event.key.code == sf::Keyboard::BackSpace;
}

/**
 *
 */
void InputTextWidget::updateCursorPosition() &
{
    /* update the position of the cursor according to the new SFML text surface
       width; add 5 pixels everytime horizontaly and verticaly; we set the
       cursor exactly after the last letter; we cannot predict what is one
       character width, because it is different for all of them, so we use
       getLocalBounds() to calculate the "real" text surface width and add
       the cursor directly right after */
    impl->cursor.setPosition(
        impl->horizontalPosition + 5 +
        impl->displayedText.getLocalBounds().width,
        impl->verticalPosition + 5
    );
}

}
}
