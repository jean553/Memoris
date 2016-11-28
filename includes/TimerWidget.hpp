/**
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
 * @file TimerWidget.hpp
 * @brief a graphical timer widget; used inside the game controller to display
 * the time
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TIMERWIDGET_H_
#define MEMORIS_TIMERWIDGET_H_

#include "Context.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace widgets
{

class TimerWidget
{

public:

    /**
     * @brief constructor, set the timer positions
     *
     * @param context reference to the current context
     * @param hPosition the horizontal position
     * @param vPosition the vertical position
     */
    TimerWidget(
        const utils::Context& context,
        const float& hPosition,
        const float& vPosition
    );

    /**
     * @brief overwritte the display method to render the widget
     *
     * @param constant reference to the current context to use
     */
    void display(const utils::Context& context);

    /**
     * @brief public method to stop the timer, used by the game controller to
     * stop the timer when the lose period starts
     */
    void stop();

    /**
     * @brief public method to start the timer, used by the game controller to
     * start the timer when the watching period is finished
     */
    void start();

    /**
     * @brief setter of the minutes and seconds amount to display; the function
     * is a setter for the minutes and seconds attributes but also updates the
     * SFML surfaces that displays the countdown
     *
     * @param minutesAmount the amount of minutes to set
     * @param secondsAmount the amount of seconds to set
     */
    void setMinutesAndSeconds(
        const unsigned short& minutesAmount,
        const unsigned short& secondsAmount
    );

    /**
     * @brief getter used by the game controller to know if the countdown
     * is finished
     *
     * @return const bool&
     */
    const bool& isFinished() const;

private:

    static constexpr unsigned short ONE_SECOND {1000};
    static constexpr unsigned short FIRST_SECOND_IN_MINUTE {59};

    /**
     * @brief update the displayed timer string; add a 0 to second or minute
     * value if it contains only one digit to make a better graphical effect
     */
    void updateDisplayedString();

    /* the time of the last update of the timer; we use this variable to
       animate the timer; by default, the value is equal to 0 */
    sf::Uint32 lastTimerUpdateTime {0};

    /* SFML text surface object to render the time */
    sf::Text text;

    /* unsigned shorts to store the minutes and seconds */
    /* NOTE: we do not work with milliseconds, we do not display milliseconds;
       using milliseconds, the time step is too small and we cannot measure it
       properly */
    unsigned short minutes {0};
    unsigned short seconds {0};

    /* determinates if the timer is started or not; this is used by the game
       controller to stop the timer during the lose period for example; the
       timer is stopped and the player does not see the animation anymore;
       during the watching time, the timer is stopped by default */
    bool started {false};

    /* determinates if the countdown is finished; false when the game starts
       and become false when the last second of the last minute has been
       elapsed */
    bool finished {false};
};

}
}

#endif
