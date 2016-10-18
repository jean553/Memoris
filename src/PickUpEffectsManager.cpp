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
 * @file PickUpEffectsManager.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PickUpEffectsManager.hpp"

#include "PickUpEffect.hpp"

#include <vector>
#include <algorithm>
#include <iterator>

namespace memoris
{
namespace utils
{

class PickUpEffectsManager::Impl
{

public:

    /* we store pointer to copy items into the container faster when creating
       an effect (instead of a whole object copy); because they are smart
       pointers, they are destroyed when the container is deleted */
    std::vector<std::unique_ptr<PickUpEffect>> effects;
};

/**
 *
 */
PickUpEffectsManager::PickUpEffectsManager() noexcept :
impl(std::make_unique<Impl>())
{
}

/**
 *
 */
PickUpEffectsManager::~PickUpEffectsManager() noexcept = default;

/**
 *
 */
void PickUpEffectsManager::addPickUpEffect(
    const sf::Texture& texture,
    const float& hPosition,
    const float& vPosition
) &
{
    impl->effects.push_back(
        std::make_unique<PickUpEffect>(
            texture,
            hPosition,
            vPosition
        )
    );
}

/**
 *
 */
void PickUpEffectsManager::renderAllEffects(const utils::Context& context) &
{
    for (auto& effect : impl->effects)
        // auto -> std::unique_ptr<PickUpEffect>&
    {
        if (effect->isFinished())
        {
            continue;
        }

        effect->render(context);
    }
}

}
}
