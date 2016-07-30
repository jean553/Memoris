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
 * @file SoundsManager.hpp
 * @brief loads and provides the sounds assets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SOUNDSMANAGER_H_
#define MEMORIS_SOUNDSMANAGER_H_

#include "NotCopiable.hpp"
#include "Sound.hpp"

namespace memoris
{
namespace sounds
{

class SoundsManager : public others::NotCopiable
{

public:

    /**
     * @brief make the sounds manager a singleton class;
     * creates a static singleton object, call the private
     * constructor only one time; as the object is static,
     * this unique object is returned everytime and we never
     * create it again
     *
     * @return static SoundsManager&
     */
    static SoundsManager& get();

    /**
     * @brief getter of the move selector sound if loaded
     *
     * @return const Sound&
     */
    const Sound& getMoveSelectorSound();

    /**
     * @brief getter of the screen transition sound if loaded
     *
     * @return const Sound&
     */
    const Sound& getScreenTransitionSound();

    /**
     * @brief getter of the hide level sound if loaded
     *
     * @return const Sound&
     */
    const Sound& getHideLevelSound();

    /**
     * @brief getter of the found star cell sound if loaded
     *
     * @return const Sound&
     */
    const Sound& getFoundStarSound();

    /**
     * @brief getter of the found life/time sound if loaded; the life and the
     * time cell used the same sound
     *
     * @return const Sound&
     */
    const Sound& getFoundLifeOrTimeSound();

    /**
     * @brief getter of the found dead or less time sound if loaded; the dead
     * and the less time cell use the same sound
     *
     * @return const Sound&
     */
    const Sound& getFoundDeadOrLessTimeSound();

    /**
     * @brief getter of the collision sound; this sound is played by the game
     * controller when the player tries to make a forbidden movement and when
     * a wall cell is found
     *
     * @return const Sound&
     */
    const Sound& getCollisionSound();

private:

    /**
     * @brief constructor, loads each sound file one by one, silently
     * fails if the loading process fail; throw an exception and display
     * a message in the console; the program continues even if one or many
     * sounds file(s) cannot be loaded; the sounds manager is private
     * because loaded by the static get() function (singleton pattern)
     */
    SoundsManager();

    /* play this sound when the menu selector
       of any menu is moved up or down */
    Sound moveSelectorSound;

    /* play this sound every time the current screen is switched */
    Sound screenTransitionSound;

    /* play this sound when the game level is hidden */
    Sound hideLevelSound;

    /* play this sound when one star cell is found in the game controller */
    Sound foundStarSound;

    /* play this sound when one life cell or one time cell is found in the game
       controller */
    Sound foundLifeOrTimeSound;

    /* play this sound when one dead cell or one less time cell is found */
    Sound foundDeadOrLessTimeSound;

    /* play this sound when the player tries to make a forbidden move or when
       the player finds a wall */
    Sound collisionSound;
};

}
}

#endif
