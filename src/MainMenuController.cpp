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

namespace memoris
{
namespace controllers
{

/**
 *
 */
MainMenuController::MainMenuController(
    const std::shared_ptr<utils::Context>& context
) :
    AbstractMenuController(context),
    animatedBackground(context),
    menuGradient(context)
{
    /* the title color and selector color are copies from
       manager colors, because they are updated continually */
    colorTitle = context->getColorsManager().getColorBlueCopy();

    /* initialize the title text label, at the top center of the screen */
    title.setFont(context->getFontsManager().getTitleFont());
    title.setString("Memoris");
    title.setCharacterSize(fonts::TITLE_SIZE);
    title.setColor(colorTitle);
    title.setPosition(
        480.f,
        100.f
    );

    /* initialize the new game menu item */
    std::unique_ptr<items::MenuItem> newGame(
        std::make_unique<items::MenuItem>(
            context,
            "New game",
            615.f,
            300.f
        )
    );

    /* initialize the open game menu item */
    std::unique_ptr<items::MenuItem> loadGame(
        std::make_unique<items::MenuItem>(
            context,
            "Load game",
            605.f,
            400.f
        )
    );

    /* initialize the editor menu item */
    std::unique_ptr<items::MenuItem> editor (
        std::make_unique<items::MenuItem>(
            context,
            "Editor",
            685.f,
            500.f
        )
    );

    /* initialize the options menu item */
    std::unique_ptr<items::MenuItem> options(
        std::make_unique<items::MenuItem>(
            context,
            "Options",
            660.f,
            600.f
        )
    );

    /* initialize the exit menu item */
    std::unique_ptr<items::MenuItem> exit(
        std::make_unique<items::MenuItem>(
            context,
            "Exit",
            725.f,
            700.f
        )
    );

    /* select the first item of the menu */
    newGame->select(context);

    /* add the menu items inside the menu items list */
    addMenuItem(std::move(newGame));
    addMenuItem(std::move(loadGame));
    addMenuItem(std::move(editor));
    addMenuItem(std::move(options));
    addMenuItem(std::move(exit));

    spriteGithub.setTexture(
        context->getTexturesManager().getGithubTexture()
    );
    spriteGithub.setPosition(
        1300.f,
        0.f
    );

    incrementTitleRedColor = true;
    incrementTitleGreenColor = true;
    incrementTitleBlueColor = false;
}

/**
 *
 */
unsigned short MainMenuController::render(
    const std::shared_ptr<utils::Context>& context
)
{
    /* animate the animated background */
    animatedBackground.render(context);

    /* apply the menu sub-surface */
    menuGradient.display(context);

    /* animate the main menu title according to its last animation time */
    if(
        context->getClockMillisecondsTime() -
        titleLastAnimationTime > 10
    )
    {
        animateTitleColor();

        /* update the title animation time with the current time
           after the animation */
        titleLastAnimationTime =
            context->getClockMillisecondsTime();
    }

    /* render the title and the github picture */
    context->getSfmlWindow().draw(title);
    context->getSfmlWindow().draw(spriteGithub);

    /* display all the menu items */
    renderAllMenuItems(context);

    /* render the opening/closing animation if necessary, get the next
       controller id at the end of the closing animation if the expected
       controller id has been modified */
    nextControllerId = animateScreenTransition(context);

    /* main menu controller events loop; changes the position of the menu
       selector according to the Up/Down keys; select a menu item when
       the Enter key is pressed */
    while(context->getSfmlWindow().pollEvent(event))
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
                /* empty default block for coding style requirements */
                break;
            }
            }
        }
        default:
        {
            /* empty default block for coding style requirements */
            break;
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void MainMenuController::animateTitleColor()
{
    /* update the color of the title over time */

    if (incrementTitleRedColor)
    {
        colorTitle.r++;
    }
    else
    {
        colorTitle.r--;
    }

    if (incrementTitleGreenColor)
    {
        colorTitle.g++;
    }
    else
    {
        colorTitle.g--;
    }

    if (incrementTitleBlueColor)
    {
        colorTitle.b++;
    }
    else
    {
        colorTitle.b--;
    }

    if(
        colorTitle.r == 255 ||
        colorTitle.r == 0
    )
    {
        incrementTitleRedColor = !incrementTitleRedColor;
    }

    if(
        colorTitle.g == 180 ||
        colorTitle.g == 0
    )
    {
        incrementTitleGreenColor = !incrementTitleGreenColor;
    }

    if(
        colorTitle.b == 255 ||
        colorTitle.b == 0
    )
    {
        incrementTitleBlueColor = !incrementTitleBlueColor;
    }

    title.setColor(colorTitle);
}

/**
 *
 */
void MainMenuController::selectMenuItem()
{
    /* call the correct controller according to the current selected item */
    switch(getSelectorPosition())
    {
    /* the new game item is selected */
    case 0:
    {
        expectedControllerId = NEW_GAME_CONTROLLER_ID;

        break;
    }
    /* the editor item is selected */
    case 2:
    {
        expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

        break;
    }
    /* the exit item is selected (or any other) */
    default:
    {
        nextControllerId = EXIT;

        break;
    }
    }
}

}
}
