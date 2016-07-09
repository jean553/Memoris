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

#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

using namespace widgets;

const float ButtonWidget::BUTTON_FIXED_HEIGHT = 60;

const unsigned int ButtonWidget::SIZE_BUTTON_TEXT_FONT = 40;

/**
 *
 */
ButtonWidget::ButtonWidget()
{
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
    float buttonHorizontalPosition,
    float buttonVerticalPosition,
    float buttonWidth
)
{
    width = buttonWidth;

    setPosition(
        buttonHorizontalPosition,
        buttonVerticalPosition
    );

    buttonText.setFont(memoris::fonts::FontsManager::get().getTextFont());
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

    topLine.setSize(
        sf::Vector2f(width, 1)
    );
    bottomLine.setSize(
        sf::Vector2f(width, 1)
    );
    leftLine.setSize(
        sf::Vector2f(1, BUTTON_FIXED_HEIGHT)
    );
    rightLine.setSize(
        sf::Vector2f(1, BUTTON_FIXED_HEIGHT)
    );

    topLine.setPosition(
        buttonHorizontalPosition,
        buttonVerticalPosition
    );
    bottomLine.setPosition(
        buttonHorizontalPosition,
        buttonVerticalPosition + BUTTON_FIXED_HEIGHT
    );
    leftLine.setPosition(
        buttonHorizontalPosition,
        buttonVerticalPosition
    );
    rightLine.setPosition(
        buttonHorizontalPosition + width,
        buttonVerticalPosition
    );

    topLine.setFillColor(
        memoris::colors::ColorsManager::get().getColorWhite()
    );
    bottomLine.setFillColor(
        memoris::colors::ColorsManager::get().getColorWhite()
    );
    leftLine.setFillColor(
        memoris::colors::ColorsManager::get().getColorWhite()
    );
    rightLine.setFillColor(
        memoris::colors::ColorsManager::get().getColorWhite()
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
void ButtonWidget::display()
{
    if(enable)
    {

        buttonText.setColor(
            memoris::colors::ColorsManager::get().getColorWhite()
        );
        background.setFillColor(
            memoris::colors::ColorsManager::get().getColorGrey()
        );

        if(isMouseHover())
        {

            buttonText.setColor(
                memoris::colors::ColorsManager::get().getColorLightBlue()
            );
            background.setFillColor(
                memoris::colors::ColorsManager::get().getColorDarkGrey()
            );
        }
    }
    else
    {

        buttonText.setColor(
            memoris::colors::ColorsManager::get().getColorPartialWhite()
        );
        background.setFillColor(
            memoris::colors::ColorsManager::get().getColorPartialGrey()
        );
    }

    memoris::utils::Context::get().getSfmlWindow().draw(background);
    memoris::utils::Context::get().getSfmlWindow().draw(topLine);
    memoris::utils::Context::get().getSfmlWindow().draw(bottomLine);
    memoris::utils::Context::get().getSfmlWindow().draw(leftLine);
    memoris::utils::Context::get().getSfmlWindow().draw(rightLine);
    memoris::utils::Context::get().getSfmlWindow().draw(buttonText);
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
        (
            unsigned(sf::Mouse::getPosition().y) <
            verticalPosition + BUTTON_FIXED_HEIGHT
        ) &&
        enable
    )
    {
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
