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

#include "../defines/ColorsDefines.hpp"
#include "../defines/FontsDefines.hpp"

#define BOX_BORDER_LARGER 1
#define BOX_LARGER 60

#define CURSOR_WIDTH 25
#define CURSOR_HEIGHT 50

#define INTERVAL_ANIMATION_CURSOR 200

#define SIZE_INPUT_TEXT_FONT 45

#define CURSOR_HORIZONTAL_OFFSET 5
#define CURSOR_VERTICAL_OFFSET 5
#define TEXT_HORIZONTAL_OFFSET 5

namespace widgets
{
    class InputTextWidget
    {
        public:

            /**
             * Constructor
             *
             * @param int input horizontal position
             * @param int input vertical position
             * @param int input width
             * @param string input default text
             * @param int maximum characters size
             */
            InputTextWidget(
                unsigned int inputHorizontalPosition,
                unsigned int inputVerticalPosition,
                unsigned int inputWidth,
                std::string defaultText = "",
                unsigned int maxCharacters = 10
            );
            ~InputTextWidget();

            /**
             * @brief setter for input text content
             *
             * @param string content to set
             */
            void setText(std::string inputTextData);

            /**
             * @brief getter for input text content
             *
             * @return string input text content
             */
            std::string getText();

            /**
             * @brief display the input text
             * with its content
             *
             * @param Context current context pointer
             */
            void display(utils::Context* context);

            /**
             * @brief update the input text
             * content according to the event
             * pointer content
             *
             * @param Event pointer on SFML event
             */
            void update(sf::Event* event);

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
    };
}

#endif
