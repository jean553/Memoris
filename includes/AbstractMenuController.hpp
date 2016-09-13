/*
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
 * @file AbstractMenuController.hpp
 * @brief abstract class that manages menus selectors movement and animation
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTMENUCONTROLLER_H_
#define MEMORIS_ABSTRACTMENUCONTROLLER_H_

#include "Controller.hpp"

#include "MenuItem.hpp"

#include <vector>

namespace memoris
{
namespace controllers
{

class AbstractMenuController : public Controller
{

protected:

    /**
     * @brief constructor, does nothing; only used to pass arguments to the
     * parent constructor of Controller; protected because only called during
     * children objects creation
     *
     * @param context reference to the current context
     */
    AbstractMenuController(utils::Context& context);

    /**
     * @brief insert one menu item pointer inside the menu items list
     *
     * @param unique pointer to the item to add; this is required to use
     * pointers to avoid to create two objects; this is better to have
     * two pointers pointing on the same object; we also use pointers
     * because references cannot be added into containers
     */
    void addMenuItem(std::unique_ptr<items::MenuItem> item);

    /**
     * @brief display all the menu items
     *
     * @param context shared pointer to the context to use
     */
    void renderAllMenuItems(
        utils::Context& context
    );

    /**
     * @brief getter of the selector position
     *
     * @return unsigned short
     */
    unsigned short getSelectorPosition() const;

    /**
     * @brief move up the selector, only if the selected item is not the first
     * one
     *
     * @param context reference to the current context to use
     */
    void moveUp(utils::Context& context);

    /**
     * @brief move down the selector, only if the selected item is not the last
     * one
     *
     * @param context reference to the current context to use
     */
    void moveDown(utils::Context& context);

    /**
     * @brief pure virtual method with empty definition; this method is used
     * to make the class abstract; this method has to be overwritted by all
     * children classes to define what happens when menu items are selected
     * by definition; this method can also be used in any other menu purpose
     */
    virtual void selectMenuItem() = 0;

private:

    /**
     * @brief returns the highest item index from the menu items list;
     * returns also 0 if the list is empty or if the list only contains
     * one item
     *
     * @return unsigned short
     */
    unsigned short getLastMenuItemIndex() const;

    /**
     * @brief update the colors of all the menu items; the current
     * selected item is colored by the red color
     *
     * @param context reference to the current context
     */
    void updateMenuSelection(utils::Context& context);

    /* the current position of the selector ( the current pointed item ); the
       default value is 0 */
    unsigned short selectorPosition {0};

    /* the container of menu items; we use a vector because we have to handle
       order, keys management ( indexes ), we have to be able to find by index,
       we insert at the end and the size won't change at all after creation */
    std::vector<std::unique_ptr<items::MenuItem>> items;
};

}
}

#endif
