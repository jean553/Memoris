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
 * @file Sound.hpp
 * @brief sound representation, stores the SFML objects
 * @package sounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SOUND_H_
#define MEMORIS_SOUND_H_

#include <memory>

namespace sf
{
class Sound;
class SoundBuffer;
}

namespace memoris
{
namespace sounds
{

class Sound
{

public:

    /**
     * @brief load the sound in the given file; the SFML sound and buffer
     * objects are dynamically loaded into the memory if the file can be
     * loaded; if the loading fails, both of the two pointed objects are
     * destroyed and the two pointers become null
     *
     * @param path location of the sound file
     *
     * 'noexcept' because we do not handle error if the file cannot be loaded;
     * each time the sound has to be played, it justs silently fails
     */
    Sound(const std::string& path) noexcept;

    /**
     * @brief empty destructor declared here instead of the default one;
     * by generating the default one, the compiler needs the whole definition
     * of sf::Sound and sf::SoundBuffer, and they are not defined in this
     * header
     */
    ~Sound() noexcept;

    /**
     * @brief play the SFML sound if it has been loaded successfully
     *
     * declared public because can be called from any controller
     */
    void play() const noexcept;

private:

    /* we use unique pointers to store the SFML sound and sound buffer; it's
       better to use dynamic allocation here because if the objects cannot
       be created successfully, we just do not use memory for them */

    /* pointer to the SFML sound to play, initialized to nullptr directly
       into the constructor; not here because the sf::Sound type is not
       defined */
    std::unique_ptr<sf::Sound> sound;

    /* pointer to the SFML buffer for the current sound; not initialized
       by default because we directly try to initialize it inside the
       default constructor */
    std::unique_ptr<sf::SoundBuffer> buffer;
};

}
}

#endif
