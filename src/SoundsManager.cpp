/**
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
 * @file SoundsManager.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SoundsManager.hpp"

namespace memoris
{
namespace sounds
{

/**
 *
 */
SoundsManager& SoundsManager::get()
{
    /* create only one time a sounds manager instance */
    static SoundsManager singleton;

    /* always return the same sounds manager instance */
    return singleton;
}

/**
 *
 */
SoundsManager::SoundsManager() :
    moveSelectorSound("res/sounds/001.wav"),
    screenTransitionSound("res/sounds/002.wav"),
    hideLevelSound("res/sounds/003.wav"),
    foundStarSound("res/sounds/004.wav")
{
    /* try to load each sound from their files, one by one; the game run
       even if some/all sounds cannot be loaded; if loading succeeds, we
       reset the null pointer with a pointed SFML sound object value,
       the sound object is generated at this moment, only if the file is
       opened successfully */

    /* NOTE: the constructor body is empty, but this is required to
       add it when using initialization list */
}

/**
 *
 */
const Sound& SoundsManager::getMoveSelectorSound()
{
    return moveSelectorSound;
}

/**
 *
 */
const Sound& SoundsManager::getScreenTransitionSound()
{
    return screenTransitionSound;
}

/**
 *
 */
const Sound& SoundsManager::getHideLevelSound()
{
    return hideLevelSound;
}

/**
 *
 */
const Sound& SoundsManager::getFoundStarSound()
{
    return foundStarSound;
}

}
}
