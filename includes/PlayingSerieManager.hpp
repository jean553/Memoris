/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief manages a played serie, manage levels the user plays
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PLAYINGSERIEMANAGER_H_
#define MEMORIS_PLAYINGSERIEMANAGER_H_

#include <memory>
#include <vector>

namespace sf
{
class String;
}

namespace memoris
{

namespace entities
{
class SerieResult;
}

namespace managers
{

class PlayingSerieManager
{

public:

    /**
     * @enum PlayingSerieManager::SerieType
     * @brief a serie can be official or personal
     */
    enum class SerieType {
        Official, /** < available with the game */
        Personal /** < created by the user */
    };

    /**
     * @brief constructor
     */
    PlayingSerieManager();

    PlayingSerieManager(const PlayingSerieManager&) = delete;

    PlayingSerieManager& operator=(const PlayingSerieManager&) = delete;

    /**
     * @brief default destructor
     */
    ~PlayingSerieManager();

    /**
     * @brief checks if the levels queue has a next level
     *
     * @return const bool
     */
    const bool hasNextLevel() const & noexcept;

    /**
     * @brief getter for the current watching time for the level
     *
     * @return const unsigned short&
     */
    const unsigned short& getWatchingTime() const & noexcept;

    /**
     * @brief getter for the amount of remaining levels in the serie
     *
     * @return const size_t
     */
    const size_t getRemainingLevelsAmount() const & noexcept;

    /**
     * @brief returns the next item of the levels container according to the
     * FIFO specifications and remove the returned item from the queue
     *
     * @return const std::string
     *
     * not noexcept because the pop() and front() methods of std::queue
     * may throw if the container is empty
     */
    const std::string getNextLevelName() const &;

    /**
     * @brief setter for the watching time
     *
     * @param time the time to set to the watching time
     */
    void setWatchingTime(const unsigned short& time) const & noexcept;

    /**
     * @brief loads all the levels of a given serie file by path, save the name
     * of the serie if the file loading process succeeds
     *
     * @param name the name of the serie to open (not the full path)
     * @param type the type of the serie (official or personal)
     *
     * @throw std::invalid_argument if the file cannot be loaded, this
     * exception should be caught in order to display the error controller
     */
    void loadSerieFileContent(
        const std::string& name,
        const SerieType& type
    ) const &;

    /**
     * @brief increments the current level index
     */
    void incrementLevelIndex() const & noexcept;

    /**
     * @brief set the amount of lifes
     *
     * @param lifes the amount of lifes to save
     */
    void setLifesAmount(const unsigned short& lifes) const & noexcept;

    /**
     * @brief returns the amount of lifes
     *
     * @return const unsigned short&
     */
    const unsigned short& getLifesAmount() const & noexcept;

    /**
     * @brief getter of the total playing time
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayingTime() const & noexcept;

    /**
     * @brief setter that specifies if the serie is official or not
     *
     * @param official indicates if the serie is official or not
     */
    void setIsOfficialSerie(const bool& official) const & noexcept;

    /**
     * @brief getter that specifies if the serie is official or not
     *
     * @return const std::string&
     */
    const std::string& getSerieTypeAsString() const & noexcept;

    /**
     * @brief reinitializes the manager, used when switch from one serie
     * to another one
     */
    void reinitialize() const & noexcept;

    /**
     * @brief returns the playing time in format "00:00"; this function is
     * required for both of the level editor and the serie ending controller
     *
     * @return const sf::String
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    const sf::String getPlayingTimeAsString() const &;

    /**
     * @brief add the given seconds amount to the total amount of seconds
     * for the serie play time; this function is called at the end of every
     * level in order to make the total serie playing time
     *
     * @param levelPlayingTime the level playing time to add
     */
    void addSecondsToPlayingSerieTime(const unsigned short& levelPlayingTime)
        const & noexcept;

    /**
     * @brief setter that determines if win the current serie
     * would unlock the next one
     *
     * @param unlockable true if the serie is unlockable
     */
    void setIsUnlockable(const bool& unlockable) const & noexcept;

    /**
     * @brief getter that indicates if win the current serie
     * would unlock the next one
     *
     * @return const bool&
     */
    const bool& isUnlockable() const & noexcept;

private:

    /**
     * @brief add a 0 into a time number string if the number is less than 0
     *
     * @param numericValue the numeric value to edit
     *
     * @return const sf::String
     *
     * not noexcept because the std::string constructor may throw,
     * the SFML functions may throw
     */
    const sf::String fillMissingTimeDigits(const unsigned short& numericValue)
        const &;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
