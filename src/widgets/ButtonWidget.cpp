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
 * @file ButtonWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ButtonWidget.hpp"

using namespace widgets;

/**
 *
 */
ButtonWidget::ButtonWidget(
    unsigned int buttonHorizontalPosition,
    unsigned int buttonVerticalPosition,
    unsigned int buttonWidth,
    std::string textLabel
)
{

    horizontalPosition = buttonHorizontalPosition;
    verticalPosition = buttonVerticalPosition;
    width = buttonWidth;

    text = textLabel;

    fontButton.loadFromFile(PATH_FONT_TEXT);

    textColor.r = COLOR_WHITE_RED;
    textColor.g = COLOR_WHITE_GREEN;
    textColor.b = COLOR_WHITE_BLUE;
    textColor.a = COLOR_ALPHA_FULL;

    backgroundColor.r = COLOR_GRAY_RED;
    backgroundColor.g = COLOR_GRAY_GREEN;
    backgroundColor.b = COLOR_GRAY_BLUE;
    backgroundColor.a = COLOR_ALPHA_FULL;

    textMouseHoverColor.r = COLOR_LIGHT_BLUE_RED;
    textMouseHoverColor.g = COLOR_LIGHT_BLUE_GREEN;
    textMouseHoverColor.b = COLOR_LIGHT_BLUE_BLUE;
    textMouseHoverColor.a = COLOR_ALPHA_FULL;

    backgroundMouseHoverColor.r = COLOR_DARK_GRAY_RED;
    backgroundMouseHoverColor.g = COLOR_DARK_GRAY_GREEN;
    backgroundMouseHoverColor.b = COLOR_DARK_GRAY_BLUE;
    backgroundMouseHoverColor.a = COLOR_ALPHA_FULL;

    buttonText.setFont(fontButton);
    buttonText.setString(text);
    buttonText.setCharacterSize(SIZE_BUTTON_TEXT_FONT);
    buttonText.setPosition(
        buttonHorizontalPosition +
        (width / 2) - (buttonText.getLocalBounds().width / 2),
        buttonVerticalPosition
    );

    background.setSize(sf::Vector2f(
                           width,
                           BUTTON_FIXED_HEIGHT
                       ));
    background.setPosition(
        buttonHorizontalPosition,
        buttonVerticalPosition
    );
}

/**
 *
 */
ButtonWidget::~ButtonWidget()
{
}

/**
 *
 */
void ButtonWidget::setText(std::string inputTextData)
{
    text = inputTextData;
}

/**
 *
 */
std::string ButtonWidget::getText()
{
    return text;
}

/**
 *
 */
void ButtonWidget::display(utils::Context* context)
{
    buttonText.setColor(textColor);
    background.setFillColor(backgroundColor);

    if(isMouseHover()) {

        buttonText.setColor(textMouseHoverColor);
        background.setFillColor(backgroundMouseHoverColor);
    }

    context->getWindow()->draw(background);
    context->getWindow()->draw(buttonText);
}

/**
 *
 */
bool ButtonWidget::isMouseHover()
{
    if (
        sf::Mouse::getPosition().x > horizontalPosition &&
        sf::Mouse::getPosition().x < horizontalPosition + width &&
        sf::Mouse::getPosition().y > verticalPosition &&
        sf::Mouse::getPosition().y < verticalPosition + BUTTON_FIXED_HEIGHT
    ) {
        return true;
    }

    return false;
}
