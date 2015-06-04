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
 * @file TitleBarWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TitleBarWidget.hpp"

using namespace widgets;

/**
 *
 */
TitleBarWidget::TitleBarWidget(
    std::string text
) {
    text = text;

    fontText.loadFromFile(PATH_FONT_TEXT);

    textColor.r = COLOR_ORANGE_RED;
    textColor.g = COLOR_ORANGE_GREEN;
    textColor.b = COLOR_ORANGE_BLUE;
    textColor.a = COLOR_ALPHA_FULL;

    lineColor.r = COLOR_WHITE_RED;
    lineColor.g = COLOR_WHITE_GREEN;
    lineColor.b = COLOR_WHITE_BLUE;
    lineColor.a = COLOR_ALPHA_FULL;

    displayedText.setFont(fontText);
    displayedText.setString(text);
    displayedText.setCharacterSize(SIZE_TITLE_BAR_TEXT_FONT);
    displayedText.setColor(textColor);
    displayedText.setPosition(
        TITLE_BAR_TEXT_POSITION_X,
        TITLE_BAR_TEXT_POSITION_Y
    );

    line.setSize(sf::Vector2f(
        BAR_WIDTH,
        BAR_BORDER_LARGER
    ));
    line.setPosition(
        TITLE_BAR_LINE_POSITION_X,
        TITLE_BAR_LINE_POSITION_Y
    );
    line.setFillColor(lineColor);
}

/**
 *
 */
TitleBarWidget::~TitleBarWidget()
{
}

/**
 *
 */
void TitleBarWidget::setText(std::string inputTextData)
{
    text = inputTextData;
}

/**
 *
 */
std::string TitleBarWidget::getText()
{
    return text;
}

/**
 *
 */
void TitleBarWidget::display(utils::Context* context)
{
    context->getWindow()->draw(displayedText);
    context->getWindow()->draw(line);
}
