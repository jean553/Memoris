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
 * @file EditorMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorMenuController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
EditorMenuController::EditorMenuController(
    utils::Context& context
) : AbstractMenuController(context)
{
    /* set the parameters of the title of the screen */
    title.setFont(context.getFontsManager().getTitleFont());
    title.setString("Editor");
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(context.getColorsManager().getColorLightBlue());
    title.setPosition(
        710.f,
        50.f
    );

    /* creates the menu items */

    std::unique_ptr<items::MenuItem> level(
        std::make_unique<items::MenuItem>(
            context,
            "Level",
            710.f,
            200.f
        )
    );

    std::unique_ptr<items::MenuItem> serie(
        std::make_unique<items::MenuItem>(
            context,
            "Serie",
            710.f,
            350.f
        )
    );

    std::unique_ptr<items::MenuItem> back(
        std::make_unique<items::MenuItem>(
            context,
            "Back",
            720.f,
            800.f
        )
    );

    /* the level item is selected by default */
    level->select(context);

    addMenuItem(std::move(level));
    addMenuItem(std::move(serie));
    addMenuItem(std::move(back));
}

/**
 *
 */
const unsigned short& EditorMenuController::render(
    utils::Context& context
) &
{
    context.getSfmlWindow().draw(title);

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
                /* useless, added here to respect the syntax */
            }
            }
        }
        default:
        {
            /* useless, added here to respect the syntax */
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void EditorMenuController::selectMenuItem()
{
    switch(getSelectorPosition())
    {
    /* display the level editor */
    case 0:
    {
        expectedControllerId = LEVEL_EDITOR_CONTROLLER_ID;

        break;
    }
    /* go back to the main menu when select 'back' */
    case 2:
    {
        expectedControllerId = MAIN_MENU_CONTROLLER_ID;

        break;
    }
    }
}

}
}
