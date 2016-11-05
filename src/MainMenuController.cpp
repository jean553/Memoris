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
 * @file MainMenuController.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MainMenuController.hpp"

#include "fonts.hpp"
#include "controllers.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "TexturesManager.hpp"
#include "MenuItem.hpp"
#include "AnimatedBackground.hpp"
#include "MenuGradient.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
    }

    utils::AnimatedBackground animatedBackground;
    others::MenuGradient menuGradient;

    /* we use SFML 32 bits long integers to save the
       last updated time of each animation; we use this
       data type as it is the one used by SFML clock */
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
    impl->colorTitle = context.getColorsManager().getColorBlueCopy();

    impl->title.setFont(context.getFontsManager().getTitleFont());
    impl->title.setString("Memoris");
    impl->title.setCharacterSize(fonts::TITLE_SIZE);
    impl->title.setColor(impl->colorTitle);
    impl->title.setPosition(
        480.f,
        100.f
    );

    std::unique_ptr<items::MenuItem> newGame(
        std::make_unique<items::MenuItem>(
            context,
            "New game",
            615.f,
            300.f
        )
    );

    std::unique_ptr<items::MenuItem> loadGame(
        std::make_unique<items::MenuItem>(
            context,
            "Load game",
            605.f,
            400.f
        )
    );

    std::unique_ptr<items::MenuItem> editor (
        std::make_unique<items::MenuItem>(
            context,
            "Editor",
            685.f,
            500.f
        )
    );

    std::unique_ptr<items::MenuItem> options(
        std::make_unique<items::MenuItem>(
            context,
            "Options",
            660.f,
            600.f
        )
    );

    std::unique_ptr<items::MenuItem> exit(
        std::make_unique<items::MenuItem>(
            context,
            "Exit",
            725.f,
            700.f
        )
    );

    newGame->select(context);

    addMenuItem(std::move(newGame));
    addMenuItem(std::move(loadGame));
    addMenuItem(std::move(editor));
    addMenuItem(std::move(options));
    addMenuItem(std::move(exit));

    impl->spriteGithub.setTexture(
        context.getTexturesManager().getGithubTexture()
    );
    impl->spriteGithub.setPosition(
        1300.f,
        0.f
    );
}

/**
 *
 */
MainMenuController::~MainMenuController() noexcept = default;

/**
 *
 */
const unsigned short& MainMenuController::render(
    const utils::Context& context
) &
{
    impl->animatedBackground.render(context);
    impl->menuGradient.display(context);

    if(
        context.getClockMillisecondsTime() -
        impl->titleLastAnimationTime > 10
    )
    {
        animateTitleColor();

        impl->titleLastAnimationTime = context.getClockMillisecondsTime();
    }

    context.getSfmlWindow().draw(impl->title);
    context.getSfmlWindow().draw(impl->spriteGithub);

    renderAllMenuItems(context);

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Up:
            {
                moveUp(context);

                break;
            }
            case sf::Keyboard::Down:
            {
                moveDown(context);

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

    return nextControllerId;
}

/**
 *
 */
void MainMenuController::animateTitleColor() &
{
    if (impl->incrementTitleRedColor)
    {
        impl->colorTitle.r++;
    }
    else
    {
        impl->colorTitle.r--;
    }

    if (impl->incrementTitleGreenColor)
    {
        impl->colorTitle.g++;
    }
    else
    {
        impl->colorTitle.g--;
    }

    if (impl->incrementTitleBlueColor)
    {
        impl->colorTitle.b++;
    }
    else
    {
        impl->colorTitle.b--;
    }

    if(
        impl->colorTitle.r == 255 ||
        impl->colorTitle.r == 0
    )
    {
        impl->incrementTitleRedColor = !impl->incrementTitleRedColor;
    }

    if(
        impl->colorTitle.g == 180 ||
        impl->colorTitle.g == 0
    )
    {
        impl->incrementTitleGreenColor = !impl->incrementTitleGreenColor;
    }

    if(
        impl->colorTitle.b == 255 ||
        impl->colorTitle.b == 0
    )
    {
        impl->incrementTitleBlueColor = !impl->incrementTitleBlueColor;
    }

    impl->title.setColor(impl->colorTitle);
}

/**
 *
 */
void MainMenuController::selectMenuItem() & noexcept
{
    switch(getSelectorPosition())
    {
    case 0:
    {
        expectedControllerId = NEW_GAME_CONTROLLER_ID;

        break;
    }
    case 1:
    {
        expectedControllerId = OPEN_GAME_CONTROLLER_ID;

        break;
    }
    case 2:
    {
        expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

        break;
    }
    default:
    {
        nextControllerId = EXIT;

        break;
    }
    }
}

}
}
