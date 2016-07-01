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

#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

using namespace widgets;

const std::string ItemsListWidget::PATH_IMAGE_ARROW_UP = "res/images/up.png";
const std::string ItemsListWidget::PATH_IMAGE_ARROW_DOWN = "res/images/down.png";

const float ItemsListWidget::ITEMS_LIST_BORDER_SIZE = 1;
const float ItemsListWidget::ITEMS_LIST_ARROW_DIM = 40;
const float ItemsListWidget::ITEMS_LIST_TEXT_OFFSET = 5;
const unsigned int ItemsListWidget::ITEMS_LIST_ITEM_HEIGHT = 40;

/**
 *
 */
ItemsListWidget::ItemsListWidget(utils::Context& context)
{
    boxTop.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    boxBottom.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    boxLeft.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    boxRight.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    selector.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    arrowUpSelector.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    arrowDownSelector.setFillColor(memoris::colors::ColorsManager::get().getColorLightBlue());

    textureUp.loadFromFile(PATH_IMAGE_ARROW_UP);
    spriteUp.setTexture(textureUp, true);

    textureDown.loadFromFile(PATH_IMAGE_ARROW_DOWN);
    spriteDown.setTexture(textureDown, true);

    startingItem = 0;
    selectedItem = 0;
}

/**
 *
 */
void ItemsListWidget::setLayout(
    float widgetHorizontalPosition,
    float widgetVerticalPosition,
    float widgetWidth,
    unsigned short verticalTextContainers
)
{
    width = widgetWidth;
    verticalContainers = verticalTextContainers;

    setPosition(
        widgetHorizontalPosition,
        widgetVerticalPosition
    );

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

    selector.setPosition(
        horizontalPosition + ITEMS_LIST_BORDER_SIZE,
        verticalPosition
    );

    arrowUpSelector.setPosition(
        horizontalPosition + width - ITEMS_LIST_ARROW_DIM,
        verticalPosition
    );

    arrowDownSelector.setPosition(
        horizontalPosition + width - ITEMS_LIST_ARROW_DIM,
        verticalPosition + ITEMS_LIST_ITEM_HEIGHT * verticalContainers - ITEMS_LIST_ARROW_DIM
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

    arrowUpSelector.setSize(sf::Vector2f(
                                ITEMS_LIST_ARROW_DIM,
                                ITEMS_LIST_ARROW_DIM
                            ));

    arrowDownSelector.setSize(sf::Vector2f(
                                  ITEMS_LIST_ARROW_DIM,
                                  ITEMS_LIST_ARROW_DIM
                              ));

    selector.setSize(sf::Vector2f(
                         width - ITEMS_LIST_ARROW_DIM,
                         ITEMS_LIST_ITEM_HEIGHT
                     ));
}

/**
 *
 */
void ItemsListWidget::addTextItem(std::string textItem)
{
    stringsList.push_back(textItem);
}

/**
 *
 */
void ItemsListWidget::display(utils::Context& context)
{
    context.getSfmlWindow().draw(boxTop);
    context.getSfmlWindow().draw(boxBottom);
    context.getSfmlWindow().draw(boxLeft);
    context.getSfmlWindow().draw(boxRight);

    if (isMouseHover())
    {
        highlightCurrentItem(context);
    }

    highlightArrows(context);

    context.getSfmlWindow().draw(spriteUp);
    context.getSfmlWindow().draw(spriteDown);

    for(std::vector<std::string>::iterator textItem = stringsList.begin();
            textItem != stringsList.end(); ++textItem)
    {
        unsigned long index =
            static_cast<unsigned long>(std::distance(stringsList.begin(), textItem));

        /* do not display items that are out of the box */
        if (
            index < startingItem ||
            index >= verticalContainers + startingItem
        )
        {
            continue;
        }

        float itemsCommonVerticalPosition =
            verticalPosition +
            (static_cast<float>(index)) *
            ITEMS_LIST_ITEM_HEIGHT -
            startingItem *
            ITEMS_LIST_ITEM_HEIGHT;

        sf::Text item;

        item.setFont(memoris::fonts::FontsManager::get().getTextFont());
        item.setCharacterSize(ITEMS_LIST_ITEM_HEIGHT);
        item.setColor(memoris::colors::ColorsManager::get().getColorWhite());
        item.setString(*textItem);
        item.setPosition(
            horizontalPosition,
            itemsCommonVerticalPosition - ITEMS_LIST_TEXT_OFFSET
        );

        context.getSfmlWindow().draw(item);
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
std::vector<std::string> ItemsListWidget::getStringsList()
{
    return stringsList;
}

/**
 *
 */
bool ItemsListWidget::isMouseHover() const
{
    if (
        sf::Mouse::getPosition().x > horizontalPosition &&
        sf::Mouse::getPosition().x <
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM &&
        sf::Mouse::getPosition().y > verticalPosition &&
        sf::Mouse::getPosition().y <
        verticalPosition +
        ITEMS_LIST_ITEM_HEIGHT *
        verticalContainers
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void ItemsListWidget::highlightCurrentItem(utils::Context& context)
{
    unsigned short cursorInternalHorizontalPosition =
        static_cast<unsigned short>(sf::Mouse::getPosition().y - verticalPosition);

    unsigned short selectedItemId =
        cursorInternalHorizontalPosition / ITEMS_LIST_ITEM_HEIGHT;

    /* do not highlight items if no item */
    if (
        selectedItemId > stringsList.size() - 1 ||
        !stringsList.size()
    )
    {
        return;
    }

    selector.setPosition(
        horizontalPosition + ITEMS_LIST_BORDER_SIZE,
        verticalPosition + selectedItemId *
        ITEMS_LIST_ITEM_HEIGHT + ITEMS_LIST_BORDER_SIZE
    );

    context.getSfmlWindow().draw(selector);

    /* TODO: use the same variable, should be refactored,
       use a second separated variable to avoid all casting problems */
    selectedItem = selectedItemId;
}

/**
 *
 */
void ItemsListWidget::highlightArrows(utils::Context& context)
{
    if (isMouseHoverArrowUp())
    {
        context.getSfmlWindow().draw(arrowUpSelector);
    }
    else if (isMouseHoverArrowDown())
    {
        context.getSfmlWindow().draw(arrowDownSelector);
    }
}

/**
 *
 */
bool ItemsListWidget::isMouseHoverArrowDown() const
{
    if (
        sf::Mouse::getPosition().x >
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM &&
        sf::Mouse::getPosition().x <
        horizontalPosition +
        width &&
        sf::Mouse::getPosition().y >
        verticalPosition +
        verticalContainers *
        ITEMS_LIST_ITEM_HEIGHT -
        ITEMS_LIST_ARROW_DIM &&
        sf::Mouse::getPosition().y <
        verticalPosition +
        verticalContainers *
        ITEMS_LIST_ITEM_HEIGHT
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
bool ItemsListWidget::isMouseHoverArrowUp() const
{
    if (
        sf::Mouse::getPosition().x >
        horizontalPosition +
        width -
        ITEMS_LIST_ARROW_DIM &&
        sf::Mouse::getPosition().x <
        horizontalPosition +
        width &&
        sf::Mouse::getPosition().y > verticalPosition &&
        sf::Mouse::getPosition().y <
        verticalPosition +
        ITEMS_LIST_ARROW_DIM
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void ItemsListWidget::scroll()
{
    if (
        isMouseHoverArrowDown() &&
        stringsList.size() - startingItem != verticalContainers &&
        stringsList.size() > verticalContainers
    )
    {
        startingItem++;
    }
    else if (isMouseHoverArrowUp() && startingItem)
    {
        startingItem--;
    }
}

/**
 *
 */
std::string ItemsListWidget::getSelectedItemValue()
{
    return stringsList[selectedItem];
}
