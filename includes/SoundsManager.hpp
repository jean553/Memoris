/**
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
     * @brief constructor
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    SoundsManager();

    SoundsManager(const SoundsManager&) = delete;

    SoundsManager& operator=(const SoundsManager&) = delete;

    /**
     * @brief default destructor
     */
    ~SoundsManager();

    /**
     * @brief plays the move selector sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playMoveSelectorSound() const &;

    /**
     * @brief plays the screen transition sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playScreenTransitionSound() const &;

    /**
     * @brief plays the hide level sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playHideLevelSound() const &;

    /**
     * @brief plays the found star cell sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playFoundStarSound() const &;

    /**
     * @brief plays the found life/time sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playFoundLifeOrTimeSound() const &;

    /**
     * @brief plays the found dead or less time sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playFoundDeadOrLessTimeSound() const &;

    /**
     * @brief plays the collision sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playCollisionSound() const &;

    /**
     * @brief plays the floor switch animation sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playFloorSwitchSound() const &;

    /**
     * @brief plays the time over sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playTimeOverSound() const &;

    /**
     * @brief plays the mirror animation sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playMirrorAnimationSound() const &;

    /**
     * @brief plays the win level sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playWinLevelSound() const &;

    /**
     * @brief plays the diagonal animation sound
     *
     * not noexcept because it uses sf::Sound::play()
     */
    void playFloorMovementAnimationSound() const &;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
