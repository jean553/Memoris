/*
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
 * @file OpenLevelController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenLevelController.hpp"

#include "Context.hpp"
#include "fonts.hpp"
#include "controllers.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class OpenLevelController::Impl
{

public:

    Impl(utils::Context& context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Open level");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            620.f,
            50.f
        );
    }

    sf::Text title;
};

/**
 *
 */
OpenLevelController::OpenLevelController(utils::Context& context) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
OpenLevelController::~OpenLevelController() noexcept = default;

/**
 *
 */
unsigned short OpenLevelController::render(utils::Context& context) &
{
    context.getSfmlWindow().draw(impl->title);

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

}
}
