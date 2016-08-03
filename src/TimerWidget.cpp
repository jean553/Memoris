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
 * @file TimerWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TimerWidget.hpp"

#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "fonts.hpp"
#include "Context.hpp"

namespace memoris
{
namespace widgets
{

/**
 *
 */
TimerWidget::TimerWidget(
    const float& hPosition,
    const float& vPosition
) : Widget(
        hPosition,
        vPosition
    )
{
    /* initialize the timer text SFML surface */
    text.setFont(fonts::FontsManager::get().getTextFont());
    text.setCharacterSize(fonts::TEXT_SIZE);
    text.setColor(colors::ColorsManager::get().getColorWhite());
    text.setPosition(
        295.f,
        10.f
    );

    /* update the displayed timer string */
    updateDisplayedString();
}

/**
 *
 */
void TimerWidget::display()
{
    /* check if the elapsed time since the last timer update is more than
       1000 milliseconds; if yes, the timer value is updated; also check if
       the timer is started */
    if (
        started &&
        (
            utils::Context::get().getClockMillisecondsTime() -
            lastTimerUpdateTime > 1000
        )
    )
    {
        /* call the separated private method to update all the timer values */
        updateTimerValues();

        /* save the last timer update time at the end of the animation */
        lastTimerUpdateTime = utils::Context::get().getClockMillisecondsTime();
    }

    /* display the SFML text surface */
    utils::Context::get().getSfmlWindow().draw(text);
}

/**
 *
 */
void TimerWidget::updateTimerValues()
{
    /* increment the amount of displayed seconds */
    seconds++;

    /* adapt the values of other timer variables */

    /* NOTE: we never manage what happens when the amount of minutes is more
       than the unsigned short maximum value; in fact, one round never exceed
       a few minutes; for now, this is a timer, but this timer should be a
       countdown, so this case will never happen after the whole game
       development */

    /* check if the amount of elapsed seconds is equal to 60; if yes,
       the amount of seconds is reset and the amount of minutes is
       incremented */
    if (seconds == 60)
    {
        minutes++;
        seconds = 0;
    }

    /* update the displayed timer string */
    updateDisplayedString();
}

/**
 *
 */
void TimerWidget::updateDisplayedString()
{
    /* declare the SFML strings; call sf::String(const std::string&) for each
       SFML string creation; that's why we convert the unsigned long into
       a std::string in the rvalue, to get a string */
    sf::String secondsString = std::to_string(seconds),
               minutesString = std::to_string(minutes);

    /* NOTE: sf::String also define a insert() method that applies the
       std::string insert() function on m_string; m_string is the internal
       string of the wrapper sf::String, type is std::basic_string<Uint32>
       ( basic string containing unsigned integers of 32 bits long, std::string
       is a typedef for a specialization of that class template for char ) */

    /* add a 0 prefix if the seconds value is less than 10 for better visual
       effect */
    if (seconds < 10)
    {
        secondsString.insert(0, "0");
    }

    /* add a 0 prefix if the minutes value is less than 10 for better visual
       effect */
    if (minutes < 10)
    {
        minutesString.insert(0, "0");
    }

    /* update the SFML surface displayed text */
    text.setString(minutesString + " : " + secondsString);
}

/**
 *
 */
void TimerWidget::stop()
{
    /* the started boolean is marked as false and the timer is stopped */
    started = false;
}

}
}
