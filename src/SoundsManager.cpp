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
 * @file SoundsManager.cpp
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 *
 * TODO: #1006 add sounds files; I kept the sounds manager because the
 * expected sounds are still the sames
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
SoundsManager::SoundsManager() : impl(std::make_unique<Impl>())
{
}

/**
 *
 */
SoundsManager::~SoundsManager() = default;

/**
 *
 */
void SoundsManager::playMoveSelectorSound() const &
{
    impl->moveSelectorSound.play();
}

/**
 *
 */
void SoundsManager::playScreenTransitionSound() const &
{
    impl->screenTransitionSound.play();
}

/**
 *
 */
void SoundsManager::playHideLevelSound() const &
{
    impl->hideLevelSound.play();
}

/**
 *
 */
void SoundsManager::playFoundStarSound() const &
{
    impl->foundStarSound.play();
}

/**
 *
 */
void SoundsManager::playFoundLifeOrTimeSound() const &
{
    impl->foundLifeOrTimeSound.play();
}

/**
 *
 */
void SoundsManager::playFoundDeadOrLessTimeSound() const &
{
    impl->foundDeadOrLessTimeSound.play();
}

/**
 *
 */
void SoundsManager::playCollisionSound() const &
{
    impl->collisionSound.play();
}

/**
 *
 */
void SoundsManager::playFloorSwitchSound() const &
{
    impl->floorSwitchSound.play();
}

/**
 *
 */
void SoundsManager::playTimeOverSound() const &
{
    impl->timeOverSound.play();
}

/**
 *
 */
void SoundsManager::playMirrorAnimationSound() const &
{
    impl->mirrorAnimationSound.play();
}

/**
 *
 */
void SoundsManager::playWinLevelSound() const &
{
    impl->winLevelSound.play();
}

/**
 *
 */
void SoundsManager::playFloorMovementAnimationSound() const &
{
    impl->floorMovementAnimationSound.play();
}

}
}
