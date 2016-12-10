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

#include <memory>

namespace memoris
{
namespace managers
{

class PlayingSerieManager : public utils::NotCopiable
{
    /* declared here because used in an alias */
    static constexpr unsigned short RESULTS_PER_SERIE_FILE_AMOUNT {3};

public:

    using Results = std::array<std::string, RESULTS_PER_SERIE_FILE_AMOUNT>;

    /**
     * @brief constructor, empty, only used to initialize the implementation
     */
    PlayingSerieManager() noexcept;

    /**
     * @brief default destructor, empty, only used for forwarding declaration
     */
    ~PlayingSerieManager() noexcept;

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
    void setWatchingTime(const unsigned short& time) const & noexcept;

    /**
     * @brief loads all the levels of a given serie file by path, save the name
     * of the serie if the file loading process succeeds
     *
     * @param name the name of the serie to open (not the full path)
     *
     * @throw std::invalid_argument if the file cannot be loaded, this
     * exception should be caught in order to display the error controller
     *
     * no 'const' because it modifies the levels queue attribute
     */
    void loadSerieFileContent(const std::string& name) &;

    /**
     * @brief getter of the current loaded serie name
     *
     * @return const std::string&
     */
    const std::string& getSerieName() const & noexcept;

    /**
     * @brief getter of the current level index
     *
     * @return const unsigned short&
     */
    const unsigned short& getLevelIndex() const & noexcept;

    /**
     * @brief increments the current level index
     */
    void incrementLevelIndex() const & noexcept;

    /**
     * @brief set the amount of lifes (used to transfer this amount from one
     * level to another one)
     *
     * @param lifes constant reference to the amount of lifes to save
     */
    void setLifesAmount(const unsigned short& lifes) const & noexcept;

    /**
     * @brief returns the amount of lifes
     *
     * @return const unsigned short&
     */
    const unsigned short& getLifesAmount() const & noexcept;

    /**
     * @brief add the level playing time to the total serie playing time
     *
     * @param levelPlayingTime constant reference to the current level playing
     * time
     */
    void incrementPlayingTime() const & noexcept;

    /**
     * @brief getter of the total playing time
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayingTime() const & noexcept;

    /**
     * @brief getter of the results list loaded from the serie file
     *
     * @return const std::array<std::string, N>&
     */
    const Results& getResults() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
