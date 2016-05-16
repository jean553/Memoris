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
#include "Sounds.hpp"

using namespace utils;

/**
 *
 */
Context::Context()
{
    soundScreenTransitionBuffer.loadFromFile(
        constants::Sounds::SCREEN_TRANSITION_SOUND_PATH
    );

    soundScreenTransition.setBuffer(
        soundScreenTransitionBuffer
    );
}

/**
 *
 */
sf::RenderWindow* Context::getWindow()
{
    return pWindow;
}

/**
 *
 */
void Context::setWindow(sf::RenderWindow* commonWindow)
{
    pWindow = commonWindow;
}

/**
 *
 */
void Context::changeMusic(std::string musicPath)
{
    if(musicPath.empty())
    {
        return;
    }

    stopMusic();

    music.openFromFile(musicPath);
    music.play();
}

/**
 *
 */
void Context::stopMusic()
{
    if(music.getStatus() == sf::Sound::Playing)
    {
        music.stop();
    }
}

/**
 *
 */
void Context::playScreenTransitionCommonSound()
{
    soundScreenTransition.play();
}

/**
 *
 */
void Context::addMessageByName(
    std::string messageName,
    std::string messageValue
)
{
    messages[messageName] = messageValue;
}

/**
 *
 */
std::string Context::getMessageByName(std::string messageName)
{
    // check if the given message name exists
    if (messages.find(messageName) == messages.end())
    {
        return "";
    }

    return messages.at(messageName);
}

/**
 *
 */
void Context::removeAllMessages()
{
    messages.clear();
}

/**
 *
 */
void Context::setStringsList(std::vector<std::string> stringsListToSave)
{
    stringsList = stringsListToSave;
}

/**
 *
 */
std::vector<std::string> Context::getStringsList()
{
    return stringsList;
}

/**
 *
 */
void Context::addStringIntoStringsList(std::string newString)
{
    stringsList.push_back(newString);
}