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
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PlayingSerieManager.hpp"

#include "SerieResult.hpp"

#include <SFML/System/String.hpp>

#include <fstream>
#include <stdexcept>
#include <queue>

namespace memoris
{
namespace managers
{

constexpr const char* OFFICIALS_SERIE_DIRECTORY_NAME {"officials"};

constexpr unsigned short DEFAULT_WATCHING_TIME {6};
constexpr unsigned short DEFAULT_LIFES {0};
constexpr unsigned short DEFAULT_SERIE_PLAYING_TIME {0};

class PlayingSerieManager::Impl
{

public:

    /* we use the FIFO (first in first out) method to store the levels names;
       in fact, we add all the levels one by one into the container when we
       load a serie and we pop them one by one in the same order; the queue
       container is directly optimized for that kind of operations */
    std::queue<std::string> levels;

    unsigned short watchingTime {DEFAULT_WATCHING_TIME};
    unsigned short lifes {DEFAULT_LIFES};
    unsigned short totalSeriePlayingTime {DEFAULT_SERIE_PLAYING_TIME};
    unsigned short levelIndex {0};

    std::string serieName;
    std::string serieType {OFFICIALS_SERIE_DIRECTORY_NAME};

    std::vector<std::unique_ptr<entities::SerieResult>> results;
};

/**
 *
 */
PlayingSerieManager::PlayingSerieManager() : impl(std::make_unique<Impl>())
{
}

/**
 *
 */
PlayingSerieManager::~PlayingSerieManager() noexcept = default;

/**
 *
 */
const bool PlayingSerieManager::hasNextLevel() const & noexcept
{
    if (impl->levels.empty())
    {
        return false;
    }

    return true;
}

/**
 *
 */
const unsigned short& PlayingSerieManager::getWatchingTime() const & noexcept
{
    return impl->watchingTime;
}

/**
 *
 */
const size_t PlayingSerieManager::getRemainingLevelsAmount() const & noexcept
{
    return impl->levels.size();
}

/**
 *
 */
const std::string PlayingSerieManager::getNextLevelName() & noexcept
{
    /* get the front item of the queue and delete it from the container */
    std::string level = impl->levels.front();
    impl->levels.pop();

    return level;
}

/**
 *
 */
void PlayingSerieManager::setWatchingTime(const unsigned short& time) const &
noexcept
{
    impl->watchingTime = time;
}

/**
 *
 */
void PlayingSerieManager::loadSerieFileContent(const std::string& name) const &
{
    /* clear the queue containing the levels of the previous serie */
    impl->levels = std::queue<std::string>();

    impl->levelIndex = 0;

    /* the name parameter is in the [personals|officials]/name format */
    std::ifstream file("data/series/" + name + ".serie");
    if (!file.is_open())
    {
        /* TODO: #561 throw std::invalid_argument if the file cannot be opened;
           we could use file.exception(failbit) to directly throw an exception
           if the file cannot be loaded, but the problem is that it also
           throw an exception when the end of the file is found (eof); for now
           I do not know how to walk-around this problem, but this second
           solution would be better to also handle the file reading safely */
        throw std::invalid_argument("Cannot open the given serie file.");
    }

    constexpr unsigned short RESULTS_PER_SERIE {3};
    for (
        unsigned short i = 0;
        i < RESULTS_PER_SERIE; 
        i++
    )
    {
        std::string line;
        std::getline(file, line);

        if (line == ".")
        {
            continue;
        }

        auto result = std::make_unique<entities::SerieResult>(line);
        impl->results.push_back(std::move(result));
    }

    std::string level;

    while(std::getline(file, level))
    {
        impl->levels.push(level);
    }

    impl->serieName = name;

    /* std::ifstream object is automatically closed at the end of the scope */
}

/**
 *
 */
const std::string& PlayingSerieManager::getSerieName() const & noexcept
{
    return impl->serieName;
}

/**
 *
 */
const unsigned short& PlayingSerieManager::getLevelIndex() const & noexcept
{
    return impl->levelIndex;
}

/**
 *
 */
void PlayingSerieManager::incrementLevelIndex() const & noexcept
{
    impl->levelIndex++;
}

/**
 *
 */
void PlayingSerieManager::setLifesAmount(const unsigned short& lifes) const &
    noexcept
{
    impl->lifes = lifes;
}

/**
 *
 */
const unsigned short& PlayingSerieManager::getLifesAmount() const & noexcept
{
    return impl->lifes;
}

/**
 *
 */
const unsigned short& PlayingSerieManager::getPlayingTime() const & noexcept
{
    return impl->totalSeriePlayingTime;
}

/**
 *
 */
using SerieResults = std::vector<std::unique_ptr<entities::SerieResult>>;
const SerieResults& PlayingSerieManager::getResults()
    const & noexcept
{
    return impl->results;
}

/**
 *
 */
void PlayingSerieManager::setIsOfficialSerie(const bool& official) const &
    noexcept
{
    auto& serieType = impl->serieType;

    if (official)
    {
        serieType = OFFICIALS_SERIE_DIRECTORY_NAME;

        return;
    }

    constexpr const char* PERSONALS_SERIE_DIRECTORY_NAME {"personals"};
    serieType = PERSONALS_SERIE_DIRECTORY_NAME;
}

/**
 *
 */
const std::string& PlayingSerieManager::getSerieType() const & noexcept
{
    return impl->serieType;
}

/**
 *
 */
void PlayingSerieManager::reinitialize() const & noexcept
{
    impl->watchingTime = DEFAULT_WATCHING_TIME;
    impl->lifes = DEFAULT_LIFES;
    impl->totalSeriePlayingTime = DEFAULT_SERIE_PLAYING_TIME;
}

/**
 *
 */
const sf::String PlayingSerieManager::getPlayingTimeAsString() const &
{
    constexpr unsigned short SECONDS_IN_ONE_MINUTE {60};

    sf::String secondsString = fillMissingTimeDigits(
        impl->totalSeriePlayingTime % SECONDS_IN_ONE_MINUTE
    );

    sf::String minutesString = fillMissingTimeDigits(
        impl->totalSeriePlayingTime / SECONDS_IN_ONE_MINUTE
    );

    return minutesString + ":" + secondsString;
}

/**
 *
 */
const sf::String PlayingSerieManager::fillMissingTimeDigits(
    const unsigned short& numericValue
) const &
{
    sf::String timeNumber = std::to_string(numericValue);

    if (numericValue < 10)
    {
        timeNumber.insert(0, "0");
    }

    return timeNumber;
}

/**
 *
 */
void PlayingSerieManager::addSecondsToPlayingSerieTime(
    const unsigned short& levelPlayingTime
) const & noexcept
{
    impl->totalSeriePlayingTime += levelPlayingTime;
}

}
}
