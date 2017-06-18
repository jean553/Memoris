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
 * @file TimerWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TimerWidget.hpp"

#include "fonts_sizes.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace widgets
{

class TimerWidget::Impl
{

public:

    Impl(
        const utils::Context& context,
        const unsigned short& minutes,
        const unsigned short& seconds
    ) :
        window(context.getSfmlWindow()),
        minutes(minutes),
        seconds(seconds)
    {
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(sizes::TEXT_SIZE);
        text.setFillColor(context.getColorsManager().getColorWhite());

        constexpr float WIDGET_HORIZONTAL_POSITION {295.f};
        constexpr float WIDGET_VERTICAL_POSITION {10.f};
        text.setPosition(
            WIDGET_HORIZONTAL_POSITION,
            WIDGET_VERTICAL_POSITION
        );
    }

    sf::RenderWindow& window;

    sf::Uint32 lastTimerUpdateTime {0};

    sf::Text text;

    unsigned short minutes;
    unsigned short seconds;

    bool started {false};
};

/**
 *
 */
TimerWidget::TimerWidget(
    const utils::Context& context,
    const unsigned short& minutes,
    const unsigned short& seconds
) : 
    impl(
        std::make_unique<Impl>(
            context,
            minutes,
            seconds
        )
    )
{
    updateDisplayedString();
}

/**
 *
 */
TimerWidget::~TimerWidget() = default;

/**
 *
 */
void TimerWidget::display() const &
{
    impl->window.draw(impl->text);
}

/**
 *
 */
void TimerWidget::setStarted(const bool& started) const & noexcept
{
    impl->started = started;
}

/**
 *
 */
void TimerWidget::start() const & noexcept
{
    impl->started = true;
}

/**
 *
 */
void TimerWidget::stop() const & noexcept
{
    impl->started = false;
}

/**
 *
 */
const bool TimerWidget::isTimeOver() const & noexcept
{
    return impl->seconds == 0 and impl->minutes == 0;
}

/**
 *
 */
void TimerWidget::updateDisplayedString() const &
{
    auto& seconds = impl->seconds;
    auto& minutes = impl->minutes;

    /* conversion of the numeric values
       to std::string and then to sf::String */
    sf::String secondsString = std::to_string(seconds);
    sf::String minutesString = std::to_string(minutes);

    if (seconds < 10)
    {
        secondsString.insert(0, "0");
    }

    if (minutes < 10)
    {
        minutesString.insert(0, "0");
    }

    impl->text.setString(minutesString + " : " + secondsString);
}

/**
 *
 */
void TimerWidget::decrementPlayingTimer() const &
{
    auto& started = impl->started;
    auto& seconds = impl->seconds;
    auto& minutes = impl->minutes;

    if (seconds == 0)
    {
        if (minutes == 0)
        {
            started = false;
        }
        else
        {
            minutes--;

            constexpr unsigned short FIRST_SECOND_IN_MINUTE {59};
            seconds = FIRST_SECOND_IN_MINUTE;
        }
    }
    else
    {
        seconds--;
    }

    updateDisplayedString();
}

}
}
