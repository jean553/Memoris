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
 * @file PickUpEffect.hpp
 * @brief animated effect that is rendered during the game when an item is
 * found (star, bonus... etc...)
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PICKUPEFFECT_H_
#define MEMORIS_PICKUPEFFECT_H_

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

class PickUpEffect
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param texture constant reference to the texture to display
     * @param hPosition horizontal position of the animation
     * @param vPosition vertical position of the animation
     *
     * @throw std::bad_alloc the implementation unique pointer cannot be
     * created
     */
    PickUpEffect(
        const sf::Texture& texture,
        const float& hPosition,
        const float& vPosition
    );

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~PickUpEffect() noexcept;

    /**
     * @brief renders the current pick up effect
     *
     * @param context constant reference to the current context to use
     *
     * not 'const' because it modifies the animation properties (position,
     * size and transparency)
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void render(const utils::Context& context) &;

    /**
     * @brief getter of the current effect animation status
     *
     * @return const bool
     */
    const bool isFinished() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
