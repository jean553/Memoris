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
 * @file EditorMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorMenuController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "MenuItem.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class EditorMenuController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Editor");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            50.f
        );
    }

    sf::Text title;
};

/**
 *
 */
EditorMenuController::EditorMenuController(const utils::Context& context) :
    AbstractMenuController(context),
    impl(std::make_unique<Impl>(context))
{
    std::unique_ptr<items::MenuItem> level(
        std::make_unique<items::MenuItem>(
            context,
            "Level",
            200.f
        )
    );

    std::unique_ptr<items::MenuItem> serie(
        std::make_unique<items::MenuItem>(
            context,
            "Serie",
            350.f
        )
    );

    std::unique_ptr<items::MenuItem> back(
        std::make_unique<items::MenuItem>(
            context,
            "Back",
            800.f
        )
    );

    level->select(context);

    addMenuItem(std::move(level));
    addMenuItem(std::move(serie));
    addMenuItem(std::move(back));
}

/**
 *
 */
EditorMenuController::~EditorMenuController() noexcept = default;

/**
 *
 */
const ControllerId& EditorMenuController::render(const utils::Context& context) &
{
    context.getSfmlWindow().draw(impl->title);

    renderAllMenuItems(context);

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
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

/**
 *
 */
void EditorMenuController::selectMenuItem() & noexcept
{
    switch(getSelectorPosition())
    {
    case 0:
    {
        expectedControllerId = ControllerId::LevelEditor;

        break;
    }
    case 1:
    {
        expectedControllerId = ControllerId::SerieEditor;

        break;
    }
    case 2:
    {
        expectedControllerId = ControllerId::MainMenu;

        break;
    }
    }
}

}
}
