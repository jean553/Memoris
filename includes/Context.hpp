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

#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "SoundsManager.hpp"
#include "TexturesManager.hpp"

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
     * @brief return the elapsed time in milliseconds since
     * the clock started or restarted; returns a SFML integer
     * type for 32 bits integer; the maximum value is equivalent
     * to 49 days; we can considere that this "case won't never
     * happen"
     *
     * @return sf::Int32
     */
    sf::Int32 getClockMillisecondsTime() const;

    /**
     * @brief restart the SFML clock; this function is called
     * everytime the screen is switched from one controller
     * to another
     */
    void restartClock();

    /**
     * @brief returns a reference to the unique fonts manager object
     *
     * @return memoris::fonts::FontsManager&
     */
    memoris::fonts::FontsManager& getFontsManager();

    /**
     * @brief returns a reference to the unique colors manager object
     *
     * @return memoris::colors::ColorsManager&
     */
    memoris::colors::ColorsManager& getColorsManager();

    /**
     * @brief returns a reference to the unique sounds manager object
     *
     * @return memoris::sounds::SoundsManager&
     */
    memoris::sounds::SoundsManager& getSoundsManager();

    /**
     * @brief returns a reference to the unique textures manager object
     *
     * @return memoris::textures::TexturesManager&
     */
    memoris::textures::TexturesManager& getTexturesManager();

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

    /* the main SFML window object */
    sf::RenderWindow sfmlWindow;

    /* the SFML music to play */
    sf::Music music;

    /* the unique SFML clock for time management in every controller
     * NOTE: we use an unique clock for all the animation and time
     * management of the game; the clock is restarted everytime the
     * controller is modified; the maximum time returned in milliseconds
     * is equal to 49 days... so this is a safe method */
    sf::Clock clock;

    /* all the managers create and store SFML objects,
       they provide public method to access to these
       objects */

    /* unique object of fonts factory */
    memoris::fonts::FontsManager fontsManager;

    /* unique object of colors manager */
    memoris::colors::ColorsManager colorsManager;

    /* unique object of sounds manager */
    memoris::sounds::SoundsManager soundsManager;

    /* unique object of textures manager */
    memoris::textures::TexturesManager texturesManager;

    std::map<std::string, std::string> messages;

    std::vector<std::string> stringsList;

    std::string nxtLvlStrPath;
};
}

#endif
