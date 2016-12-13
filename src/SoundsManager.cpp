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
 * @file SoundsManager.cpp
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SoundsManager.hpp"

#include "Sound.hpp"

namespace memoris
{
namespace managers
{

class SoundsManager::Impl
{

public:

    sounds::Sound moveSelectorSound {"001"};
    sounds::Sound screenTransitionSound {"002"};
    sounds::Sound hideLevelSound {"003"};
    sounds::Sound foundStarSound {"004"};
    sounds::Sound foundLifeOrTimeSound {"005"};
    sounds::Sound foundDeadOrLessTimeSound {"006"};
    sounds::Sound collisionSound {"007"};
    sounds::Sound floorSwitchSound {"008"};
    sounds::Sound timeOverSound {"009"};
    sounds::Sound mirrorAnimationSound {"010"};
    sounds::Sound winLevelSound {"011"};
    sounds::Sound floorMovementAnimationSound {"012"};
};

/**
 *
 */
SoundsManager::SoundsManager() noexcept :
impl(std::make_unique<Impl>())
{
}

/**
 *
 */
SoundsManager::~SoundsManager() noexcept = default;

/**
 *
 */
void SoundsManager::playMoveSelectorSound() const & noexcept
{
    impl->moveSelectorSound.play();
}

/**
 *
 */
void SoundsManager::playScreenTransitionSound() const & noexcept
{
    impl->screenTransitionSound.play();
}

/**
 *
 */
void SoundsManager::playHideLevelSound() const & noexcept
{
    impl->hideLevelSound.play();
}

/**
 *
 */
void SoundsManager::playFoundStarSound() const & noexcept
{
    impl->foundStarSound.play();
}

/**
 *
 */
void SoundsManager::playFoundLifeOrTimeSound() const & noexcept
{
    impl->foundLifeOrTimeSound.play();
}

/**
 *
 */
void SoundsManager::playFoundDeadOrLessTimeSound() const & noexcept
{
    impl->foundDeadOrLessTimeSound.play();
}

/**
 *
 */
void SoundsManager::playCollisionSound() const & noexcept
{
    impl->collisionSound.play();
}

/**
 *
 */
void SoundsManager::playFloorSwitchSound() const & noexcept
{
    impl->floorSwitchSound.play();
}

/**
 *
 */
void SoundsManager::playTimeOverSound() const & noexcept
{
    impl->timeOverSound.play();
}

/**
 *
 */
void SoundsManager::playMirrorAnimationSound() const & noexcept
{
    impl->mirrorAnimationSound.play();
}

/**
 *
 */
void SoundsManager::playWinLevelSound() const & noexcept
{
    impl->winLevelSound.play();
}

/**
 *
 */
void SoundsManager::playFloorMovementAnimationSound() const &
noexcept
{
    impl->floorMovementAnimationSound.play();
}

}
}
