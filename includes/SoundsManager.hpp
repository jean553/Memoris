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

#include "Sound.hpp"

namespace memoris
{
namespace sounds
{

class SoundsManager
{

public:

    /**
     * @brief constructor, loads each sound file one by one, silently
     * fails if the loading process fail; throw an exception and display
     * a message in the console; the program continues even if one or many
     * sounds file(s) cannot be loaded.
     */
    SoundsManager();

    /**
     * @brief getter of the move selector sound if loaded
     *
     * @return Sound&
     */
    Sound& getMoveSelectorSound();

    /**
     * @brief getter of the screen transition sound if loaded
     *
     * @return Sound&
     */
    Sound& getScreenTransitionSound();

    /**
     * @brief getter of the hide level sound if loaded
     *
     * @return Sound&
     */
    Sound& getHideLevelSound();

private:

    static const std::string MOVE_SELECTOR_SOUND_PATH;
    static const std::string SCREEN_TRANSITION_SOUND_PATH;
    static const std::string HIDE_LEVEL_SOUND_PATH;

    /* play this sound when the menu selector
       of any menu is moved up or down */
    Sound moveSelectorSound;

    /* play this sound every time the current screen is switched */
    Sound screenTransitionSound;

    /* play this sound when the game level is hidden */
    Sound hideLevelSound;
};

}
}

#endif
