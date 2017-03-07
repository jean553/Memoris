/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SOUNDSMANAGER_H_
#define MEMORIS_SOUNDSMANAGER_H_

#include <memory>

namespace memoris
{
namespace managers
{

class SoundsManager
{

public:

    /**
     * @brief constructor, loads each sound file one by one, silently
     * fails if the loading process fail
     */
    SoundsManager() noexcept;

    SoundsManager(const SoundsManager&) = delete;

    SoundsManager& operator=(const SoundsManager&) = delete;

    /**
     *
     */
    ~SoundsManager() noexcept;

    /* all the sounds playters return constant references to improve
       performances and prevent objects modification; each method is
       constant as it does not modify the current object instance; no one
       of the method throw an exception */

    /**
     * @brief plays the move selector sound
     *
     * @return void
     */
    void playMoveSelectorSound() const & noexcept;

    /**
     * @brief plays the screen transition sound
     *
     * @return void
     */
    void playScreenTransitionSound() const & noexcept;

    /**
     * @brief plays the hide level sound
     *
     * @return void
     */
    void playHideLevelSound() const & noexcept;

    /**
     * @brief plays the found star cell sound
     *
     * @return void
     */
    void playFoundStarSound() const & noexcept;

    /**
     * @brief plays the found life/time sound
     *
     * @return void
     */
    void playFoundLifeOrTimeSound() const & noexcept;

    /**
     * @brief plays the found dead or less time sound
     *
     * @return void
     */
    void playFoundDeadOrLessTimeSound() const & noexcept;

    /**
     * @brief plays the collision sound
     *
     * @return void
     */
    void playCollisionSound() const & noexcept;

    /**
     * @brief plays the floor switch animation sound
     *
     * @return void
     */
    void playFloorSwitchSound() const & noexcept;

    /**
     * @brief plays the time over sound
     *
     * @return void
     */
    void playTimeOverSound() const & noexcept;

    /**
     * @brief plays the mirror animation sound
     *
     * @return void
     */
    void playMirrorAnimationSound() const & noexcept;

    /**
     * @brief plays the win level sound
     *
     * @return void
     */
    void playWinLevelSound() const & noexcept;

    /**
     * @brief plays the diagonal animation sound
     *
     * @return void
     */
    void playFloorMovementAnimationSound() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
