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
 * Screen header title bar widget
 *
 * @file TitleBarWidget.hpp
 * @brief header title bar of the screen
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_TITLE_BAR_WIDGET
#define DEF_TITLE_BAR_WIDGET

#include <SFML/Graphics.hpp>

#include "../utils/Context.hpp"

#include "../defines/Colors.hpp"
#include "../defines/Fonts.hpp"

namespace widgets {
class TitleBarWidget {

    static constexpr unsigned int SIZE_TITLE_BAR_TEXT_FONT = 45;
    static constexpr unsigned int TITLE_BAR_TEXT_POSITION_X = 10;
    static constexpr unsigned int TITLE_BAR_TEXT_POSITION_Y = 10;
    static constexpr unsigned int TITLE_BAR_LINE_POSITION_X = 0;
    static constexpr unsigned int TITLE_BAR_LINE_POSITION_Y = 80;
    static constexpr unsigned int BAR_BORDER_LARGER = 1;
    static constexpr unsigned int BAR_WIDTH = 1600;

public:

    /**
     * Constructor
     *
     * @param barText        title bar text
     */
    TitleBarWidget(
        std::string barText = ""
    );
    ~TitleBarWidget();

    /**
     * @brief setter for text content
     *
     * @param text          content to set
     */
    void setText(std::string text);

    /**
     * @brief display the header title bar
     *
     * @param context       current context pointer
     */
    void display(utils::Context* context);

private:

    std::string text;

    sf::Font fontText;

    sf::Color textColor;
    sf::Color lineColor;

    sf::Text displayedText;

    sf::RectangleShape line;
};
}

#endif
