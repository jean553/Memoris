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
#include "EditingLevelManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "Cell.hpp"
#include "NewLevelForeground.hpp"
#include "OpenLevelForeground.hpp"
#include "SaveLevelForeground.hpp"
#include "SelectionListWidget.hpp"

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
            UNNAMED_LEVEL :
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

    std::unique_ptr<foregrounds::NewLevelForeground>
        newLevelForeground {nullptr};

    std::unique_ptr<foregrounds::OpenLevelForeground>
        openLevelForeground {nullptr};

    std::unique_ptr<foregrounds::SaveLevelForeground>
        saveLevelForeground {nullptr};

    bool newFile {false};
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
    // std::unique_ptr<Level>&
    auto& level = impl->level;

    // std::unique_ptr<NewLevelForeground>&
    auto& newLevelForeground = impl->newLevelForeground;
    auto& openLevelForeground = impl->openLevelForeground;
    auto& saveLevelForeground = impl->saveLevelForeground;

    auto& levelNameSurface = impl->levelNameSurface;

    auto& newFile = impl->newFile;

    if (newLevelForeground != nullptr)
    {
        newLevelForeground->render(context);
    }
    else if (openLevelForeground != nullptr)
    {
        openLevelForeground->render(context);
    }
    else if (saveLevelForeground != nullptr)
    {
        saveLevelForeground->render(context);
    }
    else
    {
        impl->dashboard.display(context);
        impl->selector.display(context);

        level->display(
            context,
            impl->floor,
            &entities::Cell::displayWithMouseHover
        );

        window.draw(levelNameSurface);
        window.draw(impl->floorSurface);

        impl->cursor.render(context);
    }

    nextControllerId = animateScreenTransition(context);

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Y:
            {
                if (newLevelForeground != nullptr)
                {
                    level->refresh(context);

                    newLevelForeground.reset();

                    changeLevelName(
                        context,
                        UNNAMED_LEVEL
                    );

                    newFile = false;
                }

                break;
            }
            case sf::Keyboard::N:
            {
                if (newLevelForeground != nullptr)
                {
                    newLevelForeground.reset();
                }

                break;
            }
            case sf::Keyboard::Escape:
            {
                if (openLevelForeground != nullptr)
                {
                    openLevelForeground.reset();
                }
                else if (saveLevelForeground != nullptr)
                {
                    saveLevelForeground.reset();
                }

                break;
            }
            case sf::Keyboard::Return:
            {
                if (saveLevelForeground != nullptr)
                {
                    const std::string& levelName =
                        saveLevelForeground->getInputTextWidget().getText();

                    if (levelName.empty())
                    {
                        break;
                    }

                    saveLevelFile(
                        levelName,
                        level->getCells()
                    );

                    changeLevelName(
                        context,
                        levelName
                    );

                    saveLevelForeground.reset();
                }
            }
            default:
            {
                if (saveLevelForeground != nullptr)
                {
                    saveLevelForeground->getInputTextWidget().update(event);
                }
            }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (openLevelForeground != nullptr)
            {
                const auto& list = openLevelForeground->getList();
                const auto levelName = list.getCurrentItem();

                if (!levelName.empty())
                {
                    /* TODO: #972 can throw a std::invalid_argument exception,
                       should be handled as well */
                    impl->level.reset(
                        new entities::Level(
                            context,
                            "data/levels/personals/" + levelName + ".level"
                        )
                    );

                    openLevelForeground.reset();

                    changeLevelName(
                        context,
                        levelName
                    );

                    break;
                }

                openLevelForeground->getList().updateList();

                break;
            }

            /* the mouse is not used if a foreground is displayed */
            if (newLevelForeground != nullptr)
            {
                break;
            }

            switch(impl->dashboard.getActionIdBySelectedButton())
            {
            case Action::NEW:
            {
                impl->newLevelForeground =
                    std::make_unique<foregrounds::NewLevelForeground>(context);

                break;
            }
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

                const bool updatedLevel =
                    levelNameSurface.getString().toAnsiString().back() == '*';

                /* if the level is not saved yet,
                   a star is displayed after the name */
                if ((not levelName.empty() and updatedLevel) or newFile)
                {
                    saveLevelFile(
                        levelName,
                        level->getCells()
                    );

                    /* remove the asterisk at the end
                       of the displayed level name */
                    levelNameSurface.setString(levelName);

                    updateLevelNameSurfacePosition();

                    break;
                }

                saveLevelForeground =
                    std::make_unique<foregrounds::SaveLevelForeground>(
                        context
                    );

                newFile = true;

                impl->currentActionId = Action::SAVE;

                break;
            }
            case Action::OPEN:
            {
                impl->openLevelForeground =
                    std::make_unique<foregrounds::OpenLevelForeground>(
                        context
                    );

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
                level->updateSelectedCellType(
                    context,
                    impl->floor,
                    impl->selector.getSelectedCellType()
                ) &&
                levelNameSurface.getString().toAnsiString().back() != '*'
            )
            {
                levelNameSurface.setString(
                    levelNameSurface.getString() + "*"
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
void LevelEditorController::updateLevelNameSurfacePosition() const &
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

/**
 *
 */
void LevelEditorController::changeLevelName(
    const utils::Context& context,
    const std::string& levelName
) const &
{
    impl->levelNameSurface.setString(levelName);

    context.getEditingLevelManager().setLevelName(
        levelName
    );

    updateLevelNameSurfacePosition();
}

}
}
