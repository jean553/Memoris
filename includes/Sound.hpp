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
 * @file Sound.hpp
 * @brief stores a sound
 * @package sounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SOUND_H_
#define MEMORIS_SOUND_H_

#include <memory>

namespace memoris
{
namespace sounds
{

class Sound
{

public:

    /**
     * @brief loads sound with the given file name
     *
     * @param fileName sound file name (no path and no extension)
     *
     * @throw std::bad_alloc the implementation cannot be initialized,
     * this exception is never caught and the program terminates
     */
    Sound(const std::string& fileName);

    /**
     * @brief default destructor
     */
    ~Sound();

    /**
     * @brief plays the sound if correctly loaded
     *
     * NOTE: this method silently does nothing if the sound is not loaded
     *
     * no noexcept because sf::Sound::play is not noexcept
     */
    void play() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
