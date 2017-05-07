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
 * @brief animation that is played when the player finds a stairs cell
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_STAIRSABSTRACT_H_
#define MEMORIS_STAIRSABSTRACT_H_

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class StairsAnimation : public LevelAnimation
{

public:

    /**
     * @brief constructor, we define it because we have to save the time
     * just before the animation starts; we use this saved value later to
     * know when the waiting time of the animation is terminated
     *
     * @param context reference to the current context to use
     * @param level the level of the animation
     * @param dir indicates in which direction is made the transition
     * (up/down), only equals to -1 or 1;
     */
    StairsAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const short& dir
    );

    ~StairsAnimation();

    /**
     * @brief render the animation
     *
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void renderAnimation(
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & override;

    /**
     * @brief execute action by jumping to the next animation step
     *
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void playNextAnimationStep(
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) &;

private:

    /* during the animation, the transparency of the cells is modified
       progressively; the amount of transparency value update at each iteration
       is always the same and equal to 17.f, so we just refactor it in the
       code segment */
    static constexpr float TRANSPARENCY_UPDATE_AMOUNT {17.f};

    /* the direction of the movement; can be set to 1 or -1; not initialized
       here because this variable can be specified in the constructor of the
       animation */
    short direction;

    /* the update to apply on the current floor index according to the
       animation progression; first the current floor is displayed, and then
       we switch to next/previous one */
    short transformation {0};

    /* the transparency value to apply on all the cells of the same floor */
    float cellsTransparency {255.f};
};

}
}

#endif
