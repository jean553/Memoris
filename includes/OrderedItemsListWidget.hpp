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
 * Ordered items list widget, list which displays many
 * textual items, one can be selected, they can be
 * ordered using arrows on each item
 *
 * @file OrderedItemsListWidget.hpp
 * @brief list of textual items, one can be selected
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_ORDERED_ITEMS_LIST_WIDGET
#define DEF_ORDERED_ITEMS_LIST_WIDGET

#include "ItemsListWidget.hpp"

namespace widgets
{
class OrderedItemsListWidget : public ItemsListWidget
{

    static const std::string PATH_IMAGE_EDIT;
    static const std::string PATH_IMAGE_DELETE;

public:

    OrderedItemsListWidget();

    /**
     * @brief display the items list widget
     *
     * @param context  current context pointer
     */
    void display(utils::Context& context);
};
}

#endif
