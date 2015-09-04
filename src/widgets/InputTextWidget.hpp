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

#include <SFML/Graphics.hpp>

#include "../utils/Context.hpp"

#include "../defines/Colors.hpp"
#include "../defines/Fonts.hpp"

namespace widgets {
class InputTextWidget {

    static constexpr unsigned int BOX_BORDER_LARGER = 1;
    static constexpr unsigned int BOX_LARGER = 60;
    static constexpr unsigned int CURSOR_WIDTH = 25;
    static constexpr unsigned int CURSOR_HEIGHT = 50;
    static constexpr int INTERVAL_ANIMATION_CURSOR = 200;
    static constexpr unsigned int SIZE_INPUT_TEXT_FONT = 45;
    static constexpr unsigned int CURSOR_HORIZONTAL_OFFSET = 5;
    static constexpr unsigned int CURSOR_VERTICAL_OFFSET = 5;
    static constexpr unsigned int TEXT_HORIZONTAL_OFFSET = 5;
    static constexpr unsigned int DEFAULT_MAXIMUM_CHARACTERS = 10;

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
        unsigned int inputHorizontalPosition,
        unsigned int inputVerticalPosition,
        unsigned int inputWidth
    );

    /**
     * @param maxCharacters     setter value
     */
    void setMaximumCharacters(unsigned int maxCharacters);

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
     * @param context       current context pointer
     */
    void display(utils::Context* context);

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

    unsigned int horizontalPosition;
    unsigned int verticalPosition;
    unsigned int width;
    unsigned int maximumCharacters;

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
