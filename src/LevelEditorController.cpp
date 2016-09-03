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
 * @file LevelEditorController.cpp
 * @brief render the level editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelEditorController.hpp"

#include "controllers.hpp"
#include "fonts.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
LevelEditorController::LevelEditorController(
    const std::shared_ptr<utils::Context>& context
) :
    Controller(context),
    dashboard(context),
    level(context),
    cursor(context)
{
    /* the default level name is 'unnamed' */
    levelNameSurface.setString("unnamed");

    levelNameSurface.setFont(context->getFontsManager().getTextFont());
    levelNameSurface.setColor(context->getColorsManager().getColorWhite());
    levelNameSurface.setCharacterSize(fonts::TEXT_SIZE);

    /* set the position once the surface is created because we need the surface
       width to find the surface horizontal position */
    levelNameSurface.setPosition(
        1200.f - levelNameSurface.getLocalBounds().width,
        0.f
    );
}

/**
 *
 */
unsigned short LevelEditorController::render(
    const std::shared_ptr<utils::Context>& context
)
{
    /* display the editor dashboard */
    dashboard.display(context);

    /* display the level */
    level.display(
        context,
        floor
    );

    /* display the graphical cursor */
    cursor.render(context);

    /* display the level name */
    context->getSfmlWindow().draw(levelNameSurface);

    nextControllerId = animateScreenTransition(context);

    while(context->getSfmlWindow().pollEvent(event))
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

}
}
