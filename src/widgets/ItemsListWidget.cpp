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
 * @file ItemsListWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ItemsListWidget.hpp"

using namespace widgets;

const std::string ItemsListWidget::PATH_IMAGE_ARROW_UP = "res/images/up.png";
const std::string ItemsListWidget::PATH_IMAGE_ARROW_DOWN = "res/images/down.png";

/**
 *
 */
ItemsListWidget::ItemsListWidget(
    int widgetHorizontalPosition,
    int widgetVerticalPosition,
    int widgetWidth,
    unsigned char verticalTextContainers
)
{

    horizontalPosition = widgetHorizontalPosition;
    verticalPosition = widgetVerticalPosition;
    width = widgetWidth;

    borderColor.r = constants::Colors::COLOR_WHITE_RED;
    borderColor.g = constants::Colors::COLOR_WHITE_GREEN;
    borderColor.b = constants::Colors::COLOR_WHITE_BLUE;
    borderColor.a = constants::Colors::COLOR_ALPHA_FULL;

    boxTop.setSize(sf::Vector2f(
                       width,
                       ITEMS_LIST_BORDER_SIZE
                   ));
    boxTop.setPosition(
        horizontalPosition,
        verticalPosition
    );
    boxTop.setFillColor(borderColor);

    boxBottom.setSize(sf::Vector2f(
                          width,
                          ITEMS_LIST_BORDER_SIZE
                      ));
    boxBottom.setPosition(
        horizontalPosition,
        verticalPosition +
        verticalTextContainers *
        ITEMS_LIST_ITEM_HEIGHT
    );
    boxBottom.setFillColor(borderColor);

    boxLeft.setSize(sf::Vector2f(
                        ITEMS_LIST_BORDER_SIZE,
                        verticalTextContainers *
                        ITEMS_LIST_ITEM_HEIGHT
                    ));
    boxLeft.setPosition(
        horizontalPosition,
        verticalPosition
    );
    boxLeft.setFillColor(borderColor);

    boxRight.setSize(sf::Vector2f(
                         ITEMS_LIST_BORDER_SIZE,
                         verticalTextContainers *
                         ITEMS_LIST_ITEM_HEIGHT
                     ));
    boxRight.setPosition(
        horizontalPosition +
        width,
        verticalPosition
    );
    boxRight.setFillColor(borderColor);

    textureUp.loadFromFile(PATH_IMAGE_ARROW_UP);
    textureDown.loadFromFile(PATH_IMAGE_ARROW_DOWN);

    spriteUp.setTexture(textureUp, true);
    spriteUp.setPosition(
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM,
        verticalPosition
    );

    spriteDown.setTexture(textureDown, true);
    spriteDown.setPosition(
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM,
        verticalPosition +
        verticalTextContainers *
        ITEMS_LIST_ITEM_HEIGHT -
        ITEMS_LIST_ARROW_DIM
    );
}

/**
 *
 */
ItemsListWidget::~ItemsListWidget()
{
}

/**
 *
 */
void ItemsListWidget::display(utils::Context* context)
{
    context->getWindow()->draw(boxTop);
    context->getWindow()->draw(boxBottom);
    context->getWindow()->draw(boxLeft);
    context->getWindow()->draw(boxRight);
    context->getWindow()->draw(spriteUp);
    context->getWindow()->draw(spriteDown);
}
