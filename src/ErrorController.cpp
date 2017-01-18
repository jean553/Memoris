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
 * @file ErrorController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ErrorController.hpp"

#include "controllers_ids.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

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
        text.setColor(context.getColorsManager().getColorWhite());
        text.setFont(context.getFontsManager().getTextFont());
        text.setCharacterSize(fonts::TEXT_SIZE);

        /* window::WIDTH is an unsigned int, and there is guarantee about the
           getLocalBounds().width type */
        text.setPosition(
            static_cast<float>(window::WIDTH) / 2 - 
            static_cast<float>(text.getLocalBounds().width) / 2,
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
ErrorController::~ErrorController() noexcept = default;

/**
 *
 */
const ControllerId& ErrorController::render() &
{
    context.getSfmlWindow().draw(impl->text);

    setNextControllerId(animateScreenTransition(context));

    while(context.getSfmlWindow().pollEvent(event))
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
