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
 * @file EditorMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorMenuController.hpp"

#include "controllers_ids.hpp"
#include "fonts_sizes.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "MenuItem.hpp"
#include "window.hpp"
#include "SoundsManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{
namespace controllers
{

class EditorMenuController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        constexpr float TITLE_VERTICAL_POSITION {50.f};
        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Editor");
        title.setCharacterSize(memoris::sizes::SUB_TITLE_SIZE);
        title.setFillColor(context.getColorsManager().getColorLightBlue());
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
EditorMenuController::EditorMenuController(const utils::Context& context) :
    AbstractMenuController(context),
    impl(std::make_unique<Impl>(context))
{
    constexpr float LEVEL_VERTICAL_POSITION {200.f};
    std::unique_ptr<items::MenuItem> level(
        std::make_unique<items::MenuItem>(
            context,
            "Level",
            LEVEL_VERTICAL_POSITION
        )
    );

    constexpr float SERIE_VERTICAL_POSITION {350.f};
    std::unique_ptr<items::MenuItem> serie(
        std::make_unique<items::MenuItem>(
            context,
            "Serie",
            SERIE_VERTICAL_POSITION
        )
    );

    constexpr float EXIT_VERTICAL_POSITION {800.f};
    std::unique_ptr<items::MenuItem> back(
        std::make_unique<items::MenuItem>(
            context,
            "Back",
            EXIT_VERTICAL_POSITION
        )
    );

    level->select();

    addMenuItem(std::move(level));
    addMenuItem(std::move(serie));
    addMenuItem(std::move(back));
}

/**
 *
 */
EditorMenuController::~EditorMenuController() = default;

/**
 *
 */
const ControllerId& EditorMenuController::render() const &
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
void EditorMenuController::selectMenuItem() const & noexcept
{
    switch(getSelectorPosition())
    {
    case 0:
    {
        setExpectedControllerId(ControllerId::LevelEditor);

        break;
    }
    case 1:
    {
        setExpectedControllerId(ControllerId::SerieEditor);

        break;
    }
    case 2:
    {
        setExpectedControllerId(ControllerId::MainMenu);

        break;
    }
    }
}

}
}
