/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

#include "fonts.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"

namespace memoris
{
namespace widgets
{

/**
 *
 */
TimerWidget::TimerWidget(
    const utils::Context& context,
    const float& hPosition,
    const float& vPosition
)
{
    /* initialize the timer text SFML surface */
    text.setFont(context.getFontsManager().getTextFont());
    text.setCharacterSize(fonts::TEXT_SIZE);
    text.setColor(context.getColorsManager().getColorWhite());
    text.setPosition(
        hPosition,
        vPosition
    );

    /* update the displayed timer string */
    updateDisplayedString();
}

/**
 *
 */
void TimerWidget::display(const utils::Context& context)
{
    if (
        !(
            started and
            (
                context.getClockMillisecondsTime() -
                lastTimerUpdateTime > ONE_SECOND
            )
        )
    )
    {
        context.getSfmlWindow().draw(text);

        return;
    }

    if (seconds == 0)
    {
        if (minutes == 0)
        {
            started = false;
            finished = true;
        }
        else
        {
            minutes--;
            seconds = FIRST_SECOND_IN_MINUTE;
        }
    }
    else
    {
        seconds--;
    }

    updateDisplayedString();

    context.getSfmlWindow().draw(text);

    lastTimerUpdateTime = context.getClockMillisecondsTime();
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

/**
 *
 */
void TimerWidget::start()
{
    /* set the 'start' boolean to true automatically starts the countdown */
    started = true;
}

/**
 *
 */
void TimerWidget::setMinutesAndSeconds(
    const unsigned short& minutesAmount,
    const unsigned short& secondsAmount
)
{
    minutes = minutesAmount;
    seconds = secondsAmount;

    /* force the update of the SFML surfaces that displays the countdown with
       the new values */
    updateDisplayedString();
}

/**
 *
 */
const bool& TimerWidget::isFinished() const
{
    return finished;
}

}
}
