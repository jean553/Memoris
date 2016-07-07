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
 * @file OrderedItemsListWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OrderedItemsListWidget.hpp"

#include "Context.hpp"

using namespace widgets;

const std::string OrderedItemsListWidget::PATH_IMAGE_EDIT = "res/images/edit.png";
const std::string OrderedItemsListWidget::PATH_IMAGE_DELETE = "res/images/delete.png";

/**
 *
 */
OrderedItemsListWidget::OrderedItemsListWidget() :
    ItemsListWidget()
{
}

/**
 *
 */
void OrderedItemsListWidget::display()
{
    ItemsListWidget::display();

    for(std::vector<std::string>::iterator textItem = stringsList.begin();
            textItem != stringsList.end(); ++textItem)
    {

        float itemsCommonVerticalPosition = verticalPosition +
                                            (static_cast<float> (std::distance(stringsList.begin(), textItem))) *
                                            ITEMS_LIST_ITEM_HEIGHT;

        sf::Texture textureEdit, textureDelete;
        sf::Sprite spriteEdit, spriteDelete;

        textureEdit.loadFromFile(PATH_IMAGE_EDIT);
        textureDelete.loadFromFile(PATH_IMAGE_DELETE);

        spriteEdit.setTexture(textureEdit, false);
        spriteEdit.setPosition(
            horizontalPosition + width - (width / 4),
            itemsCommonVerticalPosition
        );

        spriteDelete.setTexture(textureDelete, false);
        spriteDelete.setPosition(
            horizontalPosition + width - (width / 4) + 50,
            itemsCommonVerticalPosition
        );

        utils::Context::get().getSfmlWindow().draw(spriteEdit);
        utils::Context::get().getSfmlWindow().draw(spriteDelete);
    }
}
