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

#include "Widget.hpp"

namespace widgets
{
class TitleBarWidget
{

    static const unsigned int SIZE_TITLE_BAR_TEXT_FONT;

    static const float TITLE_BAR_TEXT_POSITION_X;
    static const float TITLE_BAR_TEXT_POSITION_Y;
    static const float TITLE_BAR_LINE_POSITION_X;
    static const float TITLE_BAR_LINE_POSITION_Y;
    static const float BAR_BORDER_LARGER;
    static const float BAR_WIDTH;

public:

    /**
     * @param barText                content of the text bar
     */
    TitleBarWidget(std::string barText = "");

    /**
     * @brief update the displayed text content
     *
     * @param inputTextData          content to set
     */
    void setDisplayedText(std::string inputTextData);

    /**
     * @brief setter for the text
     *
     * @param inputTextData          content to set
     */
    void setText(std::string inputTextData);

    /**
     * @brief display the header title bar
     *
     * @param pContext       current pContext pointer
     */
    void display(utils::Context* pContext);

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
