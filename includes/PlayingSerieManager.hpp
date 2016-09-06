/*
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
 * @file PlayingSerieManager.hpp
 * @brief singleton object class used to load serie content from file and pass
 * the serie information from one game controller to another during the level
 * switchs
 * TODO: #560 this class is not "as necessary as" the textures manager or the
 * fonts manager; the scope should not be global;
 * @package series
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PLAYINGSERIEMANAGER_H_
#define MEMORIS_PLAYINGSERIEMANAGER_H_

#include <string>
#include <queue>

namespace memoris
{
namespace series
{

class PlayingSerieManager
{

public:

    /* declare deleted functions to prevent object copy */

    PlayingSerieManager(const PlayingSerieManager&) = delete;
    PlayingSerieManager operator=(const PlayingSerieManager&) = delete;

    /* use the default constructor */

    PlayingSerieManager() = default;

    /**
     * @brief loads all the level of a given serie file by path
     *
     * @param path the path of the serie file
     *
     * @throw std::invalid_argument if the file cannot be loaded, this
     * exception should be caught in order to display the error controller
     */
    void loadSerieFileContent(const std::string& path);

    /**
     * @brief returns the next (or the first) item of the levels container
     * according to the FIFO specifications
     *
     * @return std::string
     */
    std::string getNextLevelName();

    /**
     * @brief checks if the levels queue has a next level or if the queue is
     * empty; this is used by the game controller to know if a next level
     * has to be loaded when the player wins the current level
     *
     * @return const bool
     */
    const bool hasNextLevel() const;

    /**
     * @brief getter for the current watching time for the level; used by the
     * game controller to know the long of the watching period
     *
     * @return const unsigned short&
     */
    const unsigned short& getWatchingTime() const;

    /**
     * @brief setter for the watching time; used by the game controller to
     * set the next level watching time when the player wins the current level
     *
     * @param tim the time to set to the watching time
     */
    void setWatchingTime(const unsigned short& time);

    /**
     * @brief getter for the amount of remaining levels in the serie
     *
     * @return const size_t
     *
     * NOTE: we do not return a reference here but a copy of the variable; in
     * fact, this method executes 'return queue.size()' which returns a copy
     * of a variable; this variable does not exist at the end of the function
     * execution, so we cannot return a reference
     */
    const size_t getRemainingLevelsAmount() const;

private:

    /* we use the FIFO (first in first out) method to store the levels names;
       in fact, we add all the levels one by one into the container when we
       load a serie and we pop them one by one in the same order; the queue
       container is directly optimized for that kind of operations */
    std::queue<std::string> levels;

    /* current watching time that will be given for the next level; this time
       is the watching time *per floor*; this value is set to 6 by default
       all the time when a serie starts; we set it here because this value
       has to be transferred from one level to another */
    unsigned short watchingTime {6};
};

}
}

#endif
