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
     * @paran context shared pointer to the current context to use
     */
    StairsAnimation(const std::shared_ptr<utils::Context>& context);

    /**
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void renderAnimation(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void playNextAnimationStep(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );
};

}
}

#endif
