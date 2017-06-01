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
 * @file OpenGameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenGameController.hpp"

#include "controllers_ids.hpp"
#include "FontsManager.hpp"
#include "fonts_sizes.hpp"
#include "ColorsManager.hpp"
#include "controllers.hpp"
#include "FilesSelectionListWidget.hpp"
#include "Cursor.hpp"
#include "Game.hpp"
#include "Context.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <fstream>

namespace memoris
{
namespace controllers
{

constexpr char GAMES_FILES_DIRECTORY[] {"data/games/"};
constexpr char GAMES_FILES_EXTENSION[] {".game"};

class OpenGameController::Impl
{

public:

    Impl(const utils::Context& context) :
        list(
            context,
            "data/games"
        ),
        cursor(context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Open game");
        title.setCharacterSize(memoris::sizes::SUB_TITLE_SIZE);
        title.setFillColor(context.getColorsManager().getColorLightBlue());

        constexpr float TITLE_HORIZONTAL_POSITION {620.f};
        constexpr float TITLE_VERTICAL_POSITION {100.f};
        title.setPosition(
            TITLE_HORIZONTAL_POSITION,
            TITLE_VERTICAL_POSITION
        );
    }

    sf::Text title;

    widgets::FilesSelectionListWidget list;

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
OpenGameController::~OpenGameController() = default;

/**
 *
 */
const ControllerId& OpenGameController::render() const &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();

    window.draw(impl->title);

    auto& cursor = impl->cursor;
    const auto cursorPosition = cursor.getPosition();

    impl->list.display(cursorPosition);

    cursor.render();

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
                setExpectedControllerId(ControllerId::MainMenu);

                break;
            }
            default:
            {
                break;
            }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            const auto& list = impl->list;
            const auto& index = list.getCurrentIndex();

            constexpr short NO_SELECTION_INDEX {-1};
            if (
                index < list.getItemsAmount() and
                index != NO_SELECTION_INDEX
            )
            {
                const auto& gameName = list.getCurrentItem();

                context.setGameName(gameName);

                setExpectedControllerId(ControllerId::SerieMainMenu);

                break;
            }

            using ListMovement = widgets::SelectionListWidget::ListMovement;

            if (list.canScrollUp())
            {
                list.updateAllItemsPosition(ListMovement::Up);
            }
            else if (list.canScrollDown())
            {
                list.updateAllItemsPosition(ListMovement::Down);
            }

            break;
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
