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
 * @file WatchingPeriodTimer.hpp
 * @brief this timer is displayed on both left and right side of the playing
 * level during the watching period; it displays the left time for the watching
 * period
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WATCHINGPERIODTIMER_H_
#define MEMORIS_WATCHINGPERIODTIMER_H_

#include <SFML/Graphics.hpp>

#include <memory>

namespace memoris
{
namespace utils
{

class WatchingPeriodTimer
{
public:

    /**
     * @brief constructor, save the given time and initialize the SFML surfaces
     * according to this given time
     *
     * @param time the watching period total time
     */
    WatchingPeriodTimer(const unsigned short& time);

    /**
     * @brief displays the watching period timer SFML surfaces; automatically
     * updates the displayed value every seconds until the last one
     */
    void display();

    /**
     * @brief returns true if the timer is started; used by the game controller
     * to know if the countdown has to be displayed or not
     *
     * @return const bool&
     */
    const bool& isStarted() const;

    /**
     * @brief multiplies the time by the amount of floors
     *
     * @param floors amount of floors in the current level
     *
     * TODO: this is better to directly sends the time amount into the
     * constructor of the object, but when the constructor is called, the
     * level object that contains the amount of floors does not exist yet
     */
    void applyFloorsAmount(const unsigned short& floors);

private:

    /**
     * @brief factory that creates the two SFML surfaces that are displayed
     * on the left and right sides of the level; we use this method because
     * the two surfaces are exactly the sames except some specific attributes,
     * so we refactor the code; we return unique pointer instead of SFML
     * objects, so we make the program run faster during the 'return'
     * instruction of this factory; this method is static because it is a
     * factory function, so it do not manipulate the object attributes
     *
     * @param hPosition horizontal position of the counter
     * @param vPosition vertical position of the counter
     * @param time time to display inside the surface
     *
     * @return std::unique_ptr<sf::Text>
     */
    static std::unique_ptr<sf::Text> createWatchingPeriodTimerText(
        const float& hPosition,
        const float& vPosition,
        const unsigned short& time
    );

    /**
     * @brief displays the two SFML surfaces on both sides of the level
     */
    void updateDisplayedSurfaces() const;

    /* the displayed time into the countdown; we do not specify a default
       value directly here because this attribute is directly initialized in
       the constructor according to the given time from the game controller */
    unsigned short seconds;

    /* boolean that defines if the timer is started or not; by default when
       the object is created, the timer is started; the timer is stopped when
       all the time is elapsed */
    bool started {true};

    /* unsigned integer of 32 bits from the SFML to store the last time the
       timer has been updated; used for the animation */
    sf::Uint32 lastUpdateTime {0};

    /* the SFML surfaces displayed on both left and right sides of the level
       used to display the left watching time of the level */
    /* NOTE: we use unique pointers because we use a factory function
       createWatchingPeriodTimerText to create these surfaces that have common
       attributes; that avoids to copy a whole SFML object at the end of the
       factory execution; we only copy a pointer */
    std::unique_ptr<sf::Text> leftText;
    std::unique_ptr<sf::Text> rightText;
};

}
}

#endif
