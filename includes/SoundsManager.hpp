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
namespace managers
{

class SoundsManager : public utils::NotCopiable
{

public:

    /**
     * @brief constructor, loads each sound file one by one, silently
     * fails if the loading process fail
     */
    SoundsManager() noexcept;

    /* all the sounds getters return constant references to improve
       performances and prevent objects modification; each getter is
       constant as it does not modify the current object instance; no one
       of the getter throw an exception */

    /**
     * @brief getter of the move selector sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getMoveSelectorSound() const noexcept;

    /**
     * @brief getter of the screen transition sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getScreenTransitionSound() const noexcept;

    /**
     * @brief getter of the hide level sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getHideLevelSound() const noexcept;

    /**
     * @brief getter of the found star cell sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getFoundStarSound() const noexcept;

    /**
     * @brief getter of the found life/time sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getFoundLifeOrTimeSound() const noexcept;

    /**
     * @brief getter of the found dead or less time sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getFoundDeadOrLessTimeSound() const noexcept;

    /**
     * @brief getter of the collision sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getCollisionSound() const noexcept;

    /**
     * @brief getter of the floor switch animation sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getFloorSwitchSound() const noexcept;

    /**
     * @brief getter of the time over sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getTimeOverSound() const noexcept;

    /**
     * @brief getter of the mirror animation sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getMirrorAnimationSound() const noexcept;

    /**
     * @brief getter of the win level sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getWinLevelSound() const noexcept;

    /**
     * @brief getter of the diagonal animation sound
     *
     * @return const sounds::Sound&
     */
    const sounds::Sound& getFloorMovementAnimationSound() const noexcept;

private:

    sounds::Sound moveSelectorSound;
    sounds::Sound screenTransitionSound;
    sounds::Sound hideLevelSound;
    sounds::Sound foundStarSound;
    sounds::Sound foundLifeOrTimeSound;
    sounds::Sound foundDeadOrLessTimeSound;
    sounds::Sound collisionSound;
    sounds::Sound floorSwitchSound;
    sounds::Sound timeOverSound;
    sounds::Sound mirrorAnimationSound;
    sounds::Sound winLevelSound;
    sounds::Sound floorMovementAnimationSound;
};

}
}

#endif
