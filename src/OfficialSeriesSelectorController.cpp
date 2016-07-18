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
 * @file OfficialSeriesSelectorController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OfficialSeriesSelectorController.hpp"

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
OfficialSeriesSelectorController::OfficialSeriesSelectorController()
{
    /* set the parameters of the title of the screen */
    title.setFont(memoris::fonts::FontsManager::get().getTitleFont());
    title.setString("Official series");
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    title.setPosition(
        550.f,
        50.f
    );

    /* initialize all the official series menu items unique pointers for the
       menu construction */
    std::unique_ptr<items::MenuItem> tutorial(
        new items::MenuItem(
            "1. Tutorial",
            10.f,
            200.f
        )
    );

    std::unique_ptr<items::MenuItem> easy(
        new items::MenuItem(
            "2. Easy",
            10.f,
            250.f
        )
    );

    std::unique_ptr<items::MenuItem> medium(
        new items::MenuItem(
            "3. Medium",
            10.f,
            300.f
        )
    );

    std::unique_ptr<items::MenuItem> difficult(
        new items::MenuItem(
            "4. Difficult",
            10.f,
            350.f
        )
    );

    std::unique_ptr<items::MenuItem> hard(
        new items::MenuItem(
            "5. Hard",
            10.f,
            400.f
        )
    );

    std::unique_ptr<items::MenuItem> veryHard(
        new items::MenuItem(
            "6. Very Hard",
            10.f,
            450.f
        )
    );

    std::unique_ptr<items::MenuItem> hazardous(
        new items::MenuItem(
            "7. Hazardous",
            10.f,
            500.f
        )
    );

    /* select the first official serie name */
    tutorial->select();

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
unsigned short OfficialSeriesSelectorController::render()
{
    utils::Context::get().getSfmlWindow().draw(title);

    renderAllMenuItems();

    nextControllerId = animateScreenTransition();

    while(utils::Context::get().getSfmlWindow().pollEvent(event))
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
                moveUp();

                break;
            }
            case sf::Keyboard::Down:
            {
                moveDown();

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
void OfficialSeriesSelectorController::selectMenuItem()
{
    /* TODO: #512 the first level to played should be loaded from the selected
       serie */

    expectedControllerId = GAME_CONTROLLER_ID;
}

}
}
