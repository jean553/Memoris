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
 * @file ErrorController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ErrorController.hpp"

#include "controllers_ids.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts_sizes.hpp"
#include "window.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{
namespace controllers
{

class ErrorController::Impl
{

public:

    Impl(
        const utils::Context& context,
        const sf::String& message
    )
    {
        text.setString(message);
        text.setFillColor(context.getColorsManager().getColorWhite());
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(sizes::TEXT_SIZE);

        constexpr float MESSAGE_VERTICAL_POSITION {300.f};
        text.setPosition(
            window::getCenteredTextHorizontalPosition(text),
            MESSAGE_VERTICAL_POSITION
        );
    }

    sf::Text text;
};

/**
 *
 */
ErrorController::ErrorController(
    const utils::Context& context,
    const sf::String& message
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            message
        )
    )
{
}

/**
 *
 */
ErrorController::~ErrorController() = default;

/**
 *
 */
const ControllerId& ErrorController::render() const &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();

    window.draw(impl->text);

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                /* TODO: #532 return to the official series menu screen for
                   now, the error controller is only accessible from this
                   screen when a level is not found; should go back to the
                   previous controller */
                setExpectedControllerId(ControllerId::OfficialSeriesMenu);

                break;
            }
            default:
            {
                break;
            }
            }
        }
        default:
        {
            break;
        }
        }
    }

    return getNextControllerId();
}

}
}
