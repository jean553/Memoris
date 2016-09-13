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
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SoundsManager.hpp"

namespace memoris
{
namespace managers
{

/**
 *
 */
SoundsManager::SoundsManager() noexcept :
    moveSelectorSound("001"),
    screenTransitionSound("002"),
    hideLevelSound("003"),
    foundStarSound("004"),
    foundLifeOrTimeSound("005"),
    foundDeadOrLessTimeSound("006"),
    collisionSound("007"),
    floorSwitchSound("008"),
    timeOverSound("009"),
    mirrorAnimationSound("010"),
    winLevelSound("011"),
    floorMovementAnimationSound("012")
{
    /* empty constructor as we try to initialize the sounds directly inside
       the initialization list */
}

/**
 *
 */
const sounds::Sound& SoundsManager::getMoveSelectorSound() const & noexcept
{
    return moveSelectorSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getScreenTransitionSound() const & noexcept
{
    return screenTransitionSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getHideLevelSound() const & noexcept
{
    return hideLevelSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getFoundStarSound() const & noexcept
{
    return foundStarSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getFoundLifeOrTimeSound() const & noexcept
{
    return foundLifeOrTimeSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getFoundDeadOrLessTimeSound() const & noexcept
{
    return foundDeadOrLessTimeSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getCollisionSound() const & noexcept
{
    return collisionSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getFloorSwitchSound() const & noexcept
{
    return floorSwitchSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getTimeOverSound() const & noexcept
{
    return timeOverSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getMirrorAnimationSound() const & noexcept
{
    return mirrorAnimationSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getWinLevelSound() const & noexcept
{
    return winLevelSound;
}

/**
 *
 */
const sounds::Sound& SoundsManager::getFloorMovementAnimationSound() const &
noexcept
{
    return floorMovementAnimationSound;
}

}
}
