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
    levelNameSurface.setString("unnamed");
    levelNameSurface.setFont(context->getFontsManager().getTextFont());
    levelNameSurface.setColor(context->getColorsManager().getColorWhite());
    levelNameSurface.setCharacterSize(fonts::TEXT_SIZE);

    updateLevelNameSurfacePosition();

    floorSurface.setFont(context->getFontsManager().getTextFont());
    floorSurface.setColor(context->getColorsManager().getColorWhite());
    floorSurface.setCharacterSize(fonts::TEXT_SIZE);
    floorSurface.setString("1");
    floorSurface.setPosition(
        1240.f,
        450.f
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

    /* display the current floor */
    context->getSfmlWindow().draw(floorSurface);

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
                deleteActiveDialog();

                break;
            }
            case sf::Keyboard::Return:
            {
                /* if the current displayed dialog window is the save window,
                   just update the level name */
                if (saveDialogIsActive())
                {
                    /* check if the level name is empty */
                    if (dialog->getInputTextWidget().isEmpty())
                    {
                        break;
                    }

                    levelNameSurface.setString(
                        dialog->getInputTextWidget().getText()
                    );

                    /* as the width of the surface has changed, we have to
                       update the position of the surface */
                    updateLevelNameSurfacePosition();

                    deleteActiveDialog();
                }
            }
            default:
            {
                /* add input into the save dialog window */
                if (saveDialogIsActive())
                {
                    dialog->getInputTextWidget().update(event);
                }
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

                currentActionId = utils::EditorDashboard::SAVE_ACTION_ID;

                break;
            }
            case utils::EditorDashboard::FLOOR_UP_ACTION_ID:
            {
                /* increment the current floor if not equal to 9 */
                if (floor != entities::Level::MAX_FLOOR)
                {
                    floor++;

                    /* update the displayed floor */
                    floorSurface.setString(std::to_string(floor + 1));
                }

                break;
            }
            case utils::EditorDashboard::FLOOR_DOWN_ACTION_ID:
            {
                /* increment the current floor if not equal to 9 */
                if (floor != entities::Level::MIN_FLOOR)
                {
                    floor--;

                    /* update the displayed floor */
                    floorSurface.setString(std::to_string(floor + 1));
                }

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

const bool LevelEditorController::saveDialogIsActive() const noexcept
{
    if (
        currentActionId ==
        utils::EditorDashboard::SAVE_ACTION_ID &&
        dialog != nullptr
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void LevelEditorController::deleteActiveDialog() noexcept
{
    if (dialog != nullptr)
    {
        dialog.reset();
    }
}

/**
 *
 */
void LevelEditorController::updateLevelNameSurfacePosition() noexcept
{
    /* set the position once the surface is created because we need the surface
       width to find the surface horizontal position */
    levelNameSurface.setPosition(
        1200.f - levelNameSurface.getLocalBounds().width,
        0.f
    );
}

}
}
