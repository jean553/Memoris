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
 * @file NewGameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "NewGameController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "InputTextWidget.hpp"
#include "window.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{

namespace controllers
{

class NewGameController::Impl
{

public:

    /* we voluntary do not use the getCenteredSfmlSurfaceHorizontalPosition()
       refactored method to center the input text line */

    Impl(const utils::Context& context) :
        inputTextGameName(
            context,
            500.f,
            450.f,
            600.f,
            15
        )
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("New game");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            200.f
        );

        explanation.setFont(context.getFontsManager().getTextFont());
        explanation.setString("Your name :");
        explanation.setCharacterSize(memoris::fonts::TEXT_SIZE);
        explanation.setColor(context.getColorsManager().getColorWhite());
        explanation.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(explanation),
            380.f
        );
    }

    sf::Text title;
    sf::Text explanation;

    widgets::InputTextWidget inputTextGameName;
};

/**
 *
 */
NewGameController::NewGameController(const utils::Context& context) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
NewGameController::~NewGameController() noexcept = default;

/**
 *
 */
const unsigned short& NewGameController::render(
    const utils::Context& context
) &
{
    window.draw(impl->title);
    window.draw(impl->explanation);

    impl->inputTextGameName.display(context);

    nextControllerId = animateScreenTransition(context);

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
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            /* TODO: #498 should not be allowed if the name already exists */
            case sf::Keyboard::Return:
            {
                if (impl->inputTextGameName.isEmpty())
                {
                    break;
                }

                context.getGame().createGame(
                    impl->inputTextGameName.getText()
                );

                expectedControllerId = SERIE_MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
                impl->inputTextGameName.update(event);

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

    return nextControllerId;
}

}
}
