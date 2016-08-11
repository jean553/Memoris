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
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

namespace memoris
{
namespace widgets
{

/**
 *
 */
InputTextWidget::InputTextWidget(
    const float& hPosition,
    const float& vPosition,
    const float& lineWidth,
    const size_t& maxCharacters
) :
    horizontalPosition(hPosition),
    verticalPosition(vPosition)
{
    /* set the maximum characters amount allowed in the input
       text widget according to the given parameter value */
    maximumCharacters = maxCharacters;

    /* set the width of the widget according to the given parameter */
    width = lineWidth;

    /* the font of the displayed text is the normal text font; we get a
       reference of this font from the fonts manager */
    displayedText.setFont(fonts::FontsManager::get().getTextFont());

    /* the font size is the one set in the fonts namespace; the input text
       widget has a font with a specific font size */
    displayedText.setCharacterSize(fonts::INPUT_TEXT_SIZE);

    /* get a reference of the light blue color for the input text widget
       text color */
    displayedText.setColor(colors::ColorsManager::get().getColorLightBlue());

    /* set the widget border to light blue */
    cursor.setFillColor(colors::ColorsManager::get().getColorLightBlue());

    /* the default position of the cursor surface is at the left side of the
       input text line; we set the same positions as the widget and add 5
       to put it into the borders rectangle */
    cursor.setPosition(
        horizontalPosition + 5,
        verticalPosition + 5
    );

    /* the size of the flashing cursor has a width of 25 pixels and a height
       of 50 pixels; this cursor size matches with the font size */
    cursor.setSize(sf::Vector2f(
                       25,
                       50
                   ));

    /* set the position of the displayed text; by default, the displayed text
       position is the same one as the cursor one; to match with the container
       size, the vertical position is the same as the widget */
    displayedText.setPosition(
        horizontalPosition + 5,
        verticalPosition
    );

    /* the position of the top border is the same as the widget */
    boxTop.setPosition(
        horizontalPosition,
        verticalPosition
    );

    /* the position of the bottom border is 60 pixels under the top border */
    boxBottom.setPosition(
        horizontalPosition,
        verticalPosition + 60
    );

    /* the position of the left border is the same as the widget */
    boxLeft.setPosition(
        horizontalPosition,
        verticalPosition
    );

    /* to find the horizontal position of the right border, we add the width
       value to the widget horizontal position */
    boxRight.setPosition(
        horizontalPosition + width,
        verticalPosition
    );

    /* the width of the horizontal borders are equals to the widgets widths */
    boxTop.setSize(sf::Vector2f(
                       width,
                       1
                   ));

    boxBottom.setSize(sf::Vector2f(
                          width,
                          1
                      ));

    /* the height of the vertical borders are equals to the widget fixed
       height */
    boxLeft.setSize(sf::Vector2f(
                        1,
                        60
                    ));

    boxRight.setSize(sf::Vector2f(
                         1,
                         60
                     ));

    /* all the borders have the same light blue color */
    boxRight.setFillColor(colors::ColorsManager::get().getColorLightBlue());
    boxTop.setFillColor(colors::ColorsManager::get().getColorLightBlue());
    boxBottom.setFillColor(colors::ColorsManager::get().getColorLightBlue());
    boxLeft.setFillColor(colors::ColorsManager::get().getColorLightBlue());
}

/**
 *
 */
void InputTextWidget::setDisplayedText(const sf::String& inputTextData)
{
    displayedText.setString(inputTextData);
}

/**
 *
 */
void InputTextWidget::display(std::shared_ptr<utils::Context> context)
{
    /* display the widget borders */
    context->getSfmlWindow().draw(boxTop);
    context->getSfmlWindow().draw(boxBottom);
    context->getSfmlWindow().draw(boxLeft);
    context->getSfmlWindow().draw(boxRight);

    /* display the widget text */
    context->getSfmlWindow().draw(displayedText);

    /* the widget cursor is animated; the displayedCursor boolean is used to
       check if the cursor has to be displayed or not */
    if(displayCursor)
    {
        context->getSfmlWindow().draw(cursor);
    }

    /* check if enough time elapsed since the last animation update of the
       cursor; the interval between each animation is 200 milliseconds */
    if(
        (
            context->getClockMillisecondsTime() -
            cursorLastFlashAnimation
        ) > 200
    )
    {

        /* if the cursor was displayed, we hide it; if the cursor was hidden,
           we show it */
        displayCursor = !displayCursor;

        /* update the cursor animation time with the current time just after
           the animation */
        cursorLastFlashAnimation =
            context->getClockMillisecondsTime();
    }
}

/**
 *
 */
void InputTextWidget::update(const sf::Event& event)
{
    /* check if the pressed key is the backspace; in that case, just empty
       the whole field */
    if (backspaceIsPressedDown(event))
    {
        /* clear the widget content; set an empty string as the SFML text
           surface content */
        displayedText.setString("");

        /* update the cursor position */
        updateCursorPosition();

        return;
    }

    /* do not allow to continue to write content if the input text widget
       already contains the maximum amount of characters allowed */
    if (
        (displayedText.getString()).getSize() ==
        maximumCharacters
    )
    {
        return;
    }

    /* make a concatenation of the existing SFML string with the new added
       string; save it as the new displayed string */
    displayedText.setString(
        displayedText.getString() + getInputLetter(event)
    );

    /* update the cursor position */
    updateCursorPosition();
}

/**
 *
 */
sf::String InputTextWidget::getText() const
{
    return displayedText.getString();
}

/**
 *
 */
bool InputTextWidget::isEmpty() const
{
    /* use directly the SFML string function */
    return displayedText.getString().isEmpty();
}

/**
 *
 */
sf::String InputTextWidget::getInputLetter(const sf::Event& event)
{
    /* creates an empty SFML string */
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
        /* does nothing, added for best practices */
        break;
    }
    }

    return character;
}

/**
 *
 */
const bool InputTextWidget::backspaceIsPressedDown(const sf::Event& event)
{
    return event.key.code == sf::Keyboard::BackSpace;
}

/**
 *
 */
void InputTextWidget::updateCursorPosition()
{
    /* update the position of the cursor according to the new SFML text surface
       width; add 5 pixels everytime horizontaly and verticaly; we set the
       cursor exactly after the last letter; we cannot predict what is one
       character width, because it is different for all of them, so we use
       getLocalBounds() to calculate the "real" text surface width and add
       the cursor directly right after */
    cursor.setPosition(
        horizontalPosition +
        5 +
        displayedText.getLocalBounds().width,
        verticalPosition +
        5
    );
}

}
}
