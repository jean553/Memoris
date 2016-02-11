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
 * Input text box widget
 *
 * @file InputTextWidget.hpp
 * @brief input text box widget
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_INPUT_TEXT_WIDGET
#define DEF_INPUT_TEXT_WIDGET

#include <string>

#include "Widget.hpp"

namespace widgets {
class InputTextWidget : public Widget {

    static const unsigned short BOX_BORDER_LARGER = 1;
    static const unsigned short BOX_LARGER = 60;
    static const unsigned short CURSOR_WIDTH = 25;
    static const unsigned short CURSOR_HEIGHT = 50;
    static const unsigned short SIZE_INPUT_TEXT_FONT = 45;
    static const unsigned short CURSOR_HORIZONTAL_OFFSET = 5;
    static const unsigned short CURSOR_VERTICAL_OFFSET = 5;
    static const unsigned short TEXT_HORIZONTAL_OFFSET = 5;
    static const unsigned short DEFAULT_MAXIMUM_CHARACTERS = 10;

    static const short INTERVAL_ANIMATION_CURSOR = 200;

public:

    InputTextWidget();

    /**
     * @brief set the size and the position of the widget
     *
     * @param inputHorizontalPosition    input horizontal position
     * @param inputVerticalPosition      input vertical position
     * @param inputWidth                 input width
     */
    void setLayout(
        float inputHorizontalPosition,
        float inputVerticalPosition,
        float inputWidth
    );

    /**
     * @param maxCharacters     setter value
     */
    void setMaximumCharacters(unsigned short maxCharacters);

    /**
     * @brief set the displayed text
     *
     * @param inputTextData content to set
     */
    void setDisplayedText(std::string inputTextData);

    /**
     * @brief setter for input text content
     *
     * @param inputTextData content to set
     */
    void setText(std::string inputTextData);

    /**
     * @brief display the input text
     * with its content
     *
     * @param pContext       current pContext pointer
     */
    void display(utils::Context* pContext);

    /**
     * @brief update the input text
     * content according to the event
     * pointer content
     *
     * @param event         pointer on SFML event
     */
    void update(sf::Event* event);

    /**
     * @brief reset the input text
     */
    void clear();

    /**
     * @brief return the current displayed text
     *
     * @return string
     */
    std::string getText();

private:

    bool displayCursor;

    float horizontalPosition;
    float verticalPosition;
    float width;
    unsigned short maximumCharacters;

    std::string text;

    sf::Font fontInputText;

    sf::Color inputTextColor;

    sf::Text displayedText;

    sf::RectangleShape boxTop;
    sf::RectangleShape boxBottom;
    sf::RectangleShape boxLeft;
    sf::RectangleShape boxRight;
    sf::RectangleShape cursor;

    sf::Clock clock;

    /**
     * @brief initialize the cursor position on the left side of the input
     *
     * NOTE: must be called AFTER the cursor object creation, the horizontal
     * and vertical positions of the input text must be defined
     */
    void initCursorPosition();
};
}

#endif
