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
 * @file StairsAnimation.hpp
 * @brief switch floor animation
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_STAIRSANIMATION_H_
#define MEMORIS_STAIRSANIMATION_H_

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class StairsAnimation : public LevelAnimation
{

public:

    /**
     * @enum StairsAnimation::FloorAnimationDirection
     * @brief the direction of the animation (up or down)
     */
    enum class FloorAnimationDirection {
        Up, /** < move to the next floor */
        Down /** < move to the previous floor */
    };

    /**
     * @brief constructor
     *
     * @param context reference to the current context to use
     * @param level the level of the animation
     * @param floor the floor index of the animation
     * @param direction indicates in what direction the transition is made
     * (up/down), only equals to -1 or 1;
     *
     * NOTE: we use a signed integer for the direction and not an enumeration;
     * it's more convenient as we directly use the integer value
     * in order to update the transparency effect values
     */
    StairsAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor,
        const short& direction
    );

    /**
     * @brief default destructor
     */
    ~StairsAnimation();

    /**
     * @brief renders the animation
     */
    void renderAnimation() & override;

    /**
     * @brief executes action by jumping to the next animation step
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void playNextAnimationStep() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
