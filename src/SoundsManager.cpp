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

const std::string SoundsManager::MOVE_SELECTOR_SOUND_PATH =
    "res/sounds/001.wav";
const std::string SoundsManager::SCREEN_TRANSITION_SOUND_PATH =
    "res/sounds/002.wav";
const std::string SoundsManager::HIDE_LEVEL_SOUND_PATH = "res/sounds/003.wav";

/**
 *
 */
SoundsManager::SoundsManager()
{
    /* by default, the pointer is NULL; this is used for error management */
    moveSelectorSound = NULL;
    screenTransitionSound = NULL;
    hideLevelSound = NULL;

    /* try to load each sound from their files, one by one; the game run
       even if some/all sounds cannot be loaded; if loading succeeds, we
       reset the NULL pointer with a pointed SFML sound object value,
       the sound object is generated at this moment, only if the file is
       opened successfully */

    if(
        moveSelectorSoundBuffer.loadFromFile(
            MOVE_SELECTOR_SOUND_PATH
        )
    )
    {
        moveSelectorSound.reset(new sf::Sound());
        moveSelectorSound->setBuffer(moveSelectorSoundBuffer);
    }

    if(
        screenTransitionSoundBuffer.loadFromFile(
            SCREEN_TRANSITION_SOUND_PATH
        )
    )
    {
        screenTransitionSound.reset(new sf::Sound());
        screenTransitionSound->setBuffer(screenTransitionSoundBuffer);
    }

    if(
        hideLevelSoundBuffer.loadFromFile(
            HIDE_LEVEL_SOUND_PATH
        )
    )
    {
        hideLevelSound.reset(new sf::Sound());
        hideLevelSound->setBuffer(hideLevelSoundBuffer);
    }
}

/**
 *
 */
void SoundsManager::playMoveSelectorSound()
{
    if (moveSelectorSound != NULL)
    {
        moveSelectorSound->play();
    }
}

/**
 *
 */
void SoundsManager::playScreenTransitionSound()
{
    if (screenTransitionSound != NULL)
    {
        screenTransitionSound->play();
    }
}

/**
 *
 */
void SoundsManager::playHideLevelSound()
{
    if (hideLevelSound != NULL)
    {
        hideLevelSound->play();
    }
}

}
}
