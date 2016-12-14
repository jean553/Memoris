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
#include "EditingLevelManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "Cell.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

using Action = utils::EditorDashboard::Action;

class LevelEditorController::Impl
{

public:

    Impl(
        const utils::Context& context,
        Level levelPtr
    ) :
        dashboard(context),
        selector(context),
        level(std::move(levelPtr)),
        cursor(context)
    {
        std::string levelName =
            context.getEditingLevelManager().getLevelName().empty() ?
            "unnamed" :
            context.getEditingLevelManager().getLevelName();

        levelNameSurface.setString(levelName);
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

    /* use a pointer here for two reasons: this is faster to copy from one
       method to another, especially after creation into controllers.cpp; we
       have no other choice that creating the Level object into controllers.cpp
       and we still want access it into the controller, so we can not use a
       simple Level reference as the original object would be destroyed */
    std::unique_ptr<entities::Level> level;

    unsigned short floor {0};

    Action currentActionId {Action::EXIT};

    widgets::Cursor cursor;

    sf::Text levelNameSurface;
    sf::Text floorSurface;

    std::unique_ptr<popups::SaveLevelDialog> saveLevelDialog {nullptr};
};

/**
 *
 */
LevelEditorController::LevelEditorController(
    const utils::Context& context,
    Level level
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            std::move(level)
        )
    )
{
}

/**
 *
 */
LevelEditorController::~LevelEditorController() noexcept = default;

/**
 *
 */
const unsigned short& LevelEditorController::render(
    const utils::Context& context
) &
{
    impl->dashboard.display(context);

    impl->level->display(
        context,
        impl->floor,
        &entities::Cell::displayWithMouseHover
    );

    impl->selector.display(context);

    window.draw(impl->levelNameSurface);
    window.draw(impl->floorSurface);

    if (impl->saveLevelDialog != nullptr)
    {
        impl->saveLevelDialog->render(context);
    }

    impl->cursor.render(context);

    nextControllerId = animateScreenTransition(context);

    while(window.pollEvent(event))
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
                    if (impl->saveLevelDialog->getInputTextWidget().isEmpty())
                    {
                        break;
                    }

                    const std::string levelName =
                        impl->saveLevelDialog->getInputTextWidget().getText();

                    impl->levelNameSurface.setString(levelName);

                    saveLevelFile(
                        levelName,
                        impl->level->getCells()
                    );

                    context.getEditingLevelManager().setLevelName(levelName);

                    updateLevelNameSurfacePosition();

                    deleteActiveDialog();
                }
            }
            default:
            {
                if (saveDialogIsActive())
                {
                    impl->saveLevelDialog->getInputTextWidget().update(event);
                }
            }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            switch(impl->dashboard.getActionIdBySelectedButton())
            {
            case Action::EXIT:
            {
                context.getEditingLevelManager().setLevelName("");

                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

                break;
            }
            case Action::SAVE:
            {
                std::string levelName =
                    context.getEditingLevelManager().getLevelName();

                if (
                    !levelName.empty() &&
                    impl->levelNameSurface.getString()
                    .toAnsiString().back() == '*'
                )
                {
                    saveLevelFile(
                        levelName,
                        impl->level->getCells()
                    );

                    /* remove the asterisk at the end of the displayed level
                       name */
                    impl->levelNameSurface.setString(levelName);

                    updateLevelNameSurfacePosition();

                    break;
                }

                impl->saveLevelDialog =
                    std::make_unique<popups::SaveLevelDialog>(context);

                impl->currentActionId = Action::SAVE;

                break;
            }
            case Action::NEW:
            {
                break;
            }
            case Action::OPEN:
            {
                expectedControllerId = OPEN_LEVEL_CONTROLLER_ID;

                break;
            }
            case Action::UP:
            {
                if (impl->floor != entities::Level::MAX_FLOOR)
                {
                    impl->floor++;

                    impl->floorSurface.setString(
                        std::to_string(
                            impl->floor + 1
                        )
                    );
                }

                break;
            }
            case Action::DOWN:
            {
                if (impl->floor != entities::Level::MIN_FLOOR)
                {
                    impl->floor--;

                    impl->floorSurface.setString(
                        std::to_string(
                            impl->floor + 1
                        )
                    );
                }

                break;
            }
            default:
            {
            }
            }

            impl->selector.selectCell(context);

            if(
                impl->level->updateSelectedCellType(
                    context,
                    impl->floor,
                    impl->selector.getSelectedCellType()
                ) &&
                impl->levelNameSurface.getString().toAnsiString().back() != '*'
            )
            {
                impl->levelNameSurface.setString(
                    impl->levelNameSurface.getString() + "*"
                );

                updateLevelNameSurfacePosition();
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
const bool LevelEditorController::saveDialogIsActive() const & noexcept
{
    if (
        impl->currentActionId ==
        Action::SAVE &&
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
void LevelEditorController::deleteActiveDialog() & noexcept
{
    if (impl->saveLevelDialog != nullptr)
    {
        impl->saveLevelDialog.reset();
    }
}

/**
 *
 */
void LevelEditorController::updateLevelNameSurfacePosition() &
{
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
        "data/levels/personals/" + name + ".level",
        std::fstream::out
    );

    std::string cellsStr;

    cellsStr += std::to_string(impl->level->getMinutes()) + '\n';
    cellsStr += std::to_string(impl->level->getSeconds()) + '\n';

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
}

}
}
