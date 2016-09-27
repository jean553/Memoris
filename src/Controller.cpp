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
 * @file Controller.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Controller.hpp"

#include "window.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{

namespace controllers
{

class Controller::Impl
{

public:

    Impl(const utils::Context& context)
    {
        transitionSurfaceColor =
            context.getColorsManager().getColorBlackCopy();

        transitionSurface.setSize(
            sf::Vector2f(
                window::WIDTH,
                window::HEIGHT
            )
        );

        transitionSurface.setFillColor(transitionSurfaceColor);
    }

    sf::Int32 lastScreenTransitionTime {0};

    sf::Uint8 transitionStep {5};

    sf::Color transitionSurfaceColor;

    sf::RectangleShape transitionSurface;

    bool openingScreen {true};
};

/**
 *
 */
Controller::Controller(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
Controller::~Controller() noexcept = default;

/**
 *
 */
const unsigned short Controller::animateScreenTransition(
    utils::Context& context
) &
{
    if (!expectedControllerId && !impl->openingScreen)
    {
        return 0;
    }

    impl->transitionSurfaceColor.a = impl->transitionStep * COLOR_UPDATE_STEP;
    impl->transitionSurface.setFillColor(impl->transitionSurfaceColor);

    context.getSfmlWindow().draw(impl->transitionSurface);

    if (
        context.getClockMillisecondsTime() -
        impl->lastScreenTransitionTime > TRANSITION_ANIMATION_INTERVAL
    )
    {
        if (impl->openingScreen)
        {
            impl->transitionStep--;
        }
        else
        {
            impl->transitionStep++;
        }

        impl->lastScreenTransitionTime = context.getClockMillisecondsTime();
    }

    if (impl->transitionStep > TRANSITION_STEPS_MAX)
    {
        return expectedControllerId;
    }

    if (impl->transitionStep <= 0)
    {
        impl->openingScreen = false;
    }

    return 0;
}

}
}
