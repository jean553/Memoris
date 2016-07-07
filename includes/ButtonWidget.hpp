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
 * Button widget
 *
 * @file ButtonWidget.hpp
 * @brief button widget
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_BUTTON_WIDGET
#define DEF_BUTTON_WIDGET

#include "Widget.hpp"

namespace widgets
{
class ButtonWidget : public Widget
{

    static const float BUTTON_FIXED_HEIGHT;

    static const unsigned int SIZE_BUTTON_TEXT_FONT;

public:

    ButtonWidget();

    /**
     * @brief set the current displayed text
     *
     * @param textLabel                 text of the button
     */
    void setLabel(std::string textLabel);

    /**
     * @brief set the size and the position of the button
     *
     * NOTE: the method setText() must be called before
     * to calculate the real required size of text in button
     *
     * @param buttonHorizontalPosition  button horizontal position
     * @param buttonVerticalPosition    button vertical position
     * @param buttonWidth               button fixed width
     */
    void setLayout(
        float buttonHorizontalPosition,
        float buttonVerticalPosition,
        float buttonWidth
    );

    /**
     * @brief setter for text content
     *
     * @param text         content to set
     */
    void setText(std::string text);

    /**
     * @brief displays the button and manage
     * button colors according to the current
     * cursor position on screen
     */
    void display();

    /**
     * Returns true if the mouse is
     * currently hover the button
     *
     * NOTE: returns false if the button
     * is disabled, even if the mouse is
     * hover the button
     *
     * @return bool
     */
    bool isMouseHover() const;

    /**
     * @param isEnable      value of enable attribute
     */
    void setEnable(bool isEnable);

private:

    std::string text;

    sf::Text buttonText;

    sf::RectangleShape background;
    sf::RectangleShape leftLine;
    sf::RectangleShape rightLine;
    sf::RectangleShape topLine;
    sf::RectangleShape bottomLine;

    float width;

    bool enable;
};
}

#endif
