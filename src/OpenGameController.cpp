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
 * @file OpenGameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenGameController.hpp"

#include "Context.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"
#include "ColorsManager.hpp"
#include "controllers.hpp"
#include "SelectionListWidget.hpp"
#include "Cursor.hpp"
#include "DirectoryReader.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace controllers
{

class OpenGameController::Impl
{

public:

    Impl(const utils::Context& context) :
        list(context),
        cursor(context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Open game");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            620.f,
            100.f
        );

        list.setList(
            context,
            utils::getFilesFromDirectory("data/games")
        );
    }

    sf::Text title;

    widgets::SelectionListWidget list;

    widgets::Cursor cursor;
};

/**
 *
 */
OpenGameController::OpenGameController(const utils::Context& context) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
OpenGameController::~OpenGameController() noexcept = default;

/**
 *
 */
const ControllerId& OpenGameController::render() &
{
    context.getSfmlWindow().draw(impl->title);

    impl->list.display(context);

    impl->cursor.render(context);

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
            {
                expectedControllerId = ControllerId::MainMenu;

                break;
            }
            default:
            {
            }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            // const widgets::SelectionListWidget&
            const auto& list = impl->list;
            std::string gameName = list.getCurrentItem();

            if (!gameName.empty())
            {
                context.getGame().createGame(gameName);

                expectedControllerId = ControllerId::SerieMainMenu;

                break;
            }

            list.updateList();

            break;
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
