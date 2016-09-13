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
 * @brief manage how the levels are played one by one into one serie
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PLAYINGSERIEMANAGER_H_
#define MEMORIS_PLAYINGSERIEMANAGER_H_

#include "NotCopiable.hpp"

#include <string>
#include <queue>

namespace memoris
{
namespace managers
{

class PlayingSerieManager : public utils::NotCopiable
{

public:

    /**
     * @brief checks if the levels queue has a next level or (if the queue
     * is empty)
     *
     * @return const bool
     *
     * does not return a reference because the returned value only exists in
     * the method scope
     */
    const bool hasNextLevel() const & noexcept;

    /**
     * @brief getter for the current watching time for the level; used by the
     * game controller to know how long the watching period is
     *
     * @return const unsigned short&
     */
    const unsigned short& getWatchingTime() const & noexcept;

    /**
     * @brief getter for the amount of remaining levels in the serie
     *
     * @return const size_t
     *
     * does not return a reference here but a copy of the variable; in
     * fact, this method executes 'return queue.size()' which returns a copy
     * of a variable; this variable does not exist at the end of the function
     * execution, so we cannot return a reference
     */
    const size_t getRemainingLevelsAmount() const & noexcept;

    /**
     * @brief returns the next item of the levels container according to the
     * FIFO specifications
     *
     * @return const std::string
     *
     * does not return a reference because it is the string which is popped
     * from the front of the queue, this is a local variable in the method
     * that does not exists outside of it
     *
     * not 'const' method because it modifies the levels strings queue
     */
    const std::string getNextLevelName() & noexcept;

    /**
     * @brief setter for the watching time; used by the game controller to
     * set the next level watching time when the player wins the current level
     *
     * @param time the time to set to the watching time
     */
    void setWatchingTime(const unsigned short& time) & noexcept;

    /**
     * @brief loads all the levels of a given serie file by path
     *
     * @param path the path of the serie file
     *
     * @throw std::invalid_argument if the file cannot be loaded, this
     * exception should be caught in order to display the error controller
     *
     * no 'const' because it modifies the levels queue attribute
     *
     * no 'noexcept' because it throws an exception if the serie file cannot
     * be loaded
     */
    void loadSerieFileContent(const std::string& path) &;

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
