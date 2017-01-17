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
 * @file TimerWidget.hpp
 * @brief a graphical timer widget; used inside the game controller to display
 * the time
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TIMERWIDGET_H_
#define MEMORIS_TIMERWIDGET_H_

#include <memory>

namespace sf
{
class Text;
}

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
     * @brief constructor, set the timer positions
     *
     * @param context reference to the current context
     */
    TimerWidget(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     *
     * a destructor cannot be const
     *
     * no noexcept here, default destructors are noexcept
     */
    ~TimerWidget();

    /**
     * @brief changes the value of the timer widget; this method is executed
     * only if the played level is not an edited one
     */
    void render() const &;

    /**
     * @brief public method to stop the timer, used by the game controller to
     * stop the timer when the lose period starts
     */
    void stop() const & noexcept;

    /**
     * @brief public method to start the timer, used by the game controller to
     * start the timer when the watching period is finished
     */
    void start() const & noexcept;

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
    ) const &;

    /**
     * @brief getter used by the game controller to know if the countdown
     * is finished
     *
     * @return const bool&
     */
    const bool& isFinished() const &;

    /**
     * @brief the SFML surface that displays the text is the only displayed
     * attribute of the widget; so we provides a direct access to its
     * reference in order to save a reference in a controller (it avoids
     * to create a functions call tree)
     *
     * @return const sf::Text&
     */
    const sf::Text& getTextSurface() const & noexcept;

private:

    static constexpr unsigned short ONE_SECOND {1000};
    static constexpr unsigned short FIRST_SECOND_IN_MINUTE {59};

    /**
     * @brief update the displayed timer string; add a 0 to second or minute
     * value if it contains only one digit to make a better graphical effect
     *
     * not noexcept because some SFML methods are not noexcept
     */
    void updateDisplayedString() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
