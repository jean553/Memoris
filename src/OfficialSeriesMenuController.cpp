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
 * @file OfficialSeriesMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OfficialSeriesMenuController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
OfficialSeriesMenuController::OfficialSeriesMenuController(
    utils::Context& context
) :
    AbstractMenuController(context),
/* this is specific to the official series menu controller, check the
   header for more details */
    contextPtr(context)
{
    /* set the parameters of the title of the screen */
    title.setFont(context.getFontsManager().getTitleFont());
    title.setString("Official series");
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(context.getColorsManager().getColorLightBlue());
    title.setPosition(
        550.f,
        50.f
    );

    /* initialize all the official series menu items unique pointers for the
       menu construction */
    std::unique_ptr<items::MenuItem> tutorial(
        std::make_unique<items::MenuItem>(
            context,
            "1. Tutorial",
            10.f,
            200.f
        )
    );

    std::unique_ptr<items::MenuItem> easy(
        std::make_unique<items::MenuItem>(
            context,
            "2. Easy",
            10.f,
            250.f
        )
    );

    std::unique_ptr<items::MenuItem> medium(
        std::make_unique<items::MenuItem>(
            context,
            "3. Medium",
            10.f,
            300.f
        )
    );

    std::unique_ptr<items::MenuItem> difficult(
        std::make_unique<items::MenuItem>(
            context,
            "4. Difficult",
            10.f,
            350.f
        )
    );

    std::unique_ptr<items::MenuItem> hard(
        std::make_unique<items::MenuItem>(
            context,
            "5. Hard",
            10.f,
            400.f
        )
    );

    std::unique_ptr<items::MenuItem> veryHard(
        std::make_unique<items::MenuItem>(
            context,
            "6. Very Hard",
            10.f,
            450.f
        )
    );

    std::unique_ptr<items::MenuItem> hazardous(
        std::make_unique<items::MenuItem>(
            context,
            "7. Hazardous",
            10.f,
            500.f
        )
    );

    /* select the first official serie name */
    tutorial->select(context);

    /* add all the series names into the menu */
    addMenuItem(std::move(tutorial));
    addMenuItem(std::move(easy));
    addMenuItem(std::move(medium));
    addMenuItem(std::move(difficult));
    addMenuItem(std::move(hard));
    addMenuItem(std::move(veryHard));
    addMenuItem(std::move(hazardous));
}

/**
 *
 */
unsigned short OfficialSeriesMenuController::render(
    utils::Context& context
)
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
            case sf::Keyboard::Escape:
            {
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Return:
            {
                selectMenuItem();

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
void OfficialSeriesMenuController::selectMenuItem()
{
    /* load the content of the serie file into a serie object and insert into
       the game context */
    try
    {
        /* use the playing serie manager to load the serie file content */
        /* TODO: #512 we use a fixed file name for now, of course, this
           parameter should change according to the selected menu item */
        contextPtr.getPlayingSerieManager().loadSerieFileContent(
            "data/series/1.serie"
        );

        /* if no exception, we go to the game controller with the loaded
           serie */
        expectedControllerId = GAME_CONTROLLER_ID;

    }
    /* catch a std::invalid_arguments exception if the file cannot be found;
       we use a reference here to avoid copy, but this is only for optimization
       in that case */
    catch(std::invalid_argument&)
    {
        /* TODO: #559 the error controller should display the error message */

        /* if an error occured, we redirect to the error controller */
        expectedControllerId = ERROR_CONTROLLER_ID;
    }
}

}
}
