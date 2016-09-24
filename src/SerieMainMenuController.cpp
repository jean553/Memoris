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

namespace memoris
{
namespace controllers
{

/**
 *
 */
SerieMainMenuController::SerieMainMenuController(
    utils::Context& context
) :
    AbstractMenuController(context)
{
    /* set the properties of the series main menu title */
    title.setFont(context.getFontsManager().getTitleFont());
    title.setString("Series");
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(context.getColorsManager().getColorLightBlue());
    title.setPosition(
        700.f,
        50.f
    );

    /* creates the unique pointer to the official series item */
    std::unique_ptr<items::MenuItem> officialSeries(
        std::make_unique<items::MenuItem>(
            context,
            "Official series",
            550.f,
            250.f
        )
    );

    /* creates the unique pointer to the personal series item */
    std::unique_ptr<items::MenuItem> personalSeries(
        std::make_unique<items::MenuItem>(
            context,
            "Personal series",
            520.f,
            470.f
        )
    );

    /* creates the unique pointer to the back item */
    std::unique_ptr<items::MenuItem> back(
        std::make_unique<items::MenuItem>(
            context,
            "Back",
            720.f,
            800.f
        )
    );

    /* select the official series item in the menu */
    officialSeries->select(context);

    /* add the menu items inside the menu items list of the abstract menu
       controller class */
    addMenuItem(std::move(officialSeries));
    addMenuItem(std::move(personalSeries));
    addMenuItem(std::move(back));
}

/**
 *
 */
unsigned short SerieMainMenuController::render(
    utils::Context& context
) &
{
    /* display the serie main menu title */
    context.getSfmlWindow().draw(title);

    /* display all the menu items */
    renderAllMenuItems(context);

    /* render the opening/closing animation of the screen if necessary */
    nextControllerId = animateScreenTransition(context);

    /* series main menu events loop; the player can select between the
       official series item and the personal series item; the player can also
       go back to the main menu selecting the back button */
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
                /* useless, added here to respect the syntax */
                break;
            }
            }
        }
        default:
        {
            /* useless, added here to respect the syntax */
            break;
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void SerieMainMenuController::selectMenuItem()
{
    /* TODO: nothing happens for now when the personal series item is selected,
       we have to define a behavior and call the expected controller */

    switch(getSelectorPosition())
    {
    /* the official series menu item is selected */
    case 0:
    {
        expectedControllerId = OFFICIAL_SERIES_MENU_CONTROLLER_ID;

        break;
    }
    /* the back menu item is selected */
    case 2:
    {
        expectedControllerId = MAIN_MENU_CONTROLLER_ID;

        break;
    }
    }
}

}
}
