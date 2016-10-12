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
 * @file WatchingTimer.hpp
 * @brief renders the two digits displayed on both side of the game screen
 * during the watching period
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
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    WatchingTimer(const utils::Context& context);

    /**
     * @brief default destructor, empty, declared here only in order to use
     * forwarding declaration
     */
    ~WatchingTimer() noexcept;

    /**
     * @brief updates the displayed digit in the timer
     *
     * @param amount the left seconds amount
     *
     * public because called by the game controller to continually update
     * the displayed amount during the watching period
     *
     * not 'const' because it modifies the current object SFML surfaces
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void updateDisplayedAmount(const unsigned short& amount) &;

    /**
     * @brief displays the timer at both sides of the level
     *
     * @param context constant reference to the current context to use
     *
     * public because called by the game controller to render the timer
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void display(const utils::Context& context) const &;

private:

    static constexpr float TIMERS_VERTICAL_POSITION {300.f};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
