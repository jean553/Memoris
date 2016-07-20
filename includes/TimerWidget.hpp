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

#include "Widget.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace widgets
{

class TimerWidget : public Widget
{

public:

    /**
     * @brief constructor, set the timer positions
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     */
    TimerWidget(
        const float& hPosition,
        const float& vPosition
    );

    /**
     * @brief overwritte the display method to render the widget
     */
    void display();

private:

    /**
     * @brief increments the amount of seconds to the current timer time;
     * increments the seconds and minutes variables if necessary; reset the
     * seconds variable if necessary
     */
    void updateTimerValues();

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
};

}
}

#endif
