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
 * @file LevelAnimation.hpp
 * @brief interface for all the level animations
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELANIMATION_H_
#define MEMORIS_LEVELANIMATION_H_

#include "Level.hpp"

namespace memoris
{
namespace animations
{

class LevelAnimation
{

public:

    /**
     * @brief pure virtual method for level animation rendering; this method
     * is called by the game controller
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    virtual void render(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) = 0;

    /**
     * @brief getter of the 'finished' boolean, true is the animation is
     * finished
     *
     * @return const bool&
     */
    const bool& isFinished() const;

protected:

    /* used by the animation creator (game controller) to know if the animation
       is terminated; in fact, the animation object sets it to false when all
       the animation has been rendered; this is use to know when the animation
       object can be deleted */
    bool finished {false};

    /* we use a SFML unsigned integer to stop the last animation time; we use
       a SFML type to be complient with the SFML clock; when the animation is
       created, this value is equal to 0 */
    sf::Uint32 lastAnimationUpdateTime {0};

    /* an animation is divided into steps; these steps value is incremented
       every x seconds/milliseconds/minutes and is used to manage the
       animation rendering; every animation have it; */
    unsigned short animationSteps {0};
};

}
}

#endif
