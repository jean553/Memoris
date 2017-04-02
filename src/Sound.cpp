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
 * @file Sound.cpp
 * @package sounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Sound.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace memoris
{
namespace sounds
{

class Sound::Impl
{

public:

    Impl(const std::string& fileName)
    {
        constexpr char SOUNDS_PATH[] {"res/sounds/"};
        constexpr char SOUNDS_EXTENSION[] {".wav"};
        if(buffer->loadFromFile(SOUNDS_PATH + fileName + SOUNDS_EXTENSION))
        {
            sound = std::make_unique<sf::Sound>();
            buffer = std::make_unique<sf::SoundBuffer>();

            sound->setBuffer(*buffer);
        }
    }

    /* we use unique pointers to store the SFML sound and sound buffer; it's
       better to use dynamic allocation here because if the objects cannot
       be created successfully, we just do not use memory for them
       and the program can still run */

    std::unique_ptr<sf::Sound> sound {nullptr};

    std::unique_ptr<sf::SoundBuffer> buffer {nullptr};
};

/**
 *
 */
Sound::Sound(const std::string& path) : impl(std::make_unique<Impl>(path))
{
}

/**
 *
 */
Sound::~Sound() = default;

/**
 *
 */
void Sound::play() const &
{
    if (impl->sound != nullptr)
    {
        impl->sound->play();
    }
}

}
}
