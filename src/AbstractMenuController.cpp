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
 * @file AbstractMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractMenuController.hpp"

#include "MenuItem.hpp"

#include <vector>
#include <cstdlib>

namespace memoris
{
namespace controllers
{

class AbstractMenuController::Impl
{

public:

    unsigned short selectorPosition {0};

    std::vector<std::unique_ptr<const items::MenuItem>> items;
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
AbstractMenuController::~AbstractMenuController() = default;

/**
 *
 */
void AbstractMenuController::addMenuItem(
    std::unique_ptr<items::MenuItem> item
) const & noexcept
{
    impl->items.push_back(std::move(item));
}

/**
 *
 */
void AbstractMenuController::renderAllMenuItems() const &
{
    for (auto& item : impl->items)
    {
        item->render(getContext());
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
const unsigned short AbstractMenuController::getLastItemIndex() const &
{
    return static_cast<unsigned short>(impl->items.size()) - 1;
}

/**
 *
 */
void AbstractMenuController::moveUp() const & noexcept
{
    impl->selectorPosition--;
}

/**
 *
 */
void AbstractMenuController::moveDown() const & noexcept
{
    impl->selectorPosition++;
}

/**
 *
 */
void AbstractMenuController::updateMenuSelection() const &
{
    const auto& items = impl->items;
    const auto& itemsStart = items.cbegin();

    for(
        auto iterator = itemsStart;
        iterator != items.cend();
        ++iterator
    )
    {
        const auto& context = getContext();
        const auto& currentItem = **iterator;

        /* std::distance may be negative,
           so we use std::abs */
        if (
            static_cast<unsigned short>(
                std::abs(
                    std::distance(
                        itemsStart,
                        iterator
                    )
                )
            ) == impl->selectorPosition
        )
        {
            currentItem.select(context);
            continue;
        }

        currentItem.unselect(context);
    }
}

}
}
