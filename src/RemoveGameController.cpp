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
 * @file RemoveGameController.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "RemoveGameController.hpp"

#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "controllers.hpp"
#include "fonts.hpp"
#include "window.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace controllers
{

class RemoveGameController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        message.setString("Are you sure to delete this game ? Y/N");
        message.setFont(context.getFontsManager().getTextFont());
        message.setCharacterSize(fonts::TEXT_SIZE);
        message.setColor(context.getColorsManager().getColorWhite());
        message.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(message),
            300.f
        );
    }

    sf::Text message;
};

/**
 *
 */
RemoveGameController::RemoveGameController(
    const utils::Context& context
) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
RemoveGameController::~RemoveGameController()
    noexcept = default;

/**
 *
 */
const unsigned short& RemoveGameController::render(
    const utils::Context& context
) &
{
    context.getSfmlWindow().draw(impl->message);

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            case sf::Keyboard::N:
            {
                expectedControllerId = SERIE_ControllerId::MainMenu;

                break;
            }
            case sf::Keyboard::Y:
            {
                context.getGame().deleteGameFile();

                expectedControllerId = ControllerId::MainMenu;

                break;
            }
            default:
            {
            }
            }
        }
        default:
        {
        }
        }
    }

    return nextControllerId;
}

}
}
