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

/* play this sound when the menu selector of any menu is moved up or down */
const std::string SoundsManager::MOVE_SELECTOR_SOUND_PATH =
    "res/sounds/001.wav";


/* play this sound every time the current screen is switched */
const std::string SoundsManager::SCREEN_TRANSITION_SOUND_PATH =
    "res/sounds/002.wav";

/* play this sound when the game level is hidden */
const std::string SoundsManager::HIDE_LEVEL_SOUND_PATH = "res/sounds/003.wav";

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
    moveSelectorSound(MOVE_SELECTOR_SOUND_PATH),
    screenTransitionSound(SCREEN_TRANSITION_SOUND_PATH),
    hideLevelSound(HIDE_LEVEL_SOUND_PATH)
{
    /* try to load each sound from their files, one by one; the game run
       even if some/all sounds cannot be loaded; if loading succeeds, we
       reset the NULL pointer with a pointed SFML sound object value,
       the sound object is generated at this moment, only if the file is
       opened successfully */

    /* NOTE: the constructor body is empty, but this is required to
       add it when using initialization list */
}

/**
 *
 */
Sound& SoundsManager::getMoveSelectorSound()
{
    return moveSelectorSound;
}

/**
 *
 */
Sound& SoundsManager::getScreenTransitionSound()
{
    return screenTransitionSound;
}

/**
 *
 */
Sound& SoundsManager::getHideLevelSound()
{
    return hideLevelSound;
}

}
}
