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
 * @file PersonalSeriesMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PersonalSeriesMenuController.hpp"

#include "controllers.hpp"
#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"
#include "SelectionListWidget.hpp"
#include "Cursor.hpp"
#include "DirectoryReader.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class PersonalSeriesMenuController::Impl
{

public:

    Impl(const utils::Context& context) :
        list(context),
        cursor(context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Personal series");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            50.f
        );

        list.setList(
            context,
            utils::getFilesFromDirectory("data/series/personals")
        );
    }

    sf::Text title;

    widgets::SelectionListWidget list;

    widgets::Cursor cursor;
};

/**
 *
 */
PersonalSeriesMenuController::PersonalSeriesMenuController(
    const utils::Context& context
) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
PersonalSeriesMenuController::~PersonalSeriesMenuController() noexcept = 
    default;

/**
 *
 */
const unsigned short& PersonalSeriesMenuController::render(
    const utils::Context& context
) &
{
    window.draw(impl->title);

    impl->list.display(context);

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
                expectedControllerId = SERIE_MAIN_MENU_CONTROLLER_ID;

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

    return nextControllerId;
}

}
}
