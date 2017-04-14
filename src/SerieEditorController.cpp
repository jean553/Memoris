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
#include "controllers.hpp"
#include "fonts_sizes.hpp"
#include "Button.hpp"
#include "Cursor.hpp"
#include "DoubleSelectionListWidget.hpp"
#include "SelectionListWidget.hpp"
#include "InputTextForeground.hpp"
#include "MessageForeground.hpp"
#include "InputTextWidget.hpp"
#include "window.hpp"
#include "files.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

constexpr float SerieEditorController::BUTTONS_VERTICAL_POSITION;

constexpr const char* SerieEditorController::SAVE_SERIE_MESSAGE;
constexpr const char* SerieEditorController::UNTITLED_SERIE;
constexpr const char* SerieEditorController::ERASE_SERIE_MESSAGE;

class SerieEditorController::Impl
{

public:

    Impl(const utils::Context& context) : 
        buttonNew(
            context,
            10.f,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getNewTexture()
        ),
        buttonSave(
            context,
            90.f,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getSaveTexture()
        ),
        buttonExit(
            context,
            170.f,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getExitTexture()
        ),
        cursor(context),
        lists(context)
    {
        serieNameText.setString(UNTITLED_SERIE);
        serieNameText.setFont(context.getFontsManager().getTextFont());
        serieNameText.setFillColor(context.getColorsManager().getColorWhite());
        serieNameText.setCharacterSize(sizes::TEXT_SIZE);
        serieNameText.setPosition(
            1550.f - serieNameText.getLocalBounds().width,
            0.f
        );

        allLevels.setString("Available levels");
        allLevels.setFont(context.getFontsManager().getTextFont());
        allLevels.setFillColor(context.getColorsManager().getColorWhite());
        allLevels.setCharacterSize(sizes::TEXT_SIZE);
        allLevels.setPosition(
            230.f,
            INFORMATION_VERTICAL_POSITION
        );

        serieLevels.setString("Serie levels");
        serieLevels.setFont(context.getFontsManager().getTextFont());
        serieLevels.setFillColor(context.getColorsManager().getColorWhite());
        serieLevels.setCharacterSize(sizes::TEXT_SIZE);
        serieLevels.setPosition(
            1080.f,
            INFORMATION_VERTICAL_POSITION
        );

        explanations.setString(
            "Click on a level name in order to switch it from one list to "
            "another."
        );
        explanations.setFont(context.getFontsManager().getTextFont());
        explanations.setFillColor(context.getColorsManager().getColorWhite());
        explanations.setCharacterSize(sizes::TEXT_SIZE);
        explanations.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(explanations),
            850.f
        );
    }

    sf::Text serieNameText;
    sf::Text allLevels;
    sf::Text serieLevels;
    sf::Text explanations;

    widgets::Button buttonNew;
    widgets::Button buttonSave;
    widgets::Button buttonExit;

    widgets::Cursor cursor;

    widgets::DoubleSelectionListWidget lists;

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
SerieEditorController::~SerieEditorController() noexcept = default;

/**
 *
 */
const ControllerId& SerieEditorController::render() const &
{
    auto& saveSerieForeground = impl->saveSerieForeground;
    auto& newSerieForeground = impl->newSerieForeground;

    const auto& context = getContext();

    if (saveSerieForeground != nullptr)
    {
        saveSerieForeground->render(context);
    }
    else if (newSerieForeground != nullptr)
    {
        newSerieForeground->render(context);
    }
    else
    {
        context.getSfmlWindow().draw(impl->serieNameText);
        context.getSfmlWindow().draw(impl->allLevels);
        context.getSfmlWindow().draw(impl->serieLevels);
        context.getSfmlWindow().draw(impl->explanations);

        auto& cursor = impl->cursor;
        const auto& cursorPosition = cursor.getPosition();

        impl->buttonNew.display(cursorPosition);
        impl->buttonSave.display(cursorPosition);
        impl->buttonExit.display(cursorPosition);

        impl->lists.display(
            context,
            cursorPosition
        );

        cursor.render();
    }

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
            {
                if (newSerieForeground != nullptr)
                {
                    impl->lists.resetLists(context);

                    impl->serieNameText.setString(UNTITLED_SERIE);

                    updateSerieNamePosition();
                }
                else if (saveSerieForeground != nullptr)
                {
                    // const std::string&
                    const auto& serieNameText =
                        saveSerieForeground->getInputTextWidget().getText()
                            .toAnsiString();

                    if (
                        serieNameText.empty() or
                        serieNameText == UNTITLED_SERIE
                    )
                    {
                        break;
                    }

                    saveSerieFile(serieNameText);

                    impl->serieNameText.setString(serieNameText);

                    updateSerieNamePosition();

                    impl->serieName = serieNameText;

                    saveSerieForeground.reset();

                    break;
                }
            }
            case sf::Keyboard::Escape:
            {
                if (newSerieForeground != nullptr)
                {
                    newSerieForeground.reset();

                    break;
                }

                if (saveSerieForeground != nullptr)
                {
                    saveSerieForeground.reset();

                    break;
                }

                setExpectedControllerId(ControllerId::EditorMenu);

                break;
            }
            default:
            {
                if (saveSerieForeground != nullptr)
                {
                    saveSerieForeground->getInputTextWidget().update(event);
                }
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
            else if (
                impl->buttonNew.isMouseHover() and
                newSerieForeground == nullptr
            )
            {
                newSerieForeground =
                    std::make_unique<foregrounds::MessageForeground>(
                        context,
                        ERASE_SERIE_MESSAGE
                    );
            }
            else if (
                impl->buttonSave.isMouseHover() and
                saveSerieForeground == nullptr
            )
            {
                auto serieNameText =
                    impl->serieNameText.getString().toAnsiString();

                if (serieNameText != UNTITLED_SERIE)
                {
                    if (serieNameText.back() == '*')
                    {
                        const auto& serieName = impl->serieName;

                        saveSerieFile(serieName);

                        impl->serieNameText.setString(serieName);

                        updateSerieNamePosition();
                    }

                    break;
                }

                saveSerieForeground =
                    std::make_unique<foregrounds::InputTextForeground>(
                        context,
                        SAVE_SERIE_MESSAGE
                    );
            }

            const auto& levelsList = impl->lists.getLevelsList();
            const auto& seriesList = impl->lists.getSerieLevelsList();

            const auto& levelsListItemsAmount = levelsList.getItemsAmount();
            const auto& seriesListItemsAmount = seriesList.getItemsAmount();

            const auto& levelsListCurrentIndex = levelsList.getCurrentIndex();
            const auto& seriesListCurrentIndex = seriesList.getCurrentIndex();

            constexpr short NO_SELECTION_INDEX =
                widgets::SelectionListWidget::NO_SELECTION_INDEX;

            if (
                levelsListCurrentIndex < levelsListItemsAmount and
                levelsListCurrentIndex != NO_SELECTION_INDEX
            )
            {
                impl->lists.getSerieLevelsList().addItem(
                    levelsList.getCurrentItem()
                );

                levelsList.deleteSelectedItem();

                markSerieUnsaved();
            }
            else if (
                seriesListCurrentIndex < seriesListItemsAmount and
                seriesListCurrentIndex != NO_SELECTION_INDEX
            )
            {
                impl->lists.getLevelsList().addItem(
                    seriesList.getCurrentItem()
                );

                seriesList.deleteSelectedItem();

                markSerieUnsaved();
            }

            using ListMovement = widgets::SelectionListWidget::ListMovement;

            if (levelsList.canScrollUp())
            {
                levelsList.updateAllItemsPosition(ListMovement::Up);
            }
            else if (levelsList.canScrollDown())
            {
                levelsList.updateAllItemsPosition(ListMovement::Down);
            }

            if (seriesList.canScrollUp())
            {
                seriesList.updateAllItemsPosition(ListMovement::Up);
            }
            else if (seriesList.canScrollDown())
            {
                seriesList.updateAllItemsPosition(ListMovement::Down);
            }

            break;
        }
        default:
        {
        }
        }
    }

    return getNextControllerId();
}

/**
 *
 */
void SerieEditorController::saveSerieFile(const std::string& name) const &
{
    std::ofstream file;
    utils::applyFailbitAndBadbitExceptions(file);

    file.open(
        "data/series/personals/" + name + ".serie",
        std::fstream::out
    );

    /* write three empty best scores */
    file << "." << std::endl << "." << std::endl << "." << std::endl;

    // const std::vector<sf::Text>&
    const auto& texts = impl->lists.getSerieLevelsList().getTexts();

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

    serieNameText.setPosition(
        window::WIDTH -
            serieNameText.getLocalBounds().width,
        0.f
    );
}

}
}
