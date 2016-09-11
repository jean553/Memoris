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
 * @file RotateFloorAnimation.hpp
 * @brief animation that rotates the floor on the left
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ROTATEFLOORANIMATION_H_
#define MEMORIS_ROTATEFLOORANIMATION_H_

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class RotateFloorAnimation : public LevelAnimation
{

public:

    /**
     * @brief constructor, called by the animations factory
     *
     * @param movementDirection indicates if the movement is clockwise or not;
     * usually contains 1 or -1
     * @param context shared pointer reference to the current context
     */
    RotateFloorAnimation(
        aliases::ConstContextSharedPtrRef context,
        const short& movementDirection
    );

    /**
     * @brief public function called from the game controller; this function
     * handles the time management (interval) of the animation and call the
     * animation step incrementation method at each interval. This function is
     * public because this is the only interface accessible from the game
     * controller
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void renderAnimation(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;

private:

    /**
     * @brief protected virtual method that contains the animation flow with
     * the different animation steps; it defines what does the animation
     * according to the current animationSteps value; this method is protected
     * because called by the renderAnimation function
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void playNextAnimationStep(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;

    /**
     * @brief rotate the cells of the floor on the left
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void rotateCells(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /* the rotation direction, negative or positive */
    short direction {1};
};

}
}

#endif
