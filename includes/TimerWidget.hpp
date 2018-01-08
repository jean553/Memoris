/**
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
 * @file TimerWidget.hpp
 * @brief displays the time during the game
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TIMERWIDGET_H_
#define MEMORIS_TIMERWIDGET_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class TimerWidget
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context
     * @param minutes default displayed minutes value
     * @param seconds default displayed seconds value
     */
    TimerWidget(
        const utils::Context& context,
        const unsigned short& minutes,
        const unsigned short& seconds
    );

    TimerWidget(const TimerWidget&) = delete;

    TimerWidget& operator=(const TimerWidget&) = delete;

    /**
     * @brief default destructor
     */
    ~TimerWidget();

    /**
     * @brief displays the timer widget string
     *
     * not noexcept because this method uses SFML methods that are not noexcept
     */
    void display() const &;

    /**
     * @brief starts the timer
     */
    void start() const & noexcept;

    /**
     * @brief stops the timer
     */
    void stop() const & noexcept;

    /**
     * @brief indicates if the timer is running or not
     *
     * @return const bool&
     */
    const bool& isStarted() const & noexcept;

    /**
     * @brief getter to know if the countdown is finished
     *
     * @return const bool
     */
    const bool isTimeOver() const & noexcept;

    /**
     * @brief decrement the timer value
     *
     * not noexcept because this method uses SFML methods that are not noexcept
     */
    void decrementPlayingTimer() const &;

private:

    /**
     * @brief formats the time displayed string (MM:SS format)
     *
     * not noexcept because it calls some SFML methods that are not noexcept
     */
    void updateDisplayedString() const &;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
