/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief animation of a cell when the player moves to it
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
     * @brief constructor
     *
     * @param texture the texture to animate
     * @param positions horizontal and vertical positions
     *
     * @throw std::bad_alloc cannot initialize the implementation;
     * this exception is never caught and the program stops
     */
    PickUpEffect(
        const sf::Texture& texture,
        const std::pair<float, float>& positions
    );

    PickUpEffect(const PickUpEffect&) = delete;

    PickUpEffect& operator=(const PickUpEffect&) = delete;

    /**
     * @brief default destructor
     */
    ~PickUpEffect();

    /**
     * @brief renders the current pick up effect
     *
     * @param context the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void render(const utils::Context& context) const &;

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
