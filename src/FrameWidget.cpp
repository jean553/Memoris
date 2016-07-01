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
 * @file FrameWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FrameWidget.hpp"

#include "ColorsManager.hpp"

using namespace widgets;

const unsigned short FrameWidget::BORDER_WIDTH = 1;

/**
 *
 */
FrameWidget::FrameWidget(utils::Context& context)
{
    leftLine.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    rightLine.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    topLine.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    bottomLine.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());

    horizontalSize = 0;
    verticalSize = 0;
}

/**
 *
 */
void FrameWidget::display(utils::Context& context)
{
    context.getSfmlWindow().draw(leftLine);
    context.getSfmlWindow().draw(rightLine);
    context.getSfmlWindow().draw(topLine);
    context.getSfmlWindow().draw(bottomLine);
}

/**
 *
 */
void FrameWidget::setSize(
    float hSize,
    float vSize
)
{
    horizontalSize = hSize;
    verticalSize = vSize;

    leftLine.setSize(
        sf::Vector2f(
            BORDER_WIDTH,
            verticalSize
        )
    );

    rightLine.setSize(
        sf::Vector2f(
            BORDER_WIDTH,
            verticalSize
        )
    );

    topLine.setSize(
        sf::Vector2f(
            horizontalSize,
            BORDER_WIDTH
        )
    );

    bottomLine.setSize(
        sf::Vector2f(
            horizontalSize,
            BORDER_WIDTH
        )
    );
}

/**
 *
 */
void FrameWidget::setPosition(
    float hPosition,
    float vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    leftLine.setPosition(
        horizontalPosition,
        verticalPosition
    );

    topLine.setPosition(
        horizontalPosition,
        verticalPosition
    );

    rightLine.setPosition(
        horizontalPosition + horizontalSize,
        verticalPosition
    );

    bottomLine.setPosition(
        horizontalPosition,
        verticalPosition + verticalSize
    );
}
