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
 * @file WatchingPeriodTimer.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WatchingPeriodTimer.hpp"

#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "fonts.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
WatchingPeriodTimer::WatchingPeriodTimer()
{
    seconds = series::PlayingSerieManager::get().getWatchingTime();

    /* initialize the two SFML surfaces used to display the left watching time
       of the current level */

    leftText = createWatchingPeriodTimerText(75.f, 335.f, seconds);
    rightText = createWatchingPeriodTimerText(1400.f, 335.f, seconds);
}

/**
 *
 */
void WatchingPeriodTimer::display(std::shared_ptr<Context> context)
{
    /* display the SFML surfaces */
    context->getSfmlWindow().draw(*leftText);
    context->getSfmlWindow().draw(*rightText);

    /* check if the timer is started and if at least one second elapsed since
       the last timer value update; if yes, decrement the displayed value */
    if (
        started &&
        (
            context->getClockMillisecondsTime() -
            lastUpdateTime > 1000
        )
    )
    {
        /* decrement the seconds amount */
        seconds--;

        /* check if the amount of seconds is equal to 0 and stop the timer */
        if (seconds == 0)
        {
            /* stop the timer */
            started = false;

            /* directly return from here; in fact, this is optimized to do not
               update the SFML surfaces as we do just after in the code because
               these surfaces are supposed to be displayed anymore anyway */
            return;
        }

        /* update the SFML surfaces */
        updateDisplayedSurfaces();

        /* update the last update time */
        lastUpdateTime = context->getClockMillisecondsTime();
    }
}

/**
 *
 */
const bool& WatchingPeriodTimer::isStarted() const
{
    return started;
}

/**
 *
 */
std::unique_ptr<sf::Text> WatchingPeriodTimer::createWatchingPeriodTimerText(
    const float& hPosition,
    const float& vPosition,
    const unsigned short& time
)
{
    /* creates an unique pointer to a sf::Text object; we use unique pointers
       because we never need to have many pointers pointing on the same SFML
       texture; this is more restrictive and this is what we want; we use the
       make_unique function to directly creates an unique pointer safely in
       the C++14 way */
    std::unique_ptr<sf::Text> sfmlText(std::make_unique<sf::Text>());

    /* set the position of the counter according to the given values */
    sfmlText->setPosition(hPosition, vPosition);

    /* the size of the character is the sane as the main menu title size */
    sfmlText->setCharacterSize(fonts::TITLE_SIZE);

    /* the font of the counter is the normal font of the game */
    sfmlText->setFont(fonts::FontsManager::get().getTextFont());

    /* the color of the counter is a light blue color */
    sfmlText->setColor(colors::ColorsManager::get().getColorLightBlue());

    /* transform the given unsigned short into a string to pass it to the
       SFML surface function */
    sfmlText->setString(std::to_string(time));

    /* return the unique pointer to the created object */
    return sfmlText;
}

/**
 *
 */
void WatchingPeriodTimer::applyFloorsAmount(const unsigned short& floors)
{
    /* the whole watching time is the allowed watching seconds amount
       multiplied by the floors amount */
    seconds *= floors;

    /* update the SFML surfaces */
    updateDisplayedSurfaces();
}

/**
 *
 */
void WatchingPeriodTimer::updateDisplayedSurfaces() const
{
    leftText->setString(std::to_string(seconds));
    rightText->setString(std::to_string(seconds));
}

}
}
