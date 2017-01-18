/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

namespace memoris
{

namespace items
{
class MenuItem;
}

namespace controllers
{

class AbstractMenuController : public Controller
{

protected:

    /**
     * @brief constructor, pass the parameters to the parent object and
     * initialize the implementation; protected because only called by a
     * child of this class
     *
     * @param context reference to the current context
     *
     * @throw std::bad_alloc cannot initialize the implementation unique
     * pointer; this exception is never caught and the program stops
     */
    AbstractMenuController(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~AbstractMenuController() noexcept;

    /**
     * @brief insert one menu item pointer inside the menu items list
     *
     * @param item unique pointer to the menu item to insert;
     *
     * NOTE: we move the unique pointer here from the child object to the
     * parent object's container instead of using move sementics directly on
     * the object. In fact, moving a pointer to the object runs faster than
     * moving a MenuItem object directly (measured). This is because the
     * menu item object contains a sf::Text object, and this object has no
     * movement constructor in SFML. So when moving directly the object, the
     * SFML sf::Text object is copied anyway. This copy is not necessary when
     * working at the pointer level.
     *
     * the item parameters is not 'const' because it is an unique pointer
     * which is moved inside the method when calling push_back(std::move(item))
     * this is moved because an unique_ptr cannot be copied anyway
     *
     * not 'const' because it adds data into the items container
     *
     * not 'noexcept' because even if the std::unique_ptr move constructor
     * is not supposed to throw exceptions, push_back can still throw
     * exceptions for other reasons
     */
    void addMenuItem(std::unique_ptr<items::MenuItem> item) &;

    /**
     * @brief display all the menu items
     *
     * not 'noexcept' because this method calls the render() method of the
     * menu item and this last function calls SFML functions that are not
     * noexcept
     */
    void renderAllMenuItems() const &;

    /**
     * @brief getter of the selector position
     *
     * @return const unsigned short&
     */
    const unsigned short& getSelectorPosition() const & noexcept;

    /**
     * @brief move up the selector, only if the selected item is not the first
     * one
     *
     * not 'const' because it modifies the selectorPosition value
     *
     * not 'noexcept' because it calls menu item methods that calls SFML
     * functions and these functions are not noexcept
     */
    void moveUp() &;

    /**
     * @brief move down the selector, only if the selected item is not the last
     * one
     *
     * not 'const' because it modifies the selectorPosition value
     *
     * not 'noexcept' because it calls menu item methods that calls SFML
     * functions and these functions are not noexcept
     */
    void moveDown() &;

    /**
     * @brief pure virtual method used to make this class abstract; this
     * method is defined in the children objects and describes what happens
     * when an item of the menu is selected, according to which item has
     * been selected
     *
     * not 'const' because definition usually set nextControllerId and
     * expectedControllerId attributes
     *
     * NOTE: noexcept because each definition is noexcept guarantee (one
     * method handles exceptions but a try/catch is used there)
     */
    virtual void selectMenuItem() & noexcept = 0;

private:

    /**
     * @brief update the colors of all the menu items; the current
     * selected item is colored by the red color
     *
     * not 'const' because it modifies items inside the items container
     *
     * not 'noexcept' because calls STL and SFML functions that are not
     * noexcept
     */
    void updateMenuSelection() &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
