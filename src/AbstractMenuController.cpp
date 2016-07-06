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
 * @file AbstractMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractMenuController.hpp"

#include "SoundsManager.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
AbstractMenuController::AbstractMenuController(utils::Context& context) :
    Controller()
{
    /* the default pointed item is always the first one when the menu starts */
    selectorPosition = 0;
}

/**
 *
 */
void AbstractMenuController::addMenuItem(std::unique_ptr<items::MenuItem> item)
{
    items.push_back(std::move(item));
}

/**
 *
 */
void AbstractMenuController::renderAllMenuItems(utils::Context& context)
{
    /* use a loop with iterator as the unique pointer is not moved or copied
       during the loop iteration; that's why we use an iterator to point on
       each loop item one by one */
    for(
        std::vector<std::unique_ptr<items::MenuItem>>::iterator item =
            items.begin();
        item != items.end();
        ++item
    )
    {
        /* the item iterator is a pointer to an unique pointer; that's why
           whe use the double dereference to manipulate the object */
        (**item).render(context);
    }
}

/**
 *
 */
unsigned short AbstractMenuController::getLastMenuItemIndex() const
{
    /* convert the size_t to unsigned short for future usage; unsigned
       short has usually a maximum value of 31767; we use this function
       for menu items; we can considere this method as a safe method;
       there is a very small risk of unexpected behavior */
    unsigned short size = static_cast<unsigned short>(items.size());

    /* substract one if the size is more than 0 to get the last item index */
    if (size > 0)
    {
        return size - 1;
    }

    return size;
}

/**
 *
 */
void AbstractMenuController::updateMenuSelection()
{
    /* browse all the menu items; use an iterator in order to calculate the
       current index during each iteration */
    for(
        std::vector<std::unique_ptr<items::MenuItem>>::iterator iterator =
            items.begin();
        iterator != items.end();
        ++iterator
    )
    {
        /* select the item that has the index equals to the selector
           position; wrap the std::distance result with an absolute value
           calculation, in fact std::distance can return a signed value;
           use a cast to force std::distance to always return an unsigned
           short for the comparison */
        if (
            static_cast<unsigned short>(
                std::abs(
                    std::distance(
                        items.begin(),
                        iterator
                    )
                )
            ) == selectorPosition
        )
        {
            /* the item iterator is a pointer to an unique pointer; that's why
               whe use the double dereference to manipulate the object */
            (**iterator).select();

            continue;
        }

        /* unselect all the others items */
        (**iterator).unselect();
    }
}

/**
 *
 */
unsigned short AbstractMenuController::getSelectorPosition() const
{
    return selectorPosition;
}

/**
 *
 */
void AbstractMenuController::moveUp()
{
    /* move the selector only if the current position is not already the
       first one */
    if (selectorPosition == 0)
    {
        return;
    }

    selectorPosition--;

    /* graphically update the selector position */
    updateMenuSelection();

    /* play the move selector sound */
    sounds::SoundsManager::get().getMoveSelectorSound().play();
}

/**
 *
 */
void AbstractMenuController::moveDown()
{
    /* move the selector only if the current selected item is not the last
       one */
    if (selectorPosition == getLastMenuItemIndex())
    {
        return;
    }

    selectorPosition++;

    /* graphically update the selector position */
    updateMenuSelection();

    /* play the move selector sound */
    sounds::SoundsManager::get().getMoveSelectorSound().play();
}

}
}
