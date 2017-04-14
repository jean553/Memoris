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
 * @file MainMenuController.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MainMenuController.hpp"

#include "controllers_ids.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "TexturesManager.hpp"
#include "MenuItem.hpp"
#include "AnimatedBackground.hpp"
#include "MenuGradient.hpp"
#include "window.hpp"
#include "SoundsManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace memoris
{
namespace controllers
{

class MainMenuController::Impl
{

public:

    Impl(const utils::Context& context) :
        animatedBackground(context),
        menuGradient(context)
    {
        colorTitle = context.getColorsManager().getColorBlueCopy();

        title.setFont(context.getFontsManager().getTitleFont());
        title.setString("Memoris");
        title.setFillColor(colorTitle);

        constexpr unsigned int TITLE_TEXT_SIZE {140};
        title.setCharacterSize(TITLE_TEXT_SIZE);

        constexpr float TITLE_VERTICAL_POSITION {100.f};
        title.setPosition(
            window::getCenteredTextHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        spriteGithub.setTexture(
            context.getTexturesManager().getGithubTexture()
        );

        constexpr float GITHUB_SPRITE_HORIZONTAL_POSITION {1300.f};
        constexpr float GITHUB_SPRITE_VERTICAL_POSITION {0.f};
        spriteGithub.setPosition(
            GITHUB_SPRITE_HORIZONTAL_POSITION,
            GITHUB_SPRITE_VERTICAL_POSITION
        );
    }

    utils::AnimatedBackground animatedBackground;
    others::MenuGradient menuGradient;

    sf::Int32 titleLastAnimationTime {0};

    bool incrementTitleRedColor {true};
    bool incrementTitleGreenColor {true};
    bool incrementTitleBlueColor {false};

    sf::Color colorTitle;

    sf::Text title;

    sf::Sprite spriteGithub;
};

/**
 *
 */
MainMenuController::MainMenuController(const utils::Context& context) :
    AbstractMenuController(context),
    impl(std::make_unique<Impl>(context))
{
    constexpr float NEW_GAME_VERTICAL_POSITION {320.f};
    std::unique_ptr<items::MenuItem> newGame(
        std::make_unique<items::MenuItem>(
            context,
            "New game",
            NEW_GAME_VERTICAL_POSITION
        )
    );

    constexpr float LOAD_GAME_VERTICAL_POSITION {450.f};
    std::unique_ptr<items::MenuItem> loadGame(
        std::make_unique<items::MenuItem>(
            context,
            "Load game",
            LOAD_GAME_VERTICAL_POSITION
        )
    );

    constexpr float EDITOR_VERTICAL_POSITION {580.f};
    std::unique_ptr<items::MenuItem> editor (
        std::make_unique<items::MenuItem>(
            context,
            "Editor",
            EDITOR_VERTICAL_POSITION
        )
    );

    constexpr float EXIT_VERTICAL_POSITION {710.f};
    std::unique_ptr<items::MenuItem> exit(
        std::make_unique<items::MenuItem>(
            context,
            "Exit",
            EXIT_VERTICAL_POSITION
        )
    );

    newGame->select();

    addMenuItem(std::move(newGame));
    addMenuItem(std::move(loadGame));
    addMenuItem(std::move(editor));
    addMenuItem(std::move(exit));
}

/**
 *
 */
MainMenuController::~MainMenuController() = default;

/**
 *
 */
const ControllerId& MainMenuController::render() const &
{
    impl->animatedBackground.render();
    impl->menuGradient.display();

    const auto& context = getContext();
    const auto& currentTime = context.getClockMillisecondsTime();
    auto& lastTime = impl->titleLastAnimationTime;

    constexpr sf::Int32 TITLE_COLOR_ANIMATION_INTERVAL {10};
    if (currentTime - lastTime > TITLE_COLOR_ANIMATION_INTERVAL)
    {
        animateTitleColor();
        lastTime = currentTime;
    }

    auto& window = context.getSfmlWindow();
    window.draw(impl->title);
    window.draw(impl->spriteGithub);

    renderAllMenuItems();

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(context.getSfmlWindow().pollEvent(event))
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
void MainMenuController::animateTitleColor() const &
{
    auto& colorTitle = impl->colorTitle;

    auto& incrementTitleRedColor = impl->incrementTitleRedColor;
    auto& colorTitleRed = colorTitle.r;
    if (incrementTitleRedColor)
    {
        colorTitleRed++;
    }
    else
    {
        colorTitleRed--;
    }

    auto& incrementTitleGreenColor = impl->incrementTitleGreenColor;
    auto& colorTitleGreen = colorTitle.g;
    if (incrementTitleGreenColor)
    {
        colorTitleGreen++;
    }
    else
    {
        colorTitleGreen--;
    }

    auto& incrementTitleBlueColor = impl->incrementTitleBlueColor;
    auto& colorTitleBlue = colorTitle.b;
    if (incrementTitleBlueColor)
    {
        colorTitleBlue++;
    }
    else
    {
        colorTitleBlue--;
    }

    constexpr sf::Uint8 TITLE_COLOR_MAXIMUM_RED {255};
    if(
        colorTitleRed == TITLE_COLOR_MAXIMUM_RED or
        colorTitleRed == 0
    )
    {
        incrementTitleRedColor = not incrementTitleRedColor;
    }

    constexpr sf::Uint8 TITLE_COLOR_MAXIMUM_GREEN {180};
    if(
        colorTitleGreen == TITLE_COLOR_MAXIMUM_GREEN or
        colorTitleGreen == 0
    )
    {
        incrementTitleGreenColor = not incrementTitleGreenColor;
    }

    constexpr sf::Uint8 TITLE_COLOR_MAXIMUM_BLUE {255};
    if(
        colorTitleBlue == TITLE_COLOR_MAXIMUM_BLUE or
        colorTitleBlue == 0
    )
    {
        incrementTitleBlueColor = not incrementTitleBlueColor;
    }

    impl->title.setFillColor(colorTitle);
}

/**
 *
 */
void MainMenuController::selectMenuItem() const & noexcept
{
    switch(getSelectorPosition())
    {
    case 0:
    {
        setExpectedControllerId(ControllerId::NewGame);

        break;
    }
    case 1:
    {
        setExpectedControllerId(ControllerId::OpenGame);

        break;
    }
    case 2:
    {
        setExpectedControllerId(ControllerId::EditorMenu);

        break;
    }
    default:
    {
        setNextControllerId(ControllerId::Exit);

        break;
    }
    }
}

}
}
