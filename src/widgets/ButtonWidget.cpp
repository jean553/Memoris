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

#include "../defines/Colors.hpp"
#include "../defines/Fonts.hpp"

using namespace widgets;

/**
 *
 */
ButtonWidget::ButtonWidget()
{
    fontButton.loadFromFile(constants::Fonts::getTextFontPath());

    textColor.r = constants::Colors::COLOR_WHITE_RED;
    textColor.g = constants::Colors::COLOR_WHITE_GREEN;
    textColor.b = constants::Colors::COLOR_WHITE_BLUE;
    textColor.a = constants::Colors::COLOR_ALPHA_FULL;

    backgroundColor.r = constants::Colors::COLOR_GRAY_RED;
    backgroundColor.g = constants::Colors::COLOR_GRAY_GREEN;
    backgroundColor.b = constants::Colors::COLOR_GRAY_BLUE;
    backgroundColor.a = constants::Colors::COLOR_ALPHA_FULL;

    textColorDisable.r = constants::Colors::COLOR_WHITE_RED;
    textColorDisable.g = constants::Colors::COLOR_WHITE_GREEN;
    textColorDisable.b = constants::Colors::COLOR_WHITE_BLUE;
    textColorDisable.a = constants::Colors::COLOR_ALPHA_PARTIAL;

    backgroundColorDisable.r = constants::Colors::COLOR_GRAY_RED;
    backgroundColorDisable.g = constants::Colors::COLOR_GRAY_GREEN;
    backgroundColorDisable.b = constants::Colors::COLOR_GRAY_BLUE;
    backgroundColorDisable.a = constants::Colors::COLOR_ALPHA_PARTIAL;

    textMouseHoverColor.r = constants::Colors::COLOR_LIGHT_BLUE_RED;
    textMouseHoverColor.g = constants::Colors::COLOR_LIGHT_BLUE_GREEN;
    textMouseHoverColor.b = constants::Colors::COLOR_LIGHT_BLUE_BLUE;
    textMouseHoverColor.a = constants::Colors::COLOR_ALPHA_FULL;

    backgroundMouseHoverColor.r = constants::Colors::COLOR_DARK_GRAY_RED;
    backgroundMouseHoverColor.g = constants::Colors::COLOR_DARK_GRAY_GREEN;
    backgroundMouseHoverColor.b = constants::Colors::COLOR_DARK_GRAY_BLUE;
    backgroundMouseHoverColor.a = constants::Colors::COLOR_ALPHA_FULL;

    enable = true;
}

/**
 *
 */
void ButtonWidget::setLabel(std::string textLabel)
{
    setText(textLabel);
    buttonText.setString(text);
}

/**
 *
 */
void ButtonWidget::setLayout(
    unsigned int buttonHorizontalPosition,
    unsigned int buttonVerticalPosition,
    unsigned int buttonWidth
)
{
    horizontalPosition = buttonHorizontalPosition;
    verticalPosition = buttonVerticalPosition;
    width = buttonWidth;

    buttonText.setFont(fontButton);
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
void ButtonWidget::setText(std::string inputTextData)
{
    text = inputTextData;
}

/**
 *
 */
void ButtonWidget::display(utils::Context* pContext)
{
    if(enable) {

        buttonText.setColor(textColor);
        background.setFillColor(backgroundColor);

        if(isMouseHover()) {

            buttonText.setColor(textMouseHoverColor);
            background.setFillColor(backgroundMouseHoverColor);
        }
    } else {

        buttonText.setColor(textColorDisable);
        background.setFillColor(backgroundColorDisable);
    }

    pContext->getWindow()->draw(background);
    pContext->getWindow()->draw(buttonText);
}

/**
 *
 */
bool ButtonWidget::isMouseHover() const
{
    if (
        unsigned(sf::Mouse::getPosition().x) > horizontalPosition &&
        unsigned(sf::Mouse::getPosition().x) < horizontalPosition + width &&
        unsigned(sf::Mouse::getPosition().y) > verticalPosition &&
        unsigned(sf::Mouse::getPosition().y) < verticalPosition + BUTTON_FIXED_HEIGHT &&
        enable
    ) {
        return true;
    }

    return false;
}

/**
 *
 */
void ButtonWidget::setEnable(bool isEnable)
{
    enable = isEnable;
}
