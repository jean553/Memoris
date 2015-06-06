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

#include <SFML/Graphics.hpp>

#include "../utils/Context.hpp"

#include "../defines/ColorsDefines.hpp"
#include "../defines/FontsDefines.hpp"

#define BUTTON_FIXED_HEIGHT 60
#define SIZE_BUTTON_TEXT_FONT 40

namespace widgets
{
    class ButtonWidget
    {
        public:

            /**
             * Constructor
             *
             * @param int button horizontal position
             * @param int button vertical position
             * @param int button fixed width
             * @param string text of the button
             */
            ButtonWidget(
                unsigned int buttonHorizontalPosition,
                unsigned int buttonVerticalPosition,
                unsigned int width,
                std::string textLabel = ""
            );
            ~ButtonWidget();

            /**
             * @brief setter for text content
             *
             * @param string content to set
             */
            void setText(std::string text);

            /**
             * @brief getter for text content
             *
             * @return string input text content
             */
            std::string getText();

            /**
             * @brief displays the button
             *
             * @param Context current context pointer
             */
            void display(utils::Context* context);

        private:

            std::string text;

            sf::Font fontButton;

            sf::Color buttonTextColor;
            sf::Color backgroundColor;
            
            sf::Text buttonText;

            sf::RectangleShape background;
            
            unsigned int horizontalPosition;
            unsigned int verticalPosition;
            unsigned int width;
    };
}

#endif
