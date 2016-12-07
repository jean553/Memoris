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
 * @file SerieMainMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SerieMainMenuController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "MenuItem.hpp"
#include "window.hpp"
#include "Game.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class SerieMainMenuController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Series");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            50.f
        );

        gameName.setFont(context.getFontsManager().getTextFont());
        gameName.setString(context.getGame().getName());
        gameName.setCharacterSize(memoris::fonts::TEXT_SIZE);
        gameName.setColor(context.getColorsManager().getColorLightBlue());
        gameName.setPosition(
            window::WIDTH - gameName.getLocalBounds().width -
                GAME_NAME_RIGHT_PADDING,
            810.f
        );
    }

    static constexpr float GAME_NAME_RIGHT_PADDING {20.f};

    sf::Text title;
    sf::Text gameName;
};

/**
 *
 */
SerieMainMenuController::SerieMainMenuController(
    const utils::Context& context
) :
    AbstractMenuController(context),
    impl(std::make_unique<Impl>(context))
{
    std::unique_ptr<items::MenuItem> officialSeries(
        std::make_unique<items::MenuItem>(
            context,
            "Official series",
            250.f
        )
    );

    std::unique_ptr<items::MenuItem> personalSeries(
        std::make_unique<items::MenuItem>(
            context,
            "Personal series",
            350.f
        )
    );

    std::unique_ptr<items::MenuItem> back(
        std::make_unique<items::MenuItem>(
            context,
            "Back",
            650.f
        )
    );

    std::unique_ptr<items::MenuItem> remove(
        std::make_unique<items::MenuItem>(
            context,
            "Remove",
            810.f,
            items::MenuItem::HorizontalPosition::Left
        )
    );

    officialSeries->select(context);

    addMenuItem(std::move(officialSeries));
    addMenuItem(std::move(personalSeries));
    addMenuItem(std::move(back));
    addMenuItem(std::move(remove));
}

/**
 *
 */
SerieMainMenuController::~SerieMainMenuController() noexcept = default;

/**
 *
 */
const unsigned short& SerieMainMenuController::render(
    const utils::Context& context
) &
{
    context.getSfmlWindow().draw(impl->title);

    renderAllMenuItems(context);

    context.getSfmlWindow().draw(impl->gameName);

    nextControllerId = animateScreenTransition(context);

    while (context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Up:
            {
                moveUp(context);

                break;
            }
            case sf::Keyboard::Down:
            {
                moveDown(context);

                break;
            }
            case sf::Keyboard::Return:
            {
                selectMenuItem();

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

    return nextControllerId;
}

/**
 *
 */
void SerieMainMenuController::selectMenuItem() & noexcept
{
    switch(getSelectorPosition())
    {
    case 0:
    {
        expectedControllerId = OFFICIAL_SERIES_MENU_CONTROLLER_ID;

        break;
    }
    case 1:
    {
        expectedControllerId = PERSONAL_SERIES_MENU_CONTROLLER_ID;

        break;
    }
    case 2:
    {
        expectedControllerId = MAIN_MENU_CONTROLLER_ID;

        break;
    }
    case 3:
    {
        expectedControllerId = REMOVE_GAME_CONTROLLER_ID;

        break;
    }
    }
}

}
}
