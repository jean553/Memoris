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
 * @file QuarterRotationAnimation.hpp
 * @brief rotate the quarters
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_QUARTERROTATIONANIMATION_H_
#define MEMORIS_QUARTERROTATIONANIMATION_H_

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class QuarterRotationAnimation : public LevelAnimation
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the floor index of the animation
     */
    QuarterRotationAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) noexcept;

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~QuarterRotationAnimation() noexcept;

    /**
     * @brief renders the animation
     *
     * @param floor constant unsigned integer to the level floor to render
     */
    void renderAnimation(const unsigned short& floor) & override;

private:

    static constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};

    static constexpr unsigned short ANIMATION_STEPS {40};
    static constexpr unsigned short HALF_CELLS_PER_LINE {8};

    /**
     * @brief move all the quarters at the same time in the expected direction
     *
     * @param level constant reference on shared pointer to the concerned level
     * @param floor constant unsigned integer to the level floor to render
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void moveAllQuarters(
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) const &;

    /**
     * @brief invert the cells after the animation; update the position of all
     * the floor cells at the same time
     *
     * @param level constant reference on shared pointer to the concerned level
     * @param floor constant unsigned integer to the level floor to render
     *
     * not const because it modifies the current player cell
     */
    void updateCells(
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & noexcept;

    /**
     * @brief apply the given modification on the given cell index
     *
     * @param level constant reference on shared pointer to the concerned level
     *
     * not const because it modifies the current player cell
     */
    void invertCells(
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& index,
        const unsigned short& modification,
        const unsigned short& floor
    ) & noexcept;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
