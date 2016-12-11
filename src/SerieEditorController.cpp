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
        cursor(context)
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

    widgets::Cursor cursor;
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
    window.draw(impl->serieName);

    impl->buttonNew.display(context);
    impl->buttonOpen.display(context);
    impl->buttonSave.display(context);
    impl->buttonExit.display(context);

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
                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            if (impl->buttonExit.isMouseHover())
            {
                expectedControllerId = EDITOR_MENU_CONTROLLER_ID;
            }

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
