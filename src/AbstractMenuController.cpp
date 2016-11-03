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

#include "Context.hpp"
#include "SoundsManager.hpp"
#include "MenuItem.hpp"

#include <vector>
#include <cstdlib>

using UniquePtrMenuItemContainer =
    std::vector<std::unique_ptr<memoris::items::MenuItem>>;

namespace memoris
{
namespace controllers
{

class AbstractMenuController::Impl
{

public:

    unsigned short selectorPosition {0};

    UniquePtrMenuItemContainer items;
};

/**
 *
 */
AbstractMenuController::AbstractMenuController(const utils::Context& context) :
    Controller(context),
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
AbstractMenuController::~AbstractMenuController() noexcept = default;

/**
 *
 */
void AbstractMenuController::addMenuItem(
    std::unique_ptr<items::MenuItem> item
) &
{
    impl->items.push_back(std::move(item));
}

/**
 *
 */
void AbstractMenuController::renderAllMenuItems(
    const utils::Context& context
) const &
{
    for (auto& item : impl->items) // item -> std::unique_ptr<items::MenuItem>&
    {
        item->render(context);
    }
}

/**
 *
 */
const unsigned short& AbstractMenuController::getSelectorPosition() const &
noexcept
{
    return impl->selectorPosition;
}

/**
 *
 */
void AbstractMenuController::moveUp(
    const utils::Context& context
) &
{
    if (impl->selectorPosition == 0)
    {
        return;
    }

    impl->selectorPosition--;

    updateMenuSelection(context);
}

/**
 *
 */
void AbstractMenuController::moveDown(
    const utils::Context& context
) &
{
    /* static cast because std::vector::size() returns a size_t and
       selectorPosition is an unsigned short */
    if (
        impl->selectorPosition ==
        static_cast<unsigned short>(impl->items.size() - 1)
    )
    {
        return;
    }

    impl->selectorPosition++;

    updateMenuSelection(context);
}

/**
 *
 */
void AbstractMenuController::updateMenuSelection(
    const utils::Context& context
) &
{
    /* browse all the menu items; use an iterator in order to calculate the
       current index during each iteration */
    for(
        UniquePtrMenuItemContainer::iterator iterator =
        impl->items.begin();
        iterator != impl->items.end();
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
                        impl->items.begin(),
                        iterator
                    )
                )
            ) == impl->selectorPosition
        )
        {
            (**iterator).select(context);
            continue;
        }

        (**iterator).unselect(context);
    }

    context.getSoundsManager().playMoveSelectorSound();
}

}
}
