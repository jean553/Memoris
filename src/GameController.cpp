/*
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
 * @file GameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

#include "controllers.hpp"
#include "SoundsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "cells.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
GameController::GameController() :
/* TODO: #560 the playing serie manager should not be accessible from
   everywhere; we send the parameter here to force the execution of the
   Level constructor that loads from level file */
    level(series::PlayingSerieManager::get().getNextLevelName())
{
    /* save the exact time the level starts to be displayed; this is used to
       calculate the duration of the watching period before the beginning
       of the playing period */
    displayLevelTime = utils::Context::get().getClockMillisecondsTime();
}

/**
 *
 */
unsigned short GameController::render()
{
    /* displays the game dashboard */
    dashboard.display();

    /* display the level and all the cells */
    /* TODO: #546 only displays the first floor for now, so 0; should be
       modified according to the current user floor */
    level.display(0);

    /* displays all the cells of the level during the time of the watching
       period */
    /* TODO: #547 5000 ms is a default value, should be the actual bonus
       watching time of the player */
    if (
        watchingPeriod &&
        (
            utils::Context::get().getClockMillisecondsTime() -
            displayLevelTime > 5000
        )
    )
    {
        /* hide all the cells of the level */
        level.hideAllCellsExceptDeparture();

        /* plays the hide level sound */
        sounds::SoundsManager::get().getHideLevelSound().play();

        /* the watching mode is now terminated */
        watchingPeriod = false;

        /* the playing period starts now */
        playingPeriod = true;

        /* at this moment, we do not save the moment the animation ends; in
           fact, this is not a repeated action, there is no need to save
           the current time here */
    }

    /* if the current game status is playing, the player cell has to be
       animated */
    if (
        playingPeriod &&
        (
            utils::Context::get().getClockMillisecondsTime() -
            playerCellAnimationTime > 100
        )
    )
    {
        /* increment the value of the transparency with the value 64; */
        playerCellTransparency += 64;

        /* modifies the transparency of the player cell color */
        level.setPlayerCellTransparency(playerCellTransparency);

        /* check if the current value is more than 128; in fact, the
           transparency value can only be located between 64 and 128 */
        if (playerCellTransparency > 128)
        {
            /* reset the player cell transparency; this value will be set to
               64 during the next incrementation; I use this method to avoid
               to have the same constant expression at different locations in
               the code */
            playerCellTransparency = 0;
        }

        /* save the time of the last player cell animation, for the next
           animation step */
        playerCellAnimationTime =
            utils::Context::get().getClockMillisecondsTime();
    }

    /* used for the screen switch transition animation */
    nextControllerId = animateScreenTransition();

    /* the events loop of the game controller */
    while(utils::Context::get().getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        /* a key is pressed on the keyboard */
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            /* the up key is pressed down */
            case sf::Keyboard::Up:
            {
                handlePlayerMovement(-20);

                break;
            }
            /* the down key is pressed down */
            case sf::Keyboard::Down:
            {
                handlePlayerMovement(20);

                break;
            }
            /* the left key is pressed down */
            case sf::Keyboard::Left:
            {
                handlePlayerMovement(-1);

                break;
            }
            /* the right key is pressed down */
            case sf::Keyboard::Right:
            {
                handlePlayerMovement(1);

                break;
            }
            /* the escape key is pressed down */
            case sf::Keyboard::Escape:
            {
                /* the game is terminated and the called controller is the
                   main menu controller */

                /* NOTE: the game does not ask for confirmation to the player
                   when he pressed the espace key; in fact, this feature does
                   not exist in Memoris: this would give to the player some
                   'relax' time and more time to thinks about how to finish
                   the level, even if the cells are not displayed during the
                   pause time */
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
                /* useless, added here to respect syntax */
                break;
            }
            }
        }
        default:
        {
            /* useless, added here to respect syntax */
            break;
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void GameController::handlePlayerMovement(const short& movement)
{
    /* NOTE: we voluntary do not refactor the two following conditions or use
       short-circuiting on them; in fact, we really want check the movement
       allowance first and end the function if the movement cannot be perfored,
       without starting to check the second condition */

    /* checks if the movement is actually allowed before performing it; we
       check if the player is not already on level borders and is trying to
       move to the outside of the playable area */
    if (!level.allowPlayerMovement(movement))
    {
        /* stop the process and do not move if the movement is not allowed */
        return;
    }

    /* check if the player is against a wall during the movement; if there is
       a collision, the wall is displayed by the condition function and the
       movement is cancelled */
    if (level.detectWalls(movement))
    {
        /* the movement is cancelled if the player is against a wall */
        return;
    }

    /* empty the current player cell before moving; some types are not cleared,
       that's what the function has to check */
    emptyPlayerCell();

    /* move the player, display walls if there are some collisions and show
       the new cell */
    level.movePlayer(movement);

    /* execute the action of the new player cell right after the movement */
    executePlayerCellAction();
}

/**
 *
 */
void GameController::executePlayerCellAction()
{
    /* create an alias on the new player cell type, returned as a reference
       by the level getter */
    const char& newPlayerCellType = level.getPlayerCellType();

    /* NOTE: this switch only contains one case for now but expects to get
       almost one case per cell type */

    switch(newPlayerCellType)
    {
    case cells::STAR_CELL:
    {
        /* plays the found star cell sound */
        sounds::SoundsManager::get().getFoundStarSound().play();

        /* increments the amount of found stars inside the dashboard */
        dashboard.incrementFoundStars();

        break;
    }
    case cells::MORE_LIFE_CELL:
    {
        /* plays the found life cell sound */
        sounds::SoundsManager::get().getFoundLifeSound().play();

        /* increments the amount of lifes inside the dashboard */
        dashboard.incrementLifes();

        break;
    }
    }
}

/**
 *
 */
void GameController::emptyPlayerCell()
{
    /* create an alias on the new player cell type, returned as a reference
       by the level getter */
    const char& playerCellType = level.getPlayerCellType();

    /* check if the player cell is one of the types that are never deleted */
    if (
        playerCellType == cells::EMPTY_CELL ||
        playerCellType == cells::DEPARTURE_CELL
    )
    {
        /* immediately ends the function; the current cell does not need to
           be empty even if the player is leaving it */
        return;
    }

    /* empty the player cell type */
    level.emptyPlayerCell();
}

}
}
