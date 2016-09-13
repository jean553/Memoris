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

/**
 *
 */
Sound::Sound(const std::string& path) noexcept :
    sound(nullptr),
    buffer(std::make_unique<sf::SoundBuffer>())
{
    if(buffer->loadFromFile(path))
    {
        sound = std::make_unique<sf::Sound>();
        sound->setBuffer(*buffer);
    }
    else
    {
        buffer.reset();
    }
}

/**
 *
 */
Sound::~Sound() noexcept
{
}

/**
 *
 */
void Sound::play() const noexcept
{
    if (sound != nullptr)
    {
        sound->play();
    }
}

}
}
