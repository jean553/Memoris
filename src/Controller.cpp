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
 * @file Controller.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Controller.hpp"

#include "controllers_ids.hpp"
#include "window.hpp"
#include "ColorsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{

namespace controllers
{

class Controller::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
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

    sf::Event event;

    const utils::Context& context;

    ControllerId nextControllerId {ControllerId::NoController},
        expectedControllerId {ControllerId::NoController};

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
Controller::~Controller() = default;

/**
 *
 */
const ControllerId Controller::animateScreenTransition(
    const utils::Context& context
) const &
{
    const auto& expectedControllerId = impl->expectedControllerId;

    if (
        expectedControllerId == ControllerId::NoController and 
        not impl->openingScreen
    )
    {
        return ControllerId::NoController;
    }

    auto& transitionSurfaceColor = impl->transitionSurfaceColor;
    auto& transitionSurface = impl->transitionSurface;

    constexpr sf::Uint8 COLOR_UPDATE_STEP {51};
    transitionSurfaceColor.a = impl->transitionStep * COLOR_UPDATE_STEP;
    transitionSurface.setFillColor(transitionSurfaceColor);

    auto& window = context.getSfmlWindow();
    window.draw(transitionSurface);

    const auto& currentTime = context.getClockMillisecondsTime();
    auto& lastTime = impl->lastScreenTransitionTime;
    auto& transitionStep = impl->transitionStep;

    constexpr sf::Int32 TRANSITION_ANIMATION_INTERVAL {25};
    if (currentTime - lastTime > TRANSITION_ANIMATION_INTERVAL)
    {
        if (impl->openingScreen)
        {
            transitionStep--;
        }
        else
        {
            transitionStep++;
        }

        lastTime = currentTime;
    }

    constexpr sf::Uint8 TRANSITION_STEPS_MAX {5};
    if (transitionStep > TRANSITION_STEPS_MAX)
    {
        return expectedControllerId;
    }

    constexpr unsigned short OPENED_SCREEN_MINIMUM_STEP {0};
    if (transitionStep <= OPENED_SCREEN_MINIMUM_STEP)
    {
        impl->openingScreen = false;
    }

    return ControllerId::NoController;
}

/**
 *
 */
const ControllerId& Controller::getNextControllerId() const & noexcept
{
    return impl->nextControllerId;
}

/**
 *
 */
void Controller::setNextControllerId(const ControllerId& nextControllerId)
    const & noexcept
{
    impl->nextControllerId = nextControllerId;
}

/**
 *
 */
void Controller::setExpectedControllerId(
    const ControllerId& expectedControllerId
) const & noexcept
{
    impl->expectedControllerId = expectedControllerId;
}

/**
 *
 */
sf::Event& Controller::getEvent() const & noexcept
{
    return impl->event;
}

/**
 *
 */
const utils::Context& Controller::getContext() const & noexcept
{
    return impl->context;
}

}
}
