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
 * @file SerieMainMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SerieMainMenuController.hpp"

#include "controllers_ids.hpp"
#include "fonts_sizes.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "MenuItem.hpp"
#include "window.hpp"
#include "Game.hpp"
#include "SoundsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{
namespace controllers
{

class SerieMainMenuController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        const auto& fontsManager = context.getFontsManager();
        const auto& lightBlue = context.getColorsManager().getColorLightBlue();

        title.setFont(fontsManager.getTitleFont());
        title.setString("Series");
        title.setCharacterSize(sizes::SUB_TITLE_SIZE);
        title.setFillColor(lightBlue);

        constexpr float TITLE_VERTICAL_POSITION {50.f};
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        gameName.setFont(fontsManager.getTextFont());
        gameName.setString(context.getGame().getName());
        gameName.setCharacterSize(sizes::TEXT_SIZE);
        gameName.setFillColor(lightBlue);

        constexpr float GAME_NAME_VERTICAL_POSITION {810.f};
        constexpr float GAME_NAME_RIGHT_PADDING {20.f};
        gameName.setPosition(
            window::WIDTH - gameName.getLocalBounds().width -
                GAME_NAME_RIGHT_PADDING,
            GAME_NAME_VERTICAL_POSITION
        );
    }

    sf::Text title;
    sf::Text gameName;
};

/**
 *
 */
SerieMainMenuController::SerieMainMenuController(
    const utils::Context& context
) :
    AbstractMenuController(context),
    impl(std::make_unique<Impl>(context))
{
    constexpr float OFFICIAL_SERIES_ITEM_VERTICAL_POSITION {250.f};
    std::unique_ptr<items::MenuItem> officialSeries(
        std::make_unique<items::MenuItem>(
            context,
            "Official series",
            OFFICIAL_SERIES_ITEM_VERTICAL_POSITION
        )
    );

    constexpr float PERSONAL_SERIES_ITEM_VERTICAL_POSITION {350.f};
    std::unique_ptr<items::MenuItem> personalSeries(
        std::make_unique<items::MenuItem>(
            context,
            "Personal series",
            PERSONAL_SERIES_ITEM_VERTICAL_POSITION
        )
    );

    constexpr float BACK_ITEM_VERTICAL_POSITION {650.f};
    std::unique_ptr<items::MenuItem> back(
        std::make_unique<items::MenuItem>(
            context,
            "Back",
            BACK_ITEM_VERTICAL_POSITION
        )
    );

    constexpr float REMOVE_ITEM_VERTICAL_POSITION {810.f};
    std::unique_ptr<items::MenuItem> remove(
        std::make_unique<items::MenuItem>(
            context,
            "Remove",
            REMOVE_ITEM_VERTICAL_POSITION,
            items::MenuItem::HorizontalPosition::Left
        )
    );

    officialSeries->select();

    addMenuItem(std::move(officialSeries));
    addMenuItem(std::move(personalSeries));
    addMenuItem(std::move(back));
    addMenuItem(std::move(remove));
}

/**
 *
 */
SerieMainMenuController::~SerieMainMenuController() = default;

/**
 *
 */
const ControllerId& SerieMainMenuController::render() const &
{
    const auto& context = getContext();

    auto& window = context.getSfmlWindow();
    window.draw(impl->title);
    window.draw(impl->gameName);

    renderAllMenuItems();

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while (context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            const auto& selection = getSelectorPosition();

            const auto& soundsManager = context.getSoundsManager();

            using namespace managers;
            void (SoundsManager::*playSound)() const & =
                &SoundsManager::playMoveSelectorSound;

            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                setExpectedControllerId(ControllerId::MainMenu);

                break;
            }
            case sf::Keyboard::Up:
            {
                if (selection == 0)
                {
                    break;
                }

                moveUp();

                updateMenuSelection();

                (soundsManager.*playSound)();

                break;
            }
            case sf::Keyboard::Down:
            {
                if (selection == getLastItemIndex())
                {
                    break;
                }

                moveDown();

                updateMenuSelection();

                (soundsManager.*playSound)();

                break;
            }
            case sf::Keyboard::Return:
            {
                selectMenuItem();

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

    return getNextControllerId();
}

/**
 *
 */
void SerieMainMenuController::selectMenuItem() const & noexcept
{
    switch(getSelectorPosition())
    {
    case 0:
    {
        setExpectedControllerId(ControllerId::OfficialSeriesMenu);

        break;
    }
    case 1:
    {
        setExpectedControllerId(ControllerId::PersonalSeriesMenu);

        break;
    }
    case 2:
    {
        setExpectedControllerId(ControllerId::MainMenu);

        break;
    }
    default:
    {
        setExpectedControllerId(ControllerId::RemoveGame);

        break;
    }
    }
}

}
}
