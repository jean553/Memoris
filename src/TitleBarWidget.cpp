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

#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

using namespace widgets;

const unsigned int TitleBarWidget::SIZE_TITLE_BAR_TEXT_FONT = 45;

const float TitleBarWidget::TITLE_BAR_TEXT_POSITION_X = 10;
const float TitleBarWidget::TITLE_BAR_TEXT_POSITION_Y = 10;
const float TitleBarWidget::TITLE_BAR_LINE_POSITION_X = 0;
const float TitleBarWidget::TITLE_BAR_LINE_POSITION_Y = 80;
const float TitleBarWidget::BAR_BORDER_LARGER = 1;
const float TitleBarWidget::BAR_WIDTH = 1600;

/**
 *
 */
TitleBarWidget::TitleBarWidget(
    std::string barText
)
{
    setText(barText);

    displayedText.setFont(memoris::fonts::FontsManager::get().getTextFont());
    displayedText.setString(text);
    displayedText.setCharacterSize(SIZE_TITLE_BAR_TEXT_FONT);
    displayedText.setColor(memoris::colors::ColorsManager::get().getColorOrange());
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
    line.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
}

/**
 *
 */
void TitleBarWidget::setDisplayedText(std::string inputTextData)
{
    setText(inputTextData);
    displayedText.setString(inputTextData);
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
void TitleBarWidget::display()
{
    memoris::utils::Context::get().getSfmlWindow().draw(displayedText);
    memoris::utils::Context::get().getSfmlWindow().draw(line);
}
