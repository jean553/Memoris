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

using namespace widgets;

const unsigned short InputTextWidget::BOX_BORDER_LARGER = 1;
const unsigned short InputTextWidget::BOX_LARGER = 60;
const unsigned short InputTextWidget::CURSOR_WIDTH = 25;
const unsigned short InputTextWidget::CURSOR_HEIGHT = 50;
const unsigned short InputTextWidget::SIZE_INPUT_TEXT_FONT = 45;
const unsigned short InputTextWidget::CURSOR_HORIZONTAL_OFFSET = 5;
const unsigned short InputTextWidget::CURSOR_VERTICAL_OFFSET = 5;
const unsigned short InputTextWidget::TEXT_HORIZONTAL_OFFSET = 5;
const unsigned short InputTextWidget::DEFAULT_MAXIMUM_CHARACTERS = 10;

const short InputTextWidget::INTERVAL_ANIMATION_CURSOR = 200;

/**
 *
 */
InputTextWidget::InputTextWidget()
{
    displayCursor = true;
    setMaximumCharacters(DEFAULT_MAXIMUM_CHARACTERS);

    displayedText.setFont(memoris::fonts::FontsManager::get().getTextFont());
    displayedText.setCharacterSize(SIZE_INPUT_TEXT_FONT);
    displayedText.setColor(memoris::colors::ColorsManager::get().getColorLightBlue());

    cursor.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());
}

/**
 *
 */
void InputTextWidget::setMaximumCharacters(unsigned short maxCharacters)
{
    maximumCharacters = maxCharacters;
}

/**
 *
 */
void InputTextWidget::setLayout(
    float inputHorizontalPosition,
    float inputVerticalPosition,
    float inputWidth
)
{
    width = inputWidth;

    setPosition(
        inputHorizontalPosition,
        inputVerticalPosition
    );

    displayedText.setPosition(
        horizontalPosition + TEXT_HORIZONTAL_OFFSET,
        verticalPosition
    );
    boxTop.setPosition(
        horizontalPosition,
        verticalPosition
    );
    boxBottom.setPosition(
        horizontalPosition,
        verticalPosition + BOX_LARGER
    );
    boxLeft.setPosition(
        horizontalPosition,
        verticalPosition
    );
    boxRight.setPosition(
        horizontalPosition + width,
        verticalPosition
    );

    boxTop.setSize(sf::Vector2f(
                       width,
                       BOX_BORDER_LARGER
                   ));
    boxBottom.setSize(sf::Vector2f(
                          width,
                          BOX_BORDER_LARGER
                      ));
    boxLeft.setSize(sf::Vector2f(
                        BOX_BORDER_LARGER,
                        BOX_LARGER
                    ));
    boxRight.setSize(sf::Vector2f(
                         BOX_BORDER_LARGER,
                         BOX_LARGER
                     ));

    boxRight.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    boxTop.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    boxBottom.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    boxLeft.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());

    initCursorPosition();

    cursor.setSize(sf::Vector2f(
                       CURSOR_WIDTH,
                       CURSOR_HEIGHT
                   ));
}

/**
 *
 */
void InputTextWidget::setDisplayedText(std::string inputTextData)
{
    setText(inputTextData);
    displayedText.setString(inputTextData);
}

/**
 *
 */
void InputTextWidget::setText(std::string inputTextData)
{
    text = inputTextData;
}

/**
 *
 */
void InputTextWidget::display()
{
    memoris::utils::Context::get().getSfmlWindow().draw(boxTop);
    memoris::utils::Context::get().getSfmlWindow().draw(boxBottom);
    memoris::utils::Context::get().getSfmlWindow().draw(boxLeft);
    memoris::utils::Context::get().getSfmlWindow().draw(boxRight);
    memoris::utils::Context::get().getSfmlWindow().draw(displayedText);

    if(displayCursor)
    {
        memoris::utils::Context::get().getSfmlWindow().draw(cursor);
    }

    if(clock.getElapsedTime().asMilliseconds() >
            INTERVAL_ANIMATION_CURSOR
      )
    {
        displayCursor = !displayCursor;
        clock.restart();
    }
}

/**
 *
 */
void InputTextWidget::update(sf::Event* event)
{
    std::string newText = "";

    switch(event->key.code)
    {
    case sf::Keyboard::A:
    {
        newText = text + 'a';
        break;
    }
    case sf::Keyboard::B:
    {
        newText = text + 'b';
        break;
    }
    case sf::Keyboard::C:
    {
        newText = text + 'c';
        break;
    }
    case sf::Keyboard::D:
    {
        newText = text + 'd';
        break;
    }
    case sf::Keyboard::E:
    {
        newText = text + 'e';
        break;
    }
    case sf::Keyboard::F:
    {
        newText = text + 'f';
        break;
    }
    case sf::Keyboard::G:
    {
        newText = text + 'g';
        break;
    }
    case sf::Keyboard::H:
    {
        newText = text + 'h';
        break;
    }
    case sf::Keyboard::I:
    {
        newText = text + 'i';
        break;
    }
    case sf::Keyboard::J:
    {
        newText = text + 'j';
        break;
    }
    case sf::Keyboard::K:
    {
        newText = text + 'k';
        break;
    }
    case sf::Keyboard::L:
    {
        newText = text + 'l';
        break;
    }
    case sf::Keyboard::M:
    {
        newText = text + 'm';
        break;
    }
    case sf::Keyboard::N:
    {
        newText = text + 'n';
        break;
    }
    case sf::Keyboard::O:
    {
        newText = text + 'o';
        break;
    }
    case sf::Keyboard::P:
    {
        newText = text + 'p';
        break;
    }
    case sf::Keyboard::Q:
    {
        newText = text + 'q';
        break;
    }
    case sf::Keyboard::R:
    {
        newText = text + 'r';
        break;
    }
    case sf::Keyboard::S:
    {
        newText = text + 's';
        break;
    }
    case sf::Keyboard::T:
    {
        newText = text + 't';
        break;
    }
    case sf::Keyboard::U:
    {
        newText = text + 'u';
        break;
    }
    case sf::Keyboard::V:
    {
        newText = text + 'v';
        break;
    }
    case sf::Keyboard::W:
    {
        newText = text + 'w';
        break;
    }
    case sf::Keyboard::X:
    {
        newText = text + 'x';
        break;
    }
    case sf::Keyboard::Y:
    {
        newText = text + 'y';
        break;
    }
    case sf::Keyboard::Z:
    {
        newText = text + 'z';
        break;
    }
    case sf::Keyboard::BackSpace:
    {
        newText = text.substr(0, text.size() - 1);
        break;
    }
    default:
    {
        return;
    }
    }

    if(newText.size() > maximumCharacters)
    {
        return;
    }

    text = newText;
    displayedText.setString(text);

    cursor.setPosition(
        horizontalPosition +
        CURSOR_HORIZONTAL_OFFSET +
        displayedText.getLocalBounds().width,
        verticalPosition +
        CURSOR_VERTICAL_OFFSET
    );
}

/**
 *
 */
void InputTextWidget::clear()
{
    setDisplayedText("");
    initCursorPosition();
}

/**
 *
 */
void InputTextWidget::initCursorPosition()
{
    cursor.setPosition(
        horizontalPosition + CURSOR_HORIZONTAL_OFFSET,
        verticalPosition + CURSOR_VERTICAL_OFFSET
    );
}

/**
 *
 */
std::string InputTextWidget::getText()
{
    return text;
}
