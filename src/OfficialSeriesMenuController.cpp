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
 * @file OfficialSeriesMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OfficialSeriesMenuController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "MenuItem.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class OfficialSeriesMenuController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Official series");
        title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            50.f
        );
    }

    sf::Text title;
};

/**
 *
 */
OfficialSeriesMenuController::OfficialSeriesMenuController(
    const utils::Context& context
) :
    AbstractMenuController(context),
    impl(std::make_unique<Impl>(context))
{
    std::unique_ptr<items::MenuItem> easy(
        std::make_unique<items::MenuItem>(
            context,
            "Easy",
            270.f
        )
    );

    std::unique_ptr<items::MenuItem> medium(
        std::make_unique<items::MenuItem>(
            context,
            "Medium",
            340.f
        )
    );

    std::unique_ptr<items::MenuItem> difficult(
        std::make_unique<items::MenuItem>(
            context,
            "Difficult",
            410.f
        )
    );

    std::unique_ptr<items::MenuItem> hard(
        std::make_unique<items::MenuItem>(
            context,
            "Hard",
            480.f
        )
    );

    std::unique_ptr<items::MenuItem> veryHard(
        std::make_unique<items::MenuItem>(
            context,
            "Very Hard",
            560.f
        )
    );

    std::unique_ptr<items::MenuItem> hazardous(
        std::make_unique<items::MenuItem>(
            context,
            "Hazardous",
            630.f
        )
    );

    easy->select(context);

    addMenuItem(std::move(easy));
    addMenuItem(std::move(medium));
    addMenuItem(std::move(difficult));
    addMenuItem(std::move(hard));
    addMenuItem(std::move(veryHard));
    addMenuItem(std::move(hazardous));

    context.getPlayingSerieManager().reinitialize();
}

/**
 *
 */
OfficialSeriesMenuController::~OfficialSeriesMenuController() noexcept =
    default;

/**
 *
 */
const ControllerId& OfficialSeriesMenuController::render() &
{
    context.getSfmlWindow().draw(impl->title);

    renderAllMenuItems();

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
                expectedControllerId = ControllerId::MainMenu;

                break;
            }
            case sf::Keyboard::Return:
            {
                selectMenuItem();

                break;
            }
            case sf::Keyboard::Up:
            {
                moveUp();

                break;
            }
            case sf::Keyboard::Down:
            {
                moveDown();

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

/**
 *
 */
void OfficialSeriesMenuController::selectMenuItem() & noexcept
{
    const std::string serie = getSerieNameByItemId();

    /* TODO: #890 the locked list should be loaded from the game file; this
       condition is a temporary solution for tests only; to delete */
    if (serie == DIFFICULT)
    {
        expectedControllerId = ControllerId::UnlockedSerieError;

        return;
    }

    try
    {
        context.getPlayingSerieManager().loadSerieFileContent(
            "officials/" + serie
        );

        expectedControllerId = ControllerId::Game;

    }
    catch(std::invalid_argument&)
    {
        /* TODO: #559 the error controller should display the error message */
        expectedControllerId = ControllerId::OpenFileError;
    }
}

/**
 *
 */
const std::string OfficialSeriesMenuController::getSerieNameByItemId() const &
noexcept
{
    switch(getSelectorPosition())
    {
    case 2:
    {
        return DIFFICULT;

        break;
    }
    case 1:
    {
        return MEDIUM;

        break;
    }
    default:
    {
        return EASY;

        break;
    }
    }
}

}
}
