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
 * @brief handles menu common operations as selector movement and selection
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
     * @brief constructor
     *
     * @param context constant reference to the current context
     *
     * @throw std::bad_alloc cannot initialize the implementation;
     * this exception is never caught and the program stops
     */
    AbstractMenuController(const utils::Context& context);

    /**
     * AbstractMenuController copy constructor and copy operator deletion
     * are already declared into the parent class
     */

    /**
     * @brief default destructor
     */
    ~AbstractMenuController();

    /**
     * @brief defines what happens when an item is selected;
     * usually sets the next controller id value
     */
    virtual void selectMenuItem() const & noexcept = 0;

    /**
     * @brief insert one menu item pointer inside the menu items list
     *
     * @param item unique pointer to the menu item to insert
     */
    void addMenuItem(std::unique_ptr<items::MenuItem> item) const & noexcept;

    /**
     * @brief display all the menu items
     *
     * utils::Context and SFML methods are not noexcept
     */
    void renderAllMenuItems() const &;

    /**
     * @brief returns the current position of the selector
     *
     * @return const unsigned short&
     */
    const unsigned short& getSelectorPosition() const & noexcept;

    /**
     * @brief returns the size of the items list
     *
     * @return const unsigned short
     *
     * we cannot be sure that static_cast won't throw exception
     */
    const unsigned short getLastItemIndex() const &;

    /**
     * @brief move up the selector
     */
    void moveUp() const & noexcept;

    /**
     * @brief move down the selector
     */
    void moveDown() const & noexcept;

    /**
     * @brief updates colors of the menu items according to the selection
     *
     * items::MenuItem::select() and unselect() may throw exceptions
     */
    void updateMenuSelection() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
