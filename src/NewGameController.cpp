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

#include "controllers_ids.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "InputTextWidget.hpp"
#include "window.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{

namespace controllers
{

class NewGameController::Impl
{

public:

    Impl(const utils::Context& context) :
        inputTextGameName(context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("New game");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());

        constexpr float TITLE_VERTICAL_POSITION {200.f};
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        explanation.setFont(context.getFontsManager().getTextFont());
        explanation.setString("Your name :");
        explanation.setCharacterSize(memoris::fonts::TEXT_SIZE);
        explanation.setColor(context.getColorsManager().getColorWhite());

        constexpr float EXPLANATION_VERTICAL_POSITION {380.f};
        explanation.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(explanation),
            EXPLANATION_VERTICAL_POSITION
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
NewGameController::~NewGameController() = default;

/**
 *
 */
const ControllerId& NewGameController::render() const &
{
    const auto& context = getContext();

    auto& window = context.getSfmlWindow();
    window.draw(impl->title);
    window.draw(impl->explanation);

    const auto& inputText = impl->inputTextGameName;
    inputText.display();

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
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
                setExpectedControllerId(ControllerId::MainMenu);

                break;
            }
            /* TODO: #498 should not be allowed if the name already exists */
            case sf::Keyboard::Return:
            {
                if (inputText.isEmpty())
                {
                    break;
                }

                context.getGame().createGame(inputText.getText());

                setExpectedControllerId(ControllerId::SerieMainMenu);

                break;
            }
            default:
            {
                if (not inputText.isInputTextLineFull())
                {
                    inputText.update(event);
                }

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
