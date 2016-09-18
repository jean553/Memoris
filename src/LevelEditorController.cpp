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
#include "files.hpp"
#include "InputTextWidget.hpp"
#include "EditorDashboard.hpp"
#include "CellsSelector.hpp"
#include "Level.hpp"
#include "Cursor.hpp"
#include "SaveLevelDialog.hpp"
#include "NewLevelDialog.hpp"

namespace memoris
{
namespace controllers
{

class LevelEditorController::Impl
{

public:

    Impl(utils::Context& context) :
        dashboard(context),
        selector(context),
        level(context),
        cursor(context)
    {
        levelNameSurface.setString("unnamed");
        levelNameSurface.setFont(context.getFontsManager().getTextFont());
        levelNameSurface.setColor(context.getColorsManager().getColorWhite());
        levelNameSurface.setCharacterSize(fonts::TEXT_SIZE);
        levelNameSurface.setPosition(
            1200.f - levelNameSurface.getLocalBounds().width,
            0.f
        );

        floorSurface.setFont(context.getFontsManager().getTextFont());
        floorSurface.setColor(context.getColorsManager().getColorWhite());
        floorSurface.setCharacterSize(fonts::TEXT_SIZE);
        floorSurface.setString("1");
        floorSurface.setPosition(
            1240.f,
            450.f
        );
    }

    utils::EditorDashboard dashboard;

    utils::CellsSelector selector;

    entities::Level level;

    unsigned short floor {0};
    unsigned short currentActionId {0};

    widgets::Cursor cursor;

    sf::Text levelNameSurface;
    sf::Text floorSurface;

    std::unique_ptr<popups::SaveLevelDialog> saveLevelDialog {nullptr};
    std::unique_ptr<popups::NewLevelDialog> newLevelDialog {nullptr};
};

/**
 *
 */
LevelEditorController::LevelEditorController(
    utils::Context& context
) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
LevelEditorController::~LevelEditorController() noexcept = default;

/**
 *
 */
unsigned short LevelEditorController::render(
    utils::Context& context
) &
{
    /* display the editor dashboard */
    impl->dashboard.display(context);

    /* display the level */
    impl->level.display(
        context,
        impl->floor,
        &entities::Cell::displayWithMouseHover
    );

    /* display the cells selector */
    impl->selector.display(context);

    /* display the level name */
    context.getSfmlWindow().draw(impl->levelNameSurface);

    /* display the current floor */
    context.getSfmlWindow().draw(impl->floorSurface);

    /* display the saveLevelDialog window if the pointer is not null */
    if (impl->saveLevelDialog != nullptr)
    {
        impl->saveLevelDialog->render(context);
    }
    else if (impl->newLevelDialog != nullptr)
    {
        impl->newLevelDialog->render(context);
    }

    /* display the graphical cursor */
    impl->cursor.render(context);

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
                deleteActiveDialog();

                break;
            }
            case sf::Keyboard::Return:
            {
                /* if the current displayed saveLevelDialog window is the save 
                   window, just update the level name */
                if (saveDialogIsActive())
                {
                    /* check if the level name is empty */
                    if (impl->saveLevelDialog->getInputTextWidget().isEmpty())
                    {
                        break;
                    }

                    impl->levelNameSurface.setString(
                        impl->saveLevelDialog->getInputTextWidget().getText()
                    );

                    /* save the level file */
                    saveLevelFile(
                        impl->saveLevelDialog->getInputTextWidget().getText(),
                        impl->level.getCells()
                    );

                    /* as the width of the surface has changed, we have to
                       update the position of the surface */
                    updateLevelNameSurfacePosition();

                    deleteActiveDialog();
                }
            }
            case sf::Keyboard::N:
            {
                if (newDialogIsActive())
                {
                    deleteActiveDialog();

                    /* stop the process here */
                    break;
                }
            }
            default:
            {
                /* add input into the save saveLevelDialog window */
                if (saveDialogIsActive())
                {
                    impl->saveLevelDialog->getInputTextWidget().update(event);
                }
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            /* try to get the selected button from the dashboard */
            switch(impl->dashboard.getActionIdBySelectedButton())
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
                impl->saveLevelDialog = std::make_unique<popups::SaveLevelDialog>(
                                      context
                                  );

                impl->currentActionId = utils::EditorDashboard::SAVE_ACTION_ID;

                break;
            }
            case utils::EditorDashboard::NEW_ACTION_ID:
            {
                impl->newLevelDialog = std::make_unique<popups::NewLevelDialog>(
                                     context
                                 );

                impl->currentActionId = utils::EditorDashboard::NEW_ACTION_ID;

                break;
            }
            case utils::EditorDashboard::FLOOR_UP_ACTION_ID:
            {
                /* increment the current floor if not equal to 9 */
                if (impl->floor != entities::Level::MAX_FLOOR)
                {
                    impl->floor++;

                    /* update the displayed floor */
                    impl->floorSurface.setString(
                        std::to_string(
                            impl->floor + 1
                        )
                    );
                }

                break;
            }
            case utils::EditorDashboard::FLOOR_DOWN_ACTION_ID:
            {
                /* increment the current floor if not equal to 9 */
                if (impl->floor != entities::Level::MIN_FLOOR)
                {
                    impl->floor--;

                    /* update the displayed floor */
                    impl->floorSurface.setString(
                        std::to_string(
                            impl->floor + 1
                        )
                    );
                }

                break;
            }
            }

            /* try to select a cell into the selector */
            impl->selector.selectCell(context);

            /* try to select a cell on the level */
            impl->level.updateSelectedCellType(
                context,
                impl->floor,
                impl->selector.getSelectedCellType()
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

/**
 *
 */
const bool LevelEditorController::saveDialogIsActive() const & noexcept
{
    if (
        impl->currentActionId ==
        utils::EditorDashboard::SAVE_ACTION_ID &&
        impl->saveLevelDialog != nullptr
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
const bool LevelEditorController::newDialogIsActive() const & noexcept
{
    if (
        impl->currentActionId ==
        utils::EditorDashboard::NEW_ACTION_ID &&
        impl->newLevelDialog != nullptr
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void LevelEditorController::deleteActiveDialog() & noexcept
{
    if (impl->saveLevelDialog != nullptr)
    {
        impl->saveLevelDialog.reset();
    }
    else if (impl->newLevelDialog != nullptr)
    {
        impl->newLevelDialog.reset();
    }
}

/**
 *
 */
void LevelEditorController::updateLevelNameSurfacePosition() &
{
    /* set the position once the surface is created because we need the surface
       width to find the surface horizontal position */
    impl->levelNameSurface.setPosition(
        1200.f - impl->levelNameSurface.getLocalBounds().width,
        0.f
    );
}

/**
 *
 */
void LevelEditorController::saveLevelFile(
    const std::string& name,
    aliases::ConstUniquePtrCellsContainerRef cells
) const &
{
    std::ofstream file;
    utils::applyFailbitAndBadbitExceptions(file);

    file.open(
        "data/levels/" + name + ".level",
        std::fstream::out
    );

    /* string representation of the cells */
    std::string cellsStr;

    for (
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator iterator =
            cells.begin();
        iterator != cells.end();
        iterator++
    )
    {
        cellsStr += (*iterator)->getType();
    }

    file << cellsStr;

    /* manually close the file is not necessary as std::ofstream is
       automatically destroyed when it leaves the current scope */
}

}
}
