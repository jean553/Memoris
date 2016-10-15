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
 * @file PickUpEffectsManager.hpp
 * @brief renders and stores all the pick up effects to render during the game
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PICKUPEFFECTSMANAGER_H_
#define MEMORIS_PICKUPEFFECTSMANAGER_H_

#include "NotCopiable.hpp"

#include <memory>

namespace sf
{
class Texture;
}

namespace memoris
{
namespace utils
{

class Context;

class PickUpEffectsManager : public NotCopiable
{

public:

    /**
     * @brief constructor, initializes the implementation
     */
    PickUpEffectsManager() noexcept;

    /**
     * @brief default destructor, empty, only declared here in order to use
     * forwarding declaration
     */
    ~PickUpEffectsManager() noexcept;

    /**
     * @brief creates an unique pointer to a PickUpEffect object and copy this
     * pointer into the effects queue; set the textures and the position of
     * the effect; this method is called by the game controller
     *
     * @param texture constant reference to the texture to use in the effect
     * @param hPosition constant reference to the effect horizontal position
     * @param vPosition constant reference to the effect vertical position
     *
     * not 'const' because it modifies the effects container
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void addPickUpEffect(
        const sf::Texture& texture,
        const float& hPosition,
        const float& vPosition
    ) &;

    /**
     * @brief animates every pick up effect in the effects queue; delete an
     * effect from the queue when this effect is terminated
     *
     * @param context constant reference to the current context to use
     *
     * not 'const' because the effects are modified when they are rendered
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void renderAllEffects(const utils::Context& context) &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
