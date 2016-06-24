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
 * @file Sound.hpp
 * @brief sound representation, stores the SFML objects
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SOUND_H_
#define MEMORIS_SOUND_H_

#include <SFML/Audio.hpp>

#include <memory>

namespace memoris
{
namespace sounds
{

class Sound
{

public:

    /**
     * @brief constructor, creates the SFML objects and
     * try to load the sound from the given file
     *
     * @param filePath path of the sound file
     */
    Sound(const std::string& filePath);

    /**
     * @brief plays the sound if loaded successfully,
     * if the sound has not been loaded correctly, the
     * function silently fails
     */
    void play() const;

private:

    /* NOTE: we use unique pointers for the SFML sounds; we use
       an unique pointer because it is never copied (only called here), it
       is NULL if the loading process of the sound failed, it is automatically
       destroyed */

    std::unique_ptr<sf::Sound> sound;

    /* each SFML sound is linked with a sound buffer */
    sf::SoundBuffer buffer;
};

}
}

#endif
