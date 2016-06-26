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
#include "intervals.hpp"

namespace memoris
{
namespace controllers
{

/* NOTE: the string are non-integral type,
   it cannot be defined in the header */

const std::string MainMenuController::PATH_IMAGE_GITHUB =
    "res/images/fork-me.png";
const std::string MainMenuController::TITLE = "Memoris";
const std::string MainMenuController::NEW_GAME = "New game";
const std::string MainMenuController::LOAD_GAME = "Load game";
const std::string MainMenuController::EDITOR = "Editor";
const std::string MainMenuController::OPTIONS = "Options";
const std::string MainMenuController::EXIT = "Exit";

/**
 *
 */
MainMenuController::MainMenuController(utils::Context& context) :
    Controller(context),
    background(context),
    menuGradient(context)
{
    /* animations times are all set to 0 */
    titleLastAnimationTime = 0;

    /* the title color and selector color are copies from
       manager colors, because they are updated continually */
    colorTitle = context.getColorsManager().getColorBlueCopy();
    colorSelector = context.getColorsManager().getColorRedCopy();

    /* initialize the title text label, at the top center of the screen */
    title.setFont(context.getFontsManager().getTitleFont());
    title.setString(TITLE);
    title.setCharacterSize(memoris::fonts::TITLE_SIZE);
    title.setColor(colorTitle);
    title.setPosition(
        TITLE_HORIZONTAL_POSITION,
        TITLE_VERTICAL_POSITION
    );

    /* initialize the new game menu item */
    itemNewGame.setFont(context.getFontsManager().getTextFont());
    itemNewGame.setString(NEW_GAME);
    itemNewGame.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemNewGame.setColor(colorSelector);
    itemNewGame.setPosition(
        NEW_GAME_HORIZONTAL_POSITION,
        NEW_GAME_VERTICAL_POSITION
    );

    /* initialize the open game menu item */
    itemLoadGame.setFont(context.getFontsManager().getTextFont());
    itemLoadGame.setString(LOAD_GAME);
    itemLoadGame.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemLoadGame.setColor(context.getColorsManager().getColorWhite());
    itemLoadGame.setPosition(
        LOAD_GAME_HORIZONTAL_POSITION,
        LOAD_GAME_VERTICAL_POSITION
    );

    /* initialize the editor menu item */
    itemEditor.setFont(context.getFontsManager().getTextFont());
    itemEditor.setString(EDITOR);
    itemEditor.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemEditor.setColor(context.getColorsManager().getColorWhite());
    itemEditor.setPosition(
        EDITOR_HORIZONTAL_POSITION,
        EDITOR_VERTICAL_POSITION
    );

    /* initialize the options menu item */
    itemOptions.setFont(context.getFontsManager().getTextFont());
    itemOptions.setString(OPTIONS);
    itemOptions.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemOptions.setColor(context.getColorsManager().getColorWhite());
    itemOptions.setPosition(
        OPTIONS_HORIZONTAL_POSITION,
        OPTIONS_VERTICAL_POSITION
    );

    /* initialize the exit menu item */
    itemExit.setFont(context.getFontsManager().getTextFont());
    itemExit.setString(EXIT);
    itemExit.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemExit.setColor(context.getColorsManager().getColorWhite());
    itemExit.setPosition(
        EXIT_HORIZONTAL_POSITION,
        EXIT_VERTICAL_POSITION
    );

    spriteGithub.setTexture(
        context.getTexturesManager().getGithubTexture(),
        true
    );
    spriteGithub.setPosition(
        GITHUB_PICTURE_HORIZONTAL_POSITION,
        GITHUB_PICTURE_VERTICAL_POSITION
    );

    titleRedDirection = DIRECTION_TITLE_RED_INIT;
    titleGreenDirection = DIRECTION_TITLE_GREEN_INIT;
    titleBlueDirection = DIRECTION_TITLE_BLUE_INIT;

    /* TODO: #436 should be refactored in a middleware controller type, for
       example AbstractMenuController */
    selectorPosition = 0;
    selectorDirection = 1;
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

    /* TODO: #438 to refactor */
    policies::HasMenuSelectorAnimation::animateMenuSelector<MainMenuController>(this);

    /* TODO: #439 for now, the current selected item color is continually
       updated, even when it is not necessary, should be refactored */
    updateSelectorPosition(context);

    /* render the title, all the menu items and the github picture */
    context.getSfmlWindow().draw(title);
    context.getSfmlWindow().draw(itemNewGame);
    context.getSfmlWindow().draw(itemLoadGame);
    context.getSfmlWindow().draw(itemEditor);
    context.getSfmlWindow().draw(itemOptions);
    context.getSfmlWindow().draw(itemExit);
    context.getSfmlWindow().draw(spriteGithub);

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
                context.getSoundsManager().getMoveSelectorSound().play();

                selectorPosition--;

                break;
            }
            case sf::Keyboard::Down:
            {
                context.getSoundsManager().getMoveSelectorSound().play();

                selectorPosition++;

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
        colorTitle.r == COLOR_TITLE_RED_MAX ||
        colorTitle.r == COLOR_TITLE_ALL_MIN
    )
    {
        titleRedDirection = -titleRedDirection;
    }

    if(
        colorTitle.g == COLOR_TITLE_GREEN_MAX ||
        colorTitle.g == COLOR_TITLE_ALL_MIN
    )
    {
        titleGreenDirection = -titleGreenDirection;
    }

    if(
        colorTitle.b == COLOR_TITLE_BLUE_MAX ||
        colorTitle.b == COLOR_TITLE_ALL_MIN
    )
    {
        titleBlueDirection = -titleBlueDirection;
    }

    title.setColor(colorTitle);
}

/**
 *
 */
void MainMenuController::updateSelectorPosition(utils::Context& context)
{
    /* if the selector position is more than the Exit menu item position,
       the New Game item becomes the selected item */
    /* TODO: #441 going from exit to new game works but not going from new
       game to exit */
    selectorPosition = (
                           (selectorPosition > ITEM_EXIT) ?
                           ITEM_NEW_GAME :
                           selectorPosition
                       );

    /* before applying the selector color on the selected menu item, we
       first change the color of every menu item to white */
    itemNewGame.setColor(context.getColorsManager().getColorWhite());
    itemLoadGame.setColor(context.getColorsManager().getColorWhite());
    itemEditor.setColor(context.getColorsManager().getColorWhite());
    itemOptions.setColor(context.getColorsManager().getColorWhite());
    itemExit.setColor(context.getColorsManager().getColorWhite());

    /* apply the selector color on the right item, according to the current
       selector position */
    switch(selectorPosition)
    {
    case ITEM_NEW_GAME:
    {
        itemNewGame.setColor(colorSelector);
        break;
    }
    case ITEM_LOAD_GAME:
    {
        itemLoadGame.setColor(colorSelector);
        break;
    }
    case ITEM_EDITOR:
    {
        itemEditor.setColor(colorSelector);
        break;
    }
    case ITEM_OPTIONS:
    {
        itemOptions.setColor(colorSelector);
        break;
    }
    default:
    {
        itemExit.setColor(colorSelector);
        break;
    }
    }
}

/**
 *
 */
void MainMenuController::selectMenuItem()
{
    /* update the expected controller id according to the selector
       current position */
    switch(selectorPosition)
    {
    case ITEM_NEW_GAME:
    {
        expectedControllerId = NEW_GAME_CONTROLLER_ID;

        break;
    }
    case ITEM_EDITOR:
    {
        expectedControllerId = EDITOR_MENU_CONTROLLER_ID;

        break;
    }
    default:
    {
        /* TODO: #442 we specify the namespace because the variable name is the
           same as the EXIT menu item string */
        nextControllerId = controllers::EXIT;

        break;
    }
    }
}

}
}
