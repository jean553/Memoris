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
 * @file SerieEditorController.hpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SerieEditorController.hpp"

#include "controllers_ids.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "TexturesManager.hpp"
#include "Context.hpp"
#include "fonts_sizes.hpp"
#include "Button.hpp"
#include "Cursor.hpp"
#include "FilesSelectionListWidget.hpp"
#include "InputTextForeground.hpp"
#include "MessageForeground.hpp"
#include "InputTextWidget.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <fstream>

namespace memoris
{
namespace controllers
{

constexpr float BUTTONS_VERTICAL_POSITION {10.f};
constexpr float NEW_BUTTON_HORIZONTAL_POSITION {10.f};
constexpr float SAVE_BUTTON_HORIZONTAL_POSITION {90.f};
constexpr float EXIT_BUTTON_HORIZONTAL_POSITION {170.f};
constexpr float ALL_LEVELS_LIST_HORIZONTAL_POSITION {100.f};
constexpr float SERIE_LEVELS_LIST_HORIZONTAL_POSITION {890.f};

constexpr const char* UNTITLED_SERIE {"untitled"};

class SerieEditorController::Impl
{

public:

    Impl(const utils::Context& context) : 
        buttonNew(
            context,
            NEW_BUTTON_HORIZONTAL_POSITION,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getNewTexture()
        ),
        buttonSave(
            context,
            SAVE_BUTTON_HORIZONTAL_POSITION,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getSaveTexture()
        ),
        buttonExit(
            context,
            EXIT_BUTTON_HORIZONTAL_POSITION,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getExitTexture()
        ),
        cursor(context),
        filesLevelsList(
            context,
            "data/levels/personals",
            ALL_LEVELS_LIST_HORIZONTAL_POSITION
        ),
        serieLevelsList(
            context,
            SERIE_LEVELS_LIST_HORIZONTAL_POSITION
        )
    {
        serieNameText.setString(UNTITLED_SERIE);
        serieNameText.setFont(context.getFontsManager().getTextFont());
        serieNameText.setFillColor(context.getColorsManager().getColorWhite());
        serieNameText.setCharacterSize(sizes::TEXT_SIZE);

        constexpr float SERIE_NAME_TEXT_HORIZONTAL_BASE {1550.f};
        constexpr float SERIE_NAME_TEXT_VERTICAL_POSITION {0.f};
        serieNameText.setPosition(
            SERIE_NAME_TEXT_HORIZONTAL_BASE -
                serieNameText.getLocalBounds().width,
            SERIE_NAME_TEXT_VERTICAL_POSITION
        );
    }

    sf::Text serieNameText;

    widgets::Button buttonNew;
    widgets::Button buttonSave;
    widgets::Button buttonExit;

    widgets::Cursor cursor;

    widgets::FilesSelectionListWidget filesLevelsList;
    widgets::SelectionListWidget serieLevelsList;

    std::unique_ptr<foregrounds::InputTextForeground> saveSerieForeground
        {nullptr};

    std::unique_ptr<foregrounds::MessageForeground> newSerieForeground
        {nullptr};

    std::string serieName;
};

/**
 *
 */
SerieEditorController::SerieEditorController(const utils::Context& context) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
SerieEditorController::~SerieEditorController() = default;

/**
 *
 */
const ControllerId& SerieEditorController::render() const &
{
    auto& saveSerieForeground = impl->saveSerieForeground;
    auto& newSerieForeground = impl->newSerieForeground;

    if (newSerieForeground != nullptr)
    {
        newSerieForeground->render();

        handleNewSerieForegroundEvents();
    }
    else if (saveSerieForeground != nullptr)
    {
        saveSerieForeground->render();

        handleSaveSerieForegroundEvents();
    }
    else
    {
        renderControllerMainComponents();

        setNextControllerId(animateScreenTransition(getContext()));

        handleControllerEvents();
    }

    return getNextControllerId();
}

/**
 *
 */
void SerieEditorController::renderControllerMainComponents() const &
{
    getContext().getSfmlWindow().draw(impl->serieNameText);

    const auto& cursor = impl->cursor;
    const auto& cursorPosition = cursor.getPosition();

    impl->buttonNew.display(cursorPosition);
    impl->buttonSave.display(cursorPosition);
    impl->buttonExit.display(cursorPosition);
    impl->filesLevelsList.display(cursorPosition);
    impl->serieLevelsList.display(cursorPosition);

    cursor.render();
}

/**
 *
 */
void SerieEditorController::handleNewSerieForegroundEvents() const &
{
    auto& event = getEvent();
    auto& window = getContext().getSfmlWindow();

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
            {
                resetLevelsLists();

                updateSerieName(UNTITLED_SERIE);

                break;
            }
            case sf::Keyboard::Escape:
            {
                impl->newSerieForeground.reset();

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
void SerieEditorController::handleSaveSerieForegroundEvents() const &
{
    auto& saveSerieForeground = impl->saveSerieForeground;
    auto& event = getEvent();
    auto& window = getContext().getSfmlWindow();

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
            {
                const auto& serieName =
                    saveSerieForeground->getInputTextWidget().getText()
                        .toAnsiString();

                if (
                    serieName.empty() or
                    serieName == UNTITLED_SERIE
                )
                {
                    break;
                }

                saveSerieFile(serieName);

                updateSerieName(serieName);

                impl->serieName = serieName;

                saveSerieForeground.reset();

                break;
            }
            case sf::Keyboard::Escape:
            {
                saveSerieForeground.reset();

                break;
            }
            default:
            {
                const auto& textInput = 
                    saveSerieForeground->getInputTextWidget();

                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    textInput.empty();
                }

                if(textInput.isFull())
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
void SerieEditorController::handleControllerEvents() const &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();
    auto& event = getEvent();

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
                setExpectedControllerId(ControllerId::EditorMenu);

                break;
            }
            default:
            {
                break;
            }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (impl->buttonExit.isMouseHover())
            {
                setExpectedControllerId(ControllerId::EditorMenu);
            }
            else if (impl->buttonNew.isMouseHover())
            {
                openNewSerieForeground();
            }
            else if (impl->buttonSave.isMouseHover())
            {
                auto serieNameText =
                    impl->serieNameText.getString().toAnsiString();

                if (
                    serieNameText != UNTITLED_SERIE and
                    serieNameText.back() == '*'
                )
                {
                    const auto& serieName = impl->serieName;

                    saveSerieFile(serieName);

                    updateSerieName(serieName);

                    break;
                }

                openSaveSerieForeground();
            }

            const auto& allLevelsList = impl->filesLevelsList;
            const auto& serieLevelsList = impl->serieLevelsList;

            const auto& allLevelsIndex = allLevelsList.getCurrentIndex();
            const auto& serieLevelsIndex = serieLevelsList.getCurrentIndex();

            constexpr short NO_SELECTION_INDEX =
                widgets::SelectionListWidget::NO_SELECTION_INDEX;

            if (
                allLevelsIndex < allLevelsList.getItemsAmount() and
                allLevelsIndex != NO_SELECTION_INDEX
            )
            {
                serieLevelsList.addItem(allLevelsList.getCurrentItem());

                allLevelsList.deleteSelectedItem();

                markSerieUnsaved();
            }
            else if (
                serieLevelsIndex < serieLevelsList.getItemsAmount() and
                serieLevelsIndex != NO_SELECTION_INDEX
            )
            {
                allLevelsList.addItem(serieLevelsList.getCurrentItem());

                serieLevelsList.deleteSelectedItem();

                markSerieUnsaved();
            }

            using ListMovement = widgets::SelectionListWidget::ListMovement;

            if (allLevelsList.canScrollUp())
            {
                allLevelsList.updateAllItemsPosition(ListMovement::Up);
            }
            else if (allLevelsList.canScrollDown())
            {
                allLevelsList.updateAllItemsPosition(ListMovement::Down);
            }

            if (serieLevelsList.canScrollUp())
            {
                serieLevelsList.updateAllItemsPosition(ListMovement::Up);
            }
            else if (serieLevelsList.canScrollDown())
            {
                serieLevelsList.updateAllItemsPosition(ListMovement::Down);
            }

            break;
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
void SerieEditorController::saveSerieFile(const std::string& name) const &
{
    std::ofstream file;

    file.open(
        "data/series/personals/" + name + ".serie",
        std::fstream::out
    );

    /* write three empty best scores */
    file << "." << std::endl << "." << std::endl << "." << std::endl;

    const auto& texts = impl->serieLevelsList.getTexts();

    for (const auto& text : texts)
    {
        file << text.getString().toAnsiString() << std::endl;
    }
}

/**
 *
 */
void SerieEditorController::markSerieUnsaved() const &
{
    auto& serieNameTextSurface = impl->serieNameText;

    auto serieNameText = serieNameTextSurface.getString().toAnsiString();

    if (
        serieNameText.back() == '*' or
        serieNameText == UNTITLED_SERIE
    )
    {
        return;
    }

    serieNameTextSurface.setString(serieNameText + "*");

    updateSerieNamePosition();
}

/**
 *
 */
void SerieEditorController::updateSerieNamePosition() const &
{
    auto& serieNameText = impl->serieNameText;

    constexpr float SERIE_NAME_TEXT_VERTICAL_POSITION {0.f};
    serieNameText.setPosition(
        window::WIDTH -
            serieNameText.getLocalBounds().width,
        SERIE_NAME_TEXT_VERTICAL_POSITION
    );
}

/**
 *
 */
void SerieEditorController::resetLevelsLists() const &
{
    impl->serieLevelsList.deleteAllItems();

    const auto& filesLevelsList = impl->filesLevelsList;
    filesLevelsList.deleteAllItems();
    filesLevelsList.loadFilesFromDirectory();
}

/**
 *
 */
void SerieEditorController::updateSerieName(const std::string& name) const &
{
    impl->serieNameText.setString(UNTITLED_SERIE);

    updateSerieNamePosition();
}

/**
 *
 */
void SerieEditorController::openNewSerieForeground() const &
{
    constexpr const char* ERASE_SERIE_MESSAGE
        {"Erase the current serie ? y / n"};

    impl->newSerieForeground =
        std::make_unique<foregrounds::MessageForeground>(
            getContext(),
            ERASE_SERIE_MESSAGE
        );
}

/**
 *
 */
void SerieEditorController::openSaveSerieForeground() const &
{
    constexpr const char* SAVE_SERIE_MESSAGE {"Save serie"};
    impl->saveSerieForeground =
        std::make_unique<foregrounds::InputTextForeground>(
            getContext(),
            SAVE_SERIE_MESSAGE
        );
}

}
}
