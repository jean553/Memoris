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
 * @file OfficialSeriesMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OfficialSeriesMenuController.hpp"

#include "controllers_ids.hpp"
#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "MenuItem.hpp"
#include "window.hpp"
#include "SoundsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

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

        constexpr float TITLE_VERTICAL_POSITION {50.f};
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
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
    constexpr float EASY_VERTICAL_POSITION {270.f};
    std::unique_ptr<items::MenuItem> easy(
        std::make_unique<items::MenuItem>(
            context,
            "Easy",
            EASY_VERTICAL_POSITION
        )
    );

    constexpr float MEDIUM_VERTICAL_POSITION {340.f};
    std::unique_ptr<items::MenuItem> medium(
        std::make_unique<items::MenuItem>(
            context,
            "Medium",
            MEDIUM_VERTICAL_POSITION
        )
    );

    constexpr float DIFFICULT_VERTICAL_POSITION {410.f};
    std::unique_ptr<items::MenuItem> difficult(
        std::make_unique<items::MenuItem>(
            context,
            "Difficult",
            DIFFICULT_VERTICAL_POSITION
        )
    );

    constexpr float HARD_VERTICAL_POSITION {480.f};
    std::unique_ptr<items::MenuItem> hard(
        std::make_unique<items::MenuItem>(
            context,
            "Hard",
            HARD_VERTICAL_POSITION
        )
    );

    easy->select(context);

    addMenuItem(std::move(easy));
    addMenuItem(std::move(medium));
    addMenuItem(std::move(difficult));
    addMenuItem(std::move(hard));

    /* TODO: #1079 this function should not be part
       of the menu initialization */
    context.getPlayingSerieManager().reinitialize();
}

/**
 *
 */
OfficialSeriesMenuController::~OfficialSeriesMenuController() = default;

/**
 *
 */
const ControllerId& OfficialSeriesMenuController::render() const &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();

    window.draw(impl->title);

    renderAllMenuItems();

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(window.pollEvent(event))
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

            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                setExpectedControllerId(ControllerId::MainMenu);

                break;
            }
            case sf::Keyboard::Return:
            {
                selectMenuItem();

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
void OfficialSeriesMenuController::selectMenuItem() const & noexcept
{
    const std::string serie = getSerieNameByItemId();

    /* TODO: #890 the locked list should be loaded from the game file; this
       condition is a temporary solution for tests only; to delete;
       the 'difficult' name could be refactored into a static constexpr,
       however I do not do it as this is a temporarily solution */
    if (serie == "difficult")
    {
        setExpectedControllerId(ControllerId::UnlockedSerieError);

        return;
    }

    try
    {
        getContext().getPlayingSerieManager().loadSerieFileContent(
            "officials/" + serie
        );

        setExpectedControllerId(ControllerId::Game);
    }
    catch(std::invalid_argument&)
    {
        /* TODO: #559 the error controller should display the error message */
        setExpectedControllerId(ControllerId::OpenFileError);
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
        return "difficult";

        break;
    }
    case 1:
    {
        return "medium";

        break;
    }
    default:
    {
        return "easy";

        break;
    }
    }
}

}
}
