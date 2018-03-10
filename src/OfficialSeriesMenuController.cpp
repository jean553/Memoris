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
#include "fonts_sizes.hpp"
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

#include <fstream>

namespace memoris
{
namespace controllers
{

constexpr char GAMES_FILES_DIRECTORY[] {"data/games/"};
constexpr char GAMES_FILES_EXTENSION[] {".game"};

class OfficialSeriesMenuController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Official series");
        title.setCharacterSize(memoris::sizes::SUB_TITLE_SIZE);
        title.setFillColor(context.getColorsManager().getColorLightBlue());

        constexpr float TITLE_VERTICAL_POSITION {50.f};
        title.setPosition(
            window::getCenteredTextHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );
    }

    sf::Text title;

    /* not set into the implementation constructor as it needs
       a call to the Controller parent method getContext(),
       not set directly into the required function
       as this is a virtual function marked as noexcept:
       opening the file there would force us to remove "noexcept"
       from all the others definitions */
    unsigned short lastUnlockedSerie;
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
    std::ifstream file;
    file.open(
        GAMES_FILES_DIRECTORY +
        getContext().getGameName() +
        GAMES_FILES_EXTENSION
    );

    /* get a character from file, substract the value of 48
       in order to find numeric value from character */
    char serieCharacter;
    file.get(serieCharacter);
    impl->lastUnlockedSerie = serieCharacter - '0';

    constexpr float EASY_VERTICAL_POSITION {270.f};
    std::unique_ptr<items::MenuItem> easy(
        std::make_unique<items::MenuItem>(
            context,
            "Easy",
            EASY_VERTICAL_POSITION
        )
    );

    constexpr float MEDIUM_VERTICAL_POSITION {400.f};
    std::unique_ptr<items::MenuItem> medium(
        std::make_unique<items::MenuItem>(
            context,
            "Medium",
            MEDIUM_VERTICAL_POSITION
        )
    );

    easy->select();

    addMenuItem(std::move(easy));
    addMenuItem(std::move(medium));

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
    const auto selectedSerie = getSelectorPosition();
    const auto& lastUnlockedSerie = impl->lastUnlockedSerie;

    if (selectedSerie > lastUnlockedSerie)
    {
        setExpectedControllerId(ControllerId::UnlockedSerieError);

        return;
    }

    const std::string serie = getSerieNameByItemId(selectedSerie);

    try
    {
        const auto& serieManager = getContext().getPlayingSerieManager();

        serieManager.loadSerieFileContent(
            serie,
            managers::PlayingSerieManager::SerieType::Official
        );

        serieManager.setIsUnlockable(selectedSerie == lastUnlockedSerie);

        setExpectedControllerId(ControllerId::Game);
    }
    catch(std::invalid_argument&)
    {
        setExpectedControllerId(ControllerId::OpenFileError);
    }
}

/**
 *
 */
const std::string OfficialSeriesMenuController::getSerieNameByItemId(
    const unsigned short& itemId
) const & noexcept
{
    switch(itemId)
    {
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
