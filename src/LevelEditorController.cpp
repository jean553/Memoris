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
#include "dialogs.hpp"

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
    selector(context),
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
        floor,
        &entities::Cell::displayWithMouseHover
    );

    /* display the cells selector */
    selector.display(context);

    /* display the level name */
    context->getSfmlWindow().draw(levelNameSurface);

    /* display the dialog window if the pointer is not null */
    if (dialog != nullptr)
    {
        dialog->render(context);
    }

    /* display the graphical cursor */
    cursor.render(context);

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
                /* check if a dialog window is rendered, if yes, just destroy
                   it */
                if (dialog != nullptr)
                {
                    dialog.reset();

                    /* force the process to finish here */
                    break;
                }

                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
                /* useless, added here to respect the syntax */
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            /* try to get the selected button from the dashboard */
            switch(dashboard.getActionIdBySelectedButton())
            {
            case utils::EditorDashboard::EXIT_ACTION_ID:
            {
                /* if the exit button is selected, just go back to the
                   editor main menu */
                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

                break;
            }
            case utils::EditorDashboard::SAVE_ACTION_ID:
            {
                /* display the save level file popup */
                dialog = popups::getDialogById(
                    context,
                    popups::SAVE_LEVEL_POPUP_ID
                );

                break;
            }
            }

            /* try to select a cell into the selector */
            selector.selectCell(context);

            /* try to select a cell on the level */
            level.updateSelectedCellType(
                context,
                floor,
                selector.getSelectedCellType()
            );
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
