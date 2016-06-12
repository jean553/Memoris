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
 * @file Context.hpp
 * @brief class for the unique context object of the program, contains data
 * supposed to be transfered from one controller to another
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTEXT_H_
#define MEMORIS_CONTEXT_H_

#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace utils
{
class Context
{
public:

    Context();

    /**
     * @brief getter on the SFML window object
     *
     * @return reference to the SFML window object
     */
    sf::RenderWindow& getSfmlWindow();

    /**
     * @brief load a new music file and play it,
     * silently fails if the music cannot be loaded
     *
     * @param path file path of the music to play
     */
    void loadMusicFile(const std::string& path);

    /**
     * @brief check if a music is playing, if yes, stop it
     */
    void stopMusic();

    /**
     * @brief plays the screen transition sound, this sound is played each
     * time the screen (controller) is switched from one to another one
     */
    void playScreenTransitionSound();

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
     * @return string message or empty message if the message name does not exist
     */
    std::string getMessageByName(std::string messageName);

    /**
     * @brief removes all the messages
     */
    void removeAllMessages();

    /**
     * @brief strings list setter
     *
     * @param stringsListToSave strings vector to save
     */
    void setStringsList(std::vector<std::string> stringsListToSave);

    /**
     * @brief strings list getter
     *
     * @return list of strings
     */
    std::vector<std::string> getStringsList();

    /**
     * @brief add one string inside the strings list
     *
     * @param newString string to add
     */
    void addStringIntoStringsList(std::string newString);

    /**
     * @brief return the string of the path of the next level,
     * used when call the game controller to specify the level
     *
     * @return std::string
     */
    std::string getNxtLvlStrPath() const;

    /**
     * @brief set the string of the path of the next level,
     * used when call the game controller to specify the level
     *
     * @param path string of the level file path
     */
    void setNxtLvlStrPath(const std::string& path);

    /**
     * @brief remove all the strings from the strings list
     */
    void removeAllStrings();

private:

    /**
     * @brief loads the screen transition sound
     */
    void loadScreenTransitionSound();

    /* the main SFML window object */
    sf::RenderWindow sfmlWindow;

    /* the SFML music to play */
    sf::Music music;

    /* SFML sound buffer for the unique transition sound */
    sf::SoundBuffer screenTransitionSoundBuffer;

    /* unique pointer for the SFML screen transition sound; we use an
       unique pointer because it is never copied (only called here), it
       is NULL if the loading process of the sound failed, it is automatically
       destroyed */
    std::unique_ptr<sf::Sound> screenTransitionSound;

    std::map<std::string, std::string> messages;

    std::vector<std::string> stringsList;

    std::string nxtLvlStrPath;
};
}

#endif
