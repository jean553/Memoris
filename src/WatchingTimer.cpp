/*
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
 * @file WatchingTimer.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WatchingTimer.hpp"

#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace widgets
{

class WatchingTimer::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
    {
        constexpr float TIMERS_VERTICAL_POSITION {300.f};

        constexpr float LEFT_TIMER_HORIZONTAL_POSITION {90.f};
        left.setFont(context.getFontsManager().getTextFont());
        left.setFillColor(context.getColorsManager().getColorWhite());
        left.setPosition(
            LEFT_TIMER_HORIZONTAL_POSITION,
            TIMERS_VERTICAL_POSITION
        );

        constexpr float RIGHT_TIMER_HORIZONTAL_POSITION {1400.f};
        right.setFont(context.getFontsManager().getTextFont());
        right.setFillColor(context.getColorsManager().getColorWhite());
        right.setPosition(
            RIGHT_TIMER_HORIZONTAL_POSITION,
            TIMERS_VERTICAL_POSITION
        );

        constexpr unsigned int TIMER_SIZE {140};
        left.setCharacterSize(TIMER_SIZE);
        right.setCharacterSize(TIMER_SIZE);
    }

    sf::Text left;
    sf::Text right;

    const utils::Context& context;
};

/**
 *
 */
WatchingTimer::WatchingTimer(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
WatchingTimer::~WatchingTimer() = default;

/**
 *
 */
void WatchingTimer::setValue(const unsigned short& amount) &
{
    /* setString function only accepts std::string or sf::String */
    std::string value = std::to_string(amount);

    impl->left.setString(value);
    impl->right.setString(value);
}

/**
 *
 */
void WatchingTimer::display() const &
{
    auto& window = impl->context.getSfmlWindow();
    window.draw(impl->left);
    window.draw(impl->right);
}

}
}
