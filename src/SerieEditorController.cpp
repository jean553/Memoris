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
 * @file SerieEditorController.hpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SerieEditorController.hpp"

#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "TexturesManager.hpp"
#include "Context.hpp"
#include "controllers.hpp"
#include "fonts.hpp"
#include "Button.hpp"
#include "Cursor.hpp"
#include "DoubleSelectionListWidget.hpp"
#include "SelectionListWidget.hpp"
#include "InputTextForeground.hpp"
#include "NewFileForeground.hpp"
#include "InputTextWidget.hpp"
#include "OpenFileForeground.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

constexpr float SerieEditorController::BUTTONS_VERTICAL_POSITION;
constexpr float SerieEditorController::NEW_BUTTON_HORIZONTAL_POSITION;
constexpr float SerieEditorController::OPEN_BUTTON_HORIZONTAL_POSITION;
constexpr float SerieEditorController::SAVE_BUTTON_HORIZONTAL_POSITION;
constexpr float SerieEditorController::EXIT_BUTTON_HORIZONTAL_POSITION;

constexpr const char SerieEditorController::SAVE_SERIE_MESSAGE[];

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
        buttonOpen(
            context,
            OPEN_BUTTON_HORIZONTAL_POSITION,
            BUTTONS_VERTICAL_POSITION,
            context.getTexturesManager().getOpenTexture()
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
        buttonSwitch(
            context,
            760.f,
            450.f,
            context.getTexturesManager().getSwitchTexture()
        ),
        cursor(context),
        lists(context)
    {
        serieName.setString("untitled");
        serieName.setFont(context.getFontsManager().getTextFont());
        serieName.setColor(context.getColorsManager().getColorWhite());
        serieName.setCharacterSize(fonts::TEXT_SIZE);
        serieName.setPosition(
            SERIE_NAME_POSITION - serieName.getLocalBounds().width,
            0.f
        );
    }

    sf::Text serieName;

    widgets::Button buttonNew;
    widgets::Button buttonOpen;
    widgets::Button buttonSave;
    widgets::Button buttonExit;
    widgets::Button buttonSwitch;

    widgets::Cursor cursor;

    widgets::DoubleSelectionListWidget lists;

    std::unique_ptr<foregrounds::InputTextForeground> saveSerieForeground
        {nullptr};

    std::unique_ptr<foregrounds::NewFileForeground> newSerieForeground
        {nullptr};

    std::unique_ptr<foregrounds::OpenFileForeground> openSerieForeground
        {nullptr};
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
const unsigned short& SerieEditorController::render(
    const utils::Context& context
) &
{
    auto& saveSerieForeground = impl->saveSerieForeground;
    auto& newSerieForeground = impl->newSerieForeground;
    auto& openSerieForeground = impl->openSerieForeground;

    if (saveSerieForeground != nullptr)
    {
        saveSerieForeground->render(context);
    }
    else if (newSerieForeground != nullptr)
    {
        newSerieForeground->render(context);
    }
    else if (openSerieForeground != nullptr)
    {
        openSerieForeground->render(context);
    }
    else
    {
        window.draw(impl->serieName);

        impl->buttonNew.display(context);
        impl->buttonOpen.display(context);
        impl->buttonSave.display(context);
        impl->buttonExit.display(context);
        impl->buttonSwitch.display(context);

        impl->lists.display(context);

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
            case sf::Keyboard::N:
            {
                if (newSerieForeground != nullptr)
                {
                    newSerieForeground.reset();

                    break;
                }
            }
            case sf::Keyboard::Escape:
            {
                if (saveSerieForeground != nullptr)
                {
                    saveSerieForeground.reset();

                    break;
                }

                if (openSerieForeground != nullptr)
                {
                    openSerieForeground.reset();

                    break;
                }

                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

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
                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;
            }
            else if (
                impl->buttonNew.isMouseHover() and
                newSerieForeground == nullptr
            )
            {
                newSerieForeground =
                    std::make_unique<foregrounds::NewFileForeground>(
                        context
                    );
            }
            else if (
                impl->buttonOpen.isMouseHover() and
                openSerieForeground == nullptr
            )
            {
                openSerieForeground =
                    std::make_unique<foregrounds::OpenFileForeground>(
                        context
                    );
            }
            else if (
                impl->buttonSave.isMouseHover() and
                saveSerieForeground == nullptr
            )
            {
                saveSerieForeground =
                    std::make_unique<foregrounds::InputTextForeground>(
                        context,
                        SAVE_SERIE_MESSAGE
                    );
            }

            impl->lists.getLevelsList().updateList();

            break;
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
