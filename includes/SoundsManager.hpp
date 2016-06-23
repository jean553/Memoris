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

#include <SFML/Audio.hpp>

#include <memory>

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

    /* NOTE: every function that plays a sound, plays it only if the sound
       has been successfully loaded from the file ( unique pointer not null );
       silently fails if the sound has not been loaded correctly */

    /**
     * @brief plays the move selector sound if loaded
     */
    void playMoveSelectorSound();

    /**
     * @brief plays the screen transition sound if loaded
     */
    void playScreenTransitionSound();

    /**
     * @brief plays the hide level sound if loaded
     */
    void playHideLevelSound();

private:

    static const std::string MOVE_SELECTOR_SOUND_PATH;
    static const std::string SCREEN_TRANSITION_SOUND_PATH;
    static const std::string HIDE_LEVEL_SOUND_PATH;

    /* NOTE: we use unique pointers for the SFML sounds; we use
       an unique pointer because it is never copied (only called here), it
       is NULL if the loading process of the sound failed, it is automatically
       destroyed */

    std::unique_ptr<sf::Sound> moveSelectorSound;
    std::unique_ptr<sf::Sound> screenTransitionSound;
    std::unique_ptr<sf::Sound> hideLevelSound;

    /* SFML sound buffers for every sound */
    sf::SoundBuffer moveSelectorSoundBuffer;
    sf::SoundBuffer screenTransitionSoundBuffer;
    sf::SoundBuffer hideLevelSoundBuffer;
};

}
}

#endif
