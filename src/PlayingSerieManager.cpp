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
#include <queue>

namespace memoris
{
namespace managers
{

constexpr const char* OFFICIALS_SERIE_DIRECTORY_NAME {"officials"};
constexpr const char* PERSONALS_SERIE_DIRECTORY_NAME {"personals"};

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

    /**
     * determines if win this serie would update the game
     * file last unlocked serie value; in fact, this value is set
     * by the official serie menu and we only want to unlock the next
     * serie if the current playing serie is the last unlocked one
     */
    bool unlockable {false};
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
PlayingSerieManager::~PlayingSerieManager() = default;

/**
 *
 */
const bool PlayingSerieManager::hasNextLevel() const & noexcept
{
    return !impl->levels.empty();
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
const std::string PlayingSerieManager::getNextLevelName() const &
{
    /* get the front item of the queue and
       delete it from the container */
    auto& levels = impl->levels;
    std::string level = levels.front();
    levels.pop();

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
void PlayingSerieManager::loadSerieFileContent(
    const std::string& name,
    const SerieType& type
) const &
{
    /* clear the queue containing the levels of the previous serie */
    impl->levels = std::queue<std::string>();

    impl->levelIndex = 0;

    std::string filePath = "data/series/";

    if (type == SerieType::Official)
    {
        filePath += OFFICIALS_SERIE_DIRECTORY_NAME;
    }
    else
    {
        filePath += PERSONALS_SERIE_DIRECTORY_NAME;
    }

    filePath += "/" + name + ".serie";

    std::ifstream file(filePath);
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

    std::string level;

    while(std::getline(file, level))
    {
        impl->levels.push(level);
    }

    impl->serieName = name;

    file.close();
}

/**
 *
 */
void PlayingSerieManager::incrementLevelIndex() const & noexcept
{
    impl->levelIndex += 1;
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
void PlayingSerieManager::setIsOfficialSerie(const bool& official) const &
    noexcept
{
    auto& serieType = impl->serieType;

    if (official)
    {
        serieType = OFFICIALS_SERIE_DIRECTORY_NAME;

        return;
    }

    serieType = PERSONALS_SERIE_DIRECTORY_NAME;
}

/**
 *
 */
const std::string& PlayingSerieManager::getSerieTypeAsString() const & noexcept
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
    const auto& totalSeriePlayingTime = impl->totalSeriePlayingTime;

    sf::String secondsString = fillMissingTimeDigits(
        totalSeriePlayingTime % SECONDS_IN_ONE_MINUTE
    );

    sf::String minutesString = fillMissingTimeDigits(
        totalSeriePlayingTime / SECONDS_IN_ONE_MINUTE
    );

    return minutesString + ":" + secondsString;
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

/**
 *
 */
void PlayingSerieManager::setIsUnlockable(const bool& unlockable)
    const & noexcept
{
    impl->unlockable = unlockable;
}

/**
 *
 */
const bool& PlayingSerieManager::isUnlockable() const & noexcept
{
    return impl->unlockable;
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

}
}
