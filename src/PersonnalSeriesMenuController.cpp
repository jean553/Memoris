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

#include "controllers_ids.hpp"
#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"
#include "SelectionListWidget.hpp"
#include "Cursor.hpp"
#include "DirectoryReader.hpp"
#include "PlayingSerieManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

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
        title.setCharacterSize(fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());

        constexpr float TITLE_VERTICAL_POSITION {50.f};
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
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
    /* TODO: #1079 this function should not be part
       of the menu initialization */
    context.getPlayingSerieManager().reinitialize();
}

/**
 *
 */
PersonalSeriesMenuController::~PersonalSeriesMenuController() = default;

/**
 *
 */
const ControllerId& PersonalSeriesMenuController::render() const &
{
    const auto& context = getContext();

    auto& window = context.getSfmlWindow();
    window.draw(impl->title);

    const auto& list = impl->list;
    list.display(context);

    impl->cursor.render(context);

    setNextControllerId(animateScreenTransition(context));

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
                setExpectedControllerId(ControllerId::SerieMainMenu);

                break;
            }
            default:
            {
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            if (list.isAnyItemSelected())
            {
                try
                {
                    const auto& manager = context.getPlayingSerieManager();
                    const auto& serieName = list.getCurrentItem();

                    manager.loadSerieFileContent("personals/" + serieName);
                    manager.setIsOfficialSerie(false);

                    setExpectedControllerId(ControllerId::Game);

                }
                catch(std::invalid_argument&)
                {
                    /* TODO: #559 the error controller
                       should display the error message */
                    setExpectedControllerId(ControllerId::OpenFileError);
                }

                break;
            }

            list.updateList();

            break;
        }
        default:
        {
        }
        }
    }

    return getNextControllerId();
}

}
}
