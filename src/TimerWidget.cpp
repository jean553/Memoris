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

#include "fonts.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace widgets
{

class TimerWidget::Impl
{

public:

    Impl(const utils::Context& context)
    {
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(fonts::TEXT_SIZE);
        text.setFillColor(context.getColorsManager().getColorWhite());

        constexpr float WIDGET_HORIZONTAL_POSITION {295.f};
        constexpr float WIDGET_VERTICAL_POSITION {10.f};
        text.setPosition(
            WIDGET_HORIZONTAL_POSITION,
            WIDGET_VERTICAL_POSITION
        );
    }

    sf::Uint32 lastTimerUpdateTime {0};

    sf::Text text;

    /* NOTE: we do not work with milliseconds, we do not display milliseconds;
       using milliseconds, the time step is too small and we cannot measure it
       properly */
    unsigned short minutes {0};
    unsigned short seconds {0};

    bool started {false};
    bool finished {false};
};

/**
 *
 */
TimerWidget::TimerWidget(const utils::Context& context) : 
    impl(std::make_unique<Impl>(context))
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
void TimerWidget::render() const &
{
    auto& started = impl->started;
    auto& seconds = impl->seconds;
    auto& minutes = impl->minutes;

    if (seconds == 0)
    {
        if (minutes == 0)
        {
            started = false;
            impl->finished = true;
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
}

/**
 *
 */
void TimerWidget::updateDisplayedString() const &
{
    auto& seconds = impl->seconds;
    auto& minutes = impl->minutes;

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
void TimerWidget::stop() const & noexcept
{
    impl->started = false;
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
void TimerWidget::setMinutesAndSeconds(
    const unsigned short& minutesAmount,
    const unsigned short& secondsAmount
) const &
{
    impl->minutes = minutesAmount;
    impl->seconds = secondsAmount;

    updateDisplayedString();
}

/**
 *
 */
const bool& TimerWidget::isFinished() const &
{
    return impl->finished;
}

/**
 *
 */
const sf::Text& TimerWidget::getTextSurface() const & noexcept
{
    return impl->text;
}

}
}
