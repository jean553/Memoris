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
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Sound.hpp"

namespace memoris
{
namespace sounds
{

/**
 *
 */
Sound::Sound(const std::string& filePath)
{
    /* by default, the pointer is null; this is used for error management */
    sound = nullptr;

    /* try to load the sound from file; if it fails, the pointer remains
       null, the sound won't be used */
    if(buffer.loadFromFile(filePath))
    {
        sound.reset(new sf::Sound());
        sound->setBuffer(buffer);
    }
}

/**
 *
 */
void Sound::play() const
{
    /* check if the sound has been loaded correctly;
       if not loaded, the function silently fails */
    if (sound != nullptr)
    {
        sound->play();
    }
}

}
}
