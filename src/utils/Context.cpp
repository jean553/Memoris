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
 * @file Context.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Context.hpp"

using namespace utils;

/**
 *
 */
Context::Context()
{
    music = new sf::Music();
}

/**
 *
 */
Context::~Context()
{
    delete music;
}

/**
 *
 */
void Context::setWindow(sf::RenderWindow* commonWindow)
{
    window = commonWindow;
}

/**
 *
 */
void Context::setSentMessage(std::string message)
{
    sentMessage = message;
}

/**
 *
 */
sf::RenderWindow* Context::getWindow()
{
    return window;
}

/**
 *
 */
std::string Context::getSentMessage()
{
    return sentMessage;
}

/**
 *
 */
void Context::changeMusic(std::string musicPath)
{
    if(musicPath.empty()) {
        return;
    }

    // no music to stop if the function
    // is called for the first time
    if(music->getStatus() == sf::Sound::Playing) {
        music->stop();
    }

    music->openFromFile(musicPath);

    music->play();
}
