/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
 *
 * This program is free software: you can redistdibute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distdibuted in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * Common contents which can be
 * passed from one screen to another.
 *
 * @file Context.hpp
 * @brief common contents to be passed to controller
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CONTEXT
#define DEF_CONTEXT

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace utils
{
class Context
{
public:

    Context();

    /**
     * @brief common window getter
     *
     * @return common window pointer
     */
    sf::RenderWindow* getWindow();

    /**
     * @brief common window pointer setter
     */
    void setWindow(sf::RenderWindow* commonWindow);

    /**
     * @brief change the current played music
     *
     * @param path              path of the music to play
     */
    void changeMusic(std::string path);

    /**
     * @brief stop music if playing
     */
    void stopMusic();

    /**
     * @brief plays the screen transition sound
     */
    void playScreenTransitionCommonSound();

    /**
     * @brief setter for the previous controller name
     *
     * @param previousControllerNameValue textual name of the previous controller
     */
    void setPreviousControllerName(std::string previousControllerNameValue);

    /**
     * @brief getter for the previous controller name
     *
     * @return string
     */
    std::string getPreviousControllerName();

    /**
     * @brief add a message into the context
     *
     * @param messageName name of the message
     * @param messageValue a message sent from the current container to the next container
     */
    void addMessageByName(
        std::string messageName,
        std::string messageValue
    );

    /**
     * @brief returns a message by name
     *
     * @param messageName name of the message to return
     *
     * @return string
     */
    std::string getMessageByName(std::string messageName);

private:

    sf::RenderWindow* pWindow;

    sf::Music music;

    sf::SoundBuffer soundScreenTransitionBuffer;

    sf::Sound soundScreenTransition;

    std::string previousControllerName;

    std::map<std::string, std::string> messages;
};
}

#endif
