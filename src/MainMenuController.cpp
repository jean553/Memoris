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

#include "FontsManager.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "intervals.hpp"
#include "ColorsManager.hpp"
#include "TexturesManager.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
MainMenuController::MainMenuController(utils::Context& context) :
    AbstractMenuController(context),
    background(context),
    menuGradient(context)
{
    /* animations times are all set to 0 */
    titleLastAnimationTime = 0;

    /* the title color and selector color are copies from
       manager colors, because they are updated continually */
    colorTitle = colors::ColorsManager::get().getColorBlueCopy();

    /* initialize the title text label, at the top center of the screen */
    title.setFont(fonts::FontsManager::get().getTitleFont());
    title.setString("Memoris");
    title.setCharacterSize(fonts::TITLE_SIZE);
    title.setColor(colorTitle);
    title.setPosition(
        480.f,
        100.f
    );

    /* initialize the new game menu item */
    newGame = new items::MenuItem(
        "New game",
        615.f,
        300.f
    );

    /* initialize the open game menu item */
    loadGame = new items::MenuItem(
        "Load game",
        605.f,
        400.f
    );

    /* initialize the editor menu item */
    editor = new items::MenuItem(
        "Editor",
        685.f,
        500.f
    );

    /* initialize the options menu item */
    options = new items::MenuItem(
        "Options",
        660.f,
        600.f
    );

    /* initialize the exit menu item */
    exit = new items::MenuItem(
        "Exit",
        725.f,
        700.f
    );

    /* add the menu items inside the menu items list */
    addMenuItem(newGame);
    addMenuItem(loadGame);
    addMenuItem(editor);
    addMenuItem(options);
    addMenuItem(exit);

    /* select the first item of the menu */
    newGame->select();

    spriteGithub.setTexture(
        textures::TexturesManager::get().getGithubTexture()
    );
    spriteGithub.setPosition(
        1300.f,
        0.f
    );

    titleRedDirection = 1;
    titleGreenDirection = 1;
    titleBlueDirection = -1;
}

/**
 *
 */
MainMenuController::~MainMenuController()
{
    /* TODO: #463 use a smart pointer for the management of the menu items */
    delete newGame;
    delete loadGame;
    delete editor;
    delete options;
    delete exit;
}

/**
 *
 */
unsigned short MainMenuController::render(utils::Context& context)
{
    /* display the background animation */
    background.animate(context);

    /* apply the menu sub-surface */
    menuGradient.display(context);

    /* animate the main menu title according to its last animation time */
    if(context.getClockMillisecondsTime() - titleLastAnimationTime >
            memoris::intervals::MENU_ITEM_ANIMATION_MILLISECONDS_INTERVAL
      )
    {
        animateTitleColor();

        /* update the title animation time with the current time
           after the animation */
        titleLastAnimationTime = context.getClockMillisecondsTime();
    }

    /* render the title and the github picture */
    context.getSfmlWindow().draw(title);
    context.getSfmlWindow().draw(spriteGithub);

    /* display all the menu items */
    renderAllMenuItems(context);

    /* TODO: #440 to refactor */
    nextControllerId = animateScreenTransition(context);

    /* main menu controller events loop; changes the position of the menu
       selector according to the Up/Down keys; select a menu item when
       the Enter key is pressed */
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
                moveUp();

                break;
            }
            case sf::Keyboard::Down:
            {
                moveDown();

                break;
            }
            case sf::Keyboard::Return:
            {
                selectMenuItem();

                break;
            }
            }
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

    colorTitle.r += titleRedDirection;
    colorTitle.g += titleGreenDirection;
    colorTitle.b += titleBlueDirection;

    if(
        colorTitle.r == 255 ||
        colorTitle.r == 0
    )
    {
        titleRedDirection = -titleRedDirection;
    }

    if(
        colorTitle.g == 180 ||
        colorTitle.g == 0
    )
    {
        titleGreenDirection = -titleGreenDirection;
    }

    if(
        colorTitle.b == 255 ||
        colorTitle.b == 0
    )
    {
        titleBlueDirection = -titleBlueDirection;
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
