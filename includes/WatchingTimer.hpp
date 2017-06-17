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
 * @file WatchingTimer.hpp
 * @brief countdown on both side of the level during the watching period
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WATCHINGTIMER_H_
#define MEMORIS_WATCHINGTIMER_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class WatchingTimer
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context
     * @param displayedTime default time displayed by the timer
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    WatchingTimer(
        const utils::Context& context,
        const unsigned short& displayedTime
    );

    WatchingTimer(const WatchingTimer&) = delete;

    WatchingTimer operator=(const WatchingTimer&) = delete;

    /**
     * @brief default destructor
     */
    ~WatchingTimer();

    /**
     * @brief displays the timer at both sides of the level
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void display() const &;

    /**
     * @brief decrement the watching timer (the time is not handled
     * by this function individually in order to regroup time management)
     */
    void decrementWatchingTimer() const & noexcept;

    /**
     * @brief getter of the watching timer
     *
     * @return const unsigned short&
     */
    const unsigned short& getWatchingTimerValue() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
