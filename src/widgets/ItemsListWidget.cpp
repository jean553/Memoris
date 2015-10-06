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

#include "../defines/Fonts.hpp"

using namespace widgets;

const std::string ItemsListWidget::PATH_IMAGE_ARROW_UP = "res/images/up.png";
const std::string ItemsListWidget::PATH_IMAGE_ARROW_DOWN = "res/images/down.png";

/**
 *
 */
ItemsListWidget::ItemsListWidget()
{
    textItemFont.loadFromFile(constants::Fonts::getTextFontPath());

    color.r = constants::Colors::COLOR_WHITE_RED;
    color.g = constants::Colors::COLOR_WHITE_GREEN;
    color.b = constants::Colors::COLOR_WHITE_BLUE;
    color.a = constants::Colors::COLOR_ALPHA_FULL;

    boxTop.setFillColor(color);
    boxBottom.setFillColor(color);
    boxLeft.setFillColor(color);
    boxRight.setFillColor(color);

    textureUp.loadFromFile(PATH_IMAGE_ARROW_UP);
    spriteUp.setTexture(textureUp, true);

    textureDown.loadFromFile(PATH_IMAGE_ARROW_DOWN);
    spriteDown.setTexture(textureDown, true);
}

/**
 *
 */
ItemsListWidget::~ItemsListWidget()
{
    for(sf::Text* item : textItemsList) {
        delete item;
    }
}

/**
 *
 */
void ItemsListWidget::setLayout(
    int widgetHorizontalPosition,
    int widgetVerticalPosition,
    int widgetWidth,
    unsigned char verticalTextContainers
)
{
    horizontalPosition = widgetHorizontalPosition;
    verticalPosition = widgetVerticalPosition;
    width = widgetWidth;
    verticalContainers = verticalTextContainers;

    boxTop.setPosition(
        horizontalPosition,
        verticalPosition
    );

    boxBottom.setPosition(
        horizontalPosition,
        verticalPosition +
        verticalContainers *
        ITEMS_LIST_ITEM_HEIGHT
    );

    boxLeft.setPosition(
        horizontalPosition,
        verticalPosition
    );

    boxRight.setPosition(
        horizontalPosition +
        width,
        verticalPosition
    );

    spriteUp.setPosition(
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM,
        verticalPosition
    );

    spriteDown.setPosition(
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM,
        verticalPosition +
        verticalContainers *
        ITEMS_LIST_ITEM_HEIGHT -
        ITEMS_LIST_ARROW_DIM
    );

    boxTop.setSize(sf::Vector2f(
                       width,
                       ITEMS_LIST_BORDER_SIZE
                   ));

    boxBottom.setSize(sf::Vector2f(
                          width,
                          ITEMS_LIST_BORDER_SIZE
                      ));

    boxLeft.setSize(sf::Vector2f(
                        ITEMS_LIST_BORDER_SIZE,
                        verticalContainers *
                        ITEMS_LIST_ITEM_HEIGHT
                    ));

    boxRight.setSize(sf::Vector2f(
                         ITEMS_LIST_BORDER_SIZE,
                         verticalContainers *
                         ITEMS_LIST_ITEM_HEIGHT
                     ));
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

    for(sf::Text* item : textItemsList) {
        context->getWindow()->draw(*item);
    }
}

/**
 *
 */
void ItemsListWidget::setStringsList(std::vector<std::string> list)
{
    stringsList = list;
}

/**
 *
 */
void ItemsListWidget::addTextItem(std::string textItem)
{
    stringsList.push_back(textItem);

    sf::Text *pItem = new sf::Text();

    pItem->setFont(textItemFont);
    pItem->setCharacterSize(ITEMS_LIST_ITEM_HEIGHT);
    pItem->setColor(color);
    pItem->setString(textItem);
    pItem->setPosition(
        horizontalPosition,
        verticalPosition +
        (static_cast<int> (textItemsList.size())) *
        ITEMS_LIST_ITEM_HEIGHT
    );

    textItemsList.push_back(pItem);
}
