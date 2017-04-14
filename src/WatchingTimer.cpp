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

    Impl(const utils::Context& context)
    {
        left.setFont(context.getFontsManager().getTextFont());
        left.setFillColor(context.getColorsManager().getColorWhite());
        left.setPosition(
            90.f,
            TIMERS_VERTICAL_POSITION
        );

        right.setFont(context.getFontsManager().getTextFont());
        right.setFillColor(context.getColorsManager().getColorWhite());
        right.setPosition(
            1400.f,
            TIMERS_VERTICAL_POSITION
        );

        constexpr unsigned int TIMER_SIZE {140};
        left.setCharacterSize(TIMER_SIZE);
        right.setCharacterSize(TIMER_SIZE);
    }

    sf::Text left;
    sf::Text right;
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
WatchingTimer::~WatchingTimer() noexcept = default;

/**
 *
 */
void WatchingTimer::updateDisplayedAmount(const unsigned short& amount) &
{
    /* setString function only accepts std::string or sf::String */
    impl->left.setString(std::to_string(amount));
    impl->right.setString(std::to_string(amount));
}

/**
 *
 */
void WatchingTimer::display(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->right);
}

}
}
