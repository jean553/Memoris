/**
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelEditorController.hpp"

#include "controllers_ids.hpp"
#include "fonts_sizes.hpp"
#include "InputTextWidget.hpp"
#include "EditorDashboard.hpp"
#include "CellsSelector.hpp"
#include "Level.hpp"
#include "Cursor.hpp"
#include "EditingLevelManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "Cell.hpp"
#include "MessageForeground.hpp"
#include "InputTextForeground.hpp"
#include "PlayingSerieManager.hpp"
#include "cells.hpp"

#include <fstream>

namespace memoris
{
namespace controllers
{

constexpr const char* UNNAMED_LEVEL {"unnamed"};

constexpr float TITLES_HORIZONTAL_POSITION {1200.f};

constexpr unsigned short MIN_FLOOR {0};
constexpr unsigned short MAX_FLOOR {9};

class LevelEditorController::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& levelPtr,
        const bool& tested
    ) :
        dashboard(context),
        selector(context),
        level(levelPtr),
        cursor(context),
        tested(tested)
    {
        const auto& name = context.getEditingLevelManager().getLevelName();
        const auto& font = context.getFontsManager().getTextFont();
        const auto& colorsManager = context.getColorsManager();
        const auto& white = colorsManager.getColorWhite();

        std::string levelName = name.empty() ? UNNAMED_LEVEL : name;

        constexpr float LEVEL_NAME_SURFACE_VERTICAL_POSITION {0.f};
        levelNameSurface.setString(levelName);
        levelNameSurface.setFont(font);
        levelNameSurface.setFillColor(white);
        levelNameSurface.setCharacterSize(sizes::TEXT_SIZE);
        levelNameSurface.setPosition(
            TITLES_HORIZONTAL_POSITION -
                levelNameSurface.getLocalBounds().width,
            LEVEL_NAME_SURFACE_VERTICAL_POSITION
        );

        constexpr float FLOOR_SURFACE_HORIZONTAL_POSITION {1240.f};
        constexpr float FLOOR_SURFACE_VERTICAL_POSITION {450.f};
        floorSurface.setFont(font);
        floorSurface.setFillColor(white);
        floorSurface.setCharacterSize(sizes::TEXT_SIZE);
        floorSurface.setString("1");
        floorSurface.setPosition(
            FLOOR_SURFACE_HORIZONTAL_POSITION,
            FLOOR_SURFACE_VERTICAL_POSITION
        );

        if (tested)
        {
            testedTime.setFillColor(white);
            testedTime.setString(
                context.getPlayingSerieManager().getPlayingTimeAsString()
            );
        }
        else
        {
            testedTime.setFillColor(colorsManager.getColorRed());
            testedTime.setString("Not tested yet");
        }

        testedTime.setFont(font);
        testedTime.setCharacterSize(sizes::TEXT_SIZE);

        constexpr float TESTED_TIME_VERTICAL_POSITION {40.f};
        testedTime.setPosition(
            TITLES_HORIZONTAL_POSITION - testedTime.getLocalBounds().width,
            TESTED_TIME_VERTICAL_POSITION
        );

        /* if the previous controller was the game controller, so some cells
           have been hidden during the game; this function is useless when
           the editor is loaded from the menu */
        level->showAllCells();

        constexpr float CELLS_DEFAULT_TRANSPARENCY {255.f};
        constexpr unsigned short FIRST_FLOOR_INDEX {0};
        level->setCellsTransparency(
            CELLS_DEFAULT_TRANSPARENCY,
            FIRST_FLOOR_INDEX
        );
    }

    utils::EditorDashboard dashboard;

    utils::CellsSelector selector;

    /* use a pointer here for two reasons: this is faster to copy from one
       method to another, especially after creation into controllers.cpp; we
       have no other choice that creating the Level object into controllers.cpp
       and we still want access it into the controller, so we can not use a
       simple Level reference as the original object would be destroyed */
    std::shared_ptr<entities::Level> level;

    unsigned short floor {0};

    widgets::Cursor cursor;

    sf::Text levelNameSurface;
    sf::Text floorSurface;
    sf::Text testedTime;

    std::unique_ptr<foregrounds::MessageForeground>
        newLevelForeground {nullptr};

    std::unique_ptr<foregrounds::InputTextForeground>
        saveLevelForeground {nullptr};

    bool newFile {false};
    bool tested {false};
};

/**
 *
 */
LevelEditorController::LevelEditorController(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const bool& tested
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            level,
            tested
        )
    )
{
}

/**
 *
 */
LevelEditorController::~LevelEditorController() = default;

/**
 *
 */
const ControllerId& LevelEditorController::render() const &
{
    auto& newLevelForeground = impl->newLevelForeground;
    auto& saveLevelForeground = impl->saveLevelForeground;

    const auto& context = getContext();

    if (newLevelForeground != nullptr)
    {
        newLevelForeground->render();

        handleNewLevelForegroundEvents();
    }
    else if (saveLevelForeground != nullptr)
    {
        saveLevelForeground->render();

        handleSaveLevelForegroundEvents();
    }
    else
    {
        renderControllerMainComponents();

        setNextControllerId(animateScreenTransition(context));

        handleControllerEvents();
    }

    return getNextControllerId();
}

/**
 *
 */
void LevelEditorController::updateLevelNameSurfacePosition() const &
{
    constexpr float LEVEL_NAME_SURFACE_BASE_HORIZONTAL_POSITION {1200.f};
    constexpr float LEVEL_NAME_SURFACE_VERTICAL_POSITION {0.f};
    impl->levelNameSurface.setPosition(
        LEVEL_NAME_SURFACE_BASE_HORIZONTAL_POSITION - 
            impl->levelNameSurface.getLocalBounds().width,
        LEVEL_NAME_SURFACE_VERTICAL_POSITION
    );
}

/**
 *
 */
void LevelEditorController::saveLevelFile(
    const std::string& name,
    const std::vector<std::unique_ptr<entities::Cell>>& cells
) const &
{
    std::ofstream file;

    file.open(
        "data/levels/personals/" + name + ".level",
        std::fstream::out
    );

    std::string cellsStr;

    cellsStr += std::to_string(impl->level->getMinutes()) + '\n';
    cellsStr += std::to_string(impl->level->getSeconds()) + '\n';

    for (
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator iterator =
            cells.cbegin();
        iterator != cells.cend();
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
void LevelEditorController::changeLevelName(const std::string& levelName)
    const &
{
    impl->levelNameSurface.setString(levelName);

    getContext().getEditingLevelManager().setLevelName(
        levelName
    );

    updateLevelNameSurfacePosition();
}

/**
 *
 */
void LevelEditorController::renderControllerMainComponents() const &
{
    const auto& cursorPosition = impl->cursor.getPosition();
    impl->dashboard.display(cursorPosition);

    impl->selector.display();

    const auto& context = getContext();

    impl->level->display(impl->floor);

    auto& window = context.getSfmlWindow();
    window.draw(impl->levelNameSurface);
    window.draw(impl->floorSurface);
    window.draw(impl->testedTime);

    impl->cursor.render();
}

/**
 *
 */
void LevelEditorController::handleNewLevelForegroundEvents() const &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();
    auto& event = getEvent();
    auto& newLevelForeground = impl->newLevelForeground;

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
                newLevelForeground.reset();

                break;
            }
            case sf::Keyboard::Return:
            {
                impl->level->allCellsAsWalls();

                changeLevelName(UNNAMED_LEVEL);

                newLevelForeground.reset();

                break;
            }
            default:
            {
                break;
            }
            }
        }
        default:
        {
            break;
        }
        }
    }
}

/**
 *
 */
void LevelEditorController::handleSaveLevelForegroundEvents() const &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();
    auto& event = getEvent();
    auto& saveLevelForeground = impl->saveLevelForeground;

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
                saveLevelForeground.reset();

                break;
            }
            case sf::Keyboard::Return:
            {
                const auto& levelName =
                    saveLevelForeground->getInputTextWidget().getText()
                        .toAnsiString();

                if (levelName.empty())
                {
                    break;
                }

                saveLevelFile(
                    levelName,
                    impl->level->getCells()
                );

                changeLevelName(levelName);

                saveLevelForeground.reset();

                break;
            }
            default:
            {
                auto& textInput = saveLevelForeground->getInputTextWidget();

                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    textInput.empty();

                    break;
                }

                if (textInput.isFull())
                {
                    break;
                }

                const char character = textInput.getInputLetter(event);

                if(character != 0)
                {
                    textInput.update(character);
                }

                break;
            }
            }
        }
        default:
        {
            break;
        }
        }
    }
}

/**
 *
 */
void LevelEditorController::handleControllerEvents() const &
{
    auto& level = impl->level;
    auto& newFile = impl->newFile;
    auto& levelNameSurface = impl->levelNameSurface;

    const auto& context = getContext();
    auto& window = context.getSfmlWindow();
    auto& event = getEvent();

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::MouseButtonPressed:
        {
            const auto displayedName =
                levelNameSurface.getString().toAnsiString();

            using Action = utils::EditorDashboard::Action;

            switch(impl->dashboard.getActionIdBySelectedButton())
            {
            case Action::NEW:
            {
                openNewLevelForeground();

                break;
            }
            case Action::EXIT:
            {
                resetLevel();

                setExpectedControllerId(ControllerId::EditorMenu);

                break;
            }
            case Action::SAVE:
            {
                if (not impl->tested)
                {
                    break;
                }

                std::string levelName =
                    context.getEditingLevelManager().getLevelName();

                if (
                    newFile or
                    (
                        not levelName.empty() and
                        displayedName.back() == '*'
                    )
                )
                {
                    saveLevel(levelName);

                    break;
                }

                openSaveLevelForeground();

                newFile = true;

                break;
            }
            case Action::UP:
            {
                if (impl->floor != MAX_FLOOR)
                {
                    updateFloor(1);
                }

                break;
            }
            case Action::DOWN:
            {
                if (impl->floor != MIN_FLOOR)
                {
                    updateFloor(-1);
                }

                break;
            }
            case Action::PLAY:
            {
                if (not level->hasOneDepartureAndOneArrival())
                {
                    break;
                }

                testLevel();

                setExpectedControllerId(ControllerId::Game);

                break;
            }
            default:
            {
                break;
            }
            }

            /* TODO: #1264 these two method names are not explicit enough;
               these two conditions have to be reworked */

            if(cellIsSelectedFromCellsSelector())
            {
                impl->selector.selectMouseHoverCell();
            }

            if(lastLevelVersionUpdated())
            {
                markLevelHasToBeSaved();
            }
        }
        default:
        {
            break;
        }
        }
    }
}

/**
 *
 */
void LevelEditorController::updateFloor(const short& movement) const &
{
    auto& floor = impl->floor;
    floor += movement;

    impl->floorSurface.setString(
        std::to_string(
            floor + 1
        )
    );
}

/**
 *
 */
void LevelEditorController::openNewLevelForeground() const &
{
    constexpr const char* ERASE_LEVEL_MESSAGE
        {"Erase the current level ? y / n"};

    impl->newLevelForeground =
        std::make_unique<foregrounds::MessageForeground>(
            getContext(),
            ERASE_LEVEL_MESSAGE
        );
}

/**
 *
 */
void LevelEditorController::openSaveLevelForeground() const &
{
    constexpr const char* SAVE_LEVEL_NAME_MESSAGE {"Level name"};

    impl->saveLevelForeground =
        std::make_unique<foregrounds::InputTextForeground>(
            getContext(),
            SAVE_LEVEL_NAME_MESSAGE
        );
}

/**
 *
 */
void LevelEditorController::resetLevel() const &
{
    auto& levelManager = getContext().getEditingLevelManager();
    levelManager.setLevelName("");
    levelManager.setLevel(nullptr);
    levelManager.refreshLevel();
}

/**
 *
 */
void LevelEditorController::saveLevel(const std::string& levelName) const &
{
    saveLevelFile(
        levelName,
        impl->level->getCells()
    );

    impl->levelNameSurface.setString(levelName);

    updateLevelNameSurfacePosition();
}

/**
 *
 */
void LevelEditorController::testLevel() const &
{
    auto& level = impl->level;
    const auto& context = getContext();
    auto& levelManager = getContext().getEditingLevelManager();

    level->initializeEditedLevel();

    levelManager.setLevel(level);
    levelManager.setCellsBackup(
        level->getCharactersList()
    );

    context.getPlayingSerieManager().reinitialize();
}

/**
 *
 */
const bool LevelEditorController::cellIsSelectedFromCellsSelector() const &
{
    const auto& selector = impl->selector;
    const auto mouseHoverCellType = selector.getMouseHoverCellType();

    if (
        selector.getSelectedCellType() != mouseHoverCellType and
        mouseHoverCellType != cells::NO_CELL
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
const bool LevelEditorController::lastLevelVersionUpdated() const &
{
    if(
        not impl->level->updateSelectedCellType(
            impl->floor,
            impl->selector.getSelectedCellType()
        )
    )
    {
        return false;
    }

    const auto displayedName =
        impl->levelNameSurface.getString().toAnsiString();

    /* two ifs in order to prevent expensive string copy;
       this method is called everytime the mouse moves */
    if (
        displayedName.back() != '*' and
        displayedName != UNNAMED_LEVEL
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void LevelEditorController::markLevelHasToBeSaved() const &
{
    auto& levelNameSurface = impl->levelNameSurface;

    levelNameSurface.setString(
        levelNameSurface.getString() + "*"
    );

    updateLevelNameSurfacePosition();
}

}
}
