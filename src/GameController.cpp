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

#include "SoundsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "cells.hpp"
#include "window.hpp"
#include "fonts.hpp"
#include "controllers.hpp"

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
    /* update the dashboard total stars amount according to the value returned
       by the level object */
    /* TODO: #592 this way to do is bad: we got data from one object to
       directly set it as a value of another object, should be refactored */
    dashboard.updateTotalStarsAmountSurface(level.getStarsAmount());

    /* set the values inside the game timer countdown */
    /* TODO: set a fix default value for now, should read the value from the
       serie/level file */
    dashboard.setTimerMinutesAndSeconds(0, 30);

    /* initialize the lose grey filter surface */
    initializeGreyFilter();

    /* initialize the lose text */
    initializeLoseText();

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

    /* check if the level is currently rendering a floor switch animation */
    if (level.getAnimateFloorTransition())
    {
        /* renders the floor animation */
        level.playFloorTransitionAnimation();
    }
    else
    {

        /* renders a static playable level if no animation are playing */
        level.display(floor);
    }

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
        /* call the private method that display the next floor of the level
           in watching mode if necessary or stops the watching mode if all
           the playable floors have been watched */
        watchNextFloorOrHideLevel();
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

    /* check if the current game status is the lose phase */
    if (startLosePeriodTime)
    {
        /* display the grey filter */
        utils::Context::get().getSfmlWindow().draw(greyFilter);

        /* displays the lose text */
        utils::Context::get().getSfmlWindow().draw(loseText);

        /* check if the lose period is finished; the lose period duration is
           5 seconds */
        if (
            utils::Context::get().getClockMillisecondsTime() -
            startLosePeriodTime > 5000
        )
        {
            /* just go back to the serie selector */
            expectedControllerId =
                controllers::OFFICIAL_SERIES_MENU_CONTROLLER_ID;
        }
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

    /* check if the game is in watching or lose period; in both cases, the
       movement is directly canceled */
    if (watchingPeriod || startLosePeriodTime)
    {
        /* ends the current function and the movement is not allowed */
        return;
    }

    /* checks if the movement is actually allowed before performing it; we
       check if the player is not already on level borders and is trying to
       move to the outside of the playable area */
    if (!level.allowPlayerMovement(movement, floor))
    {
        /* plays the collision sound */
        sounds::SoundsManager::get().getCollisionSound().play();

        /* stop the process and do not move if the movement is not allowed */
        return;
    }

    /* check if the player is against a wall during the movement; if there is
       a collision, the wall is displayed by the condition function and the
       movement is cancelled */
    if (level.detectWalls(movement))
    {
        /* plays the collision sound */
        sounds::SoundsManager::get().getCollisionSound().play();

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
        sounds::SoundsManager::get().getFoundLifeOrTimeSound().play();

        /* increments the amount of lifes inside the dashboard */
        dashboard.incrementLifes();

        break;
    }
    case cells::LESS_LIFE_CELL:
    {
        /* plays the sound of a dead cell */
        sounds::SoundsManager::get().getFoundDeadOrLessTimeSound().play();

        /* check if the lose period must be started */
        if (dashboard.getLifesAmount() == 0)
        {
            handleLosePeriod();
        }

        /* decrement the amount of lifes */
        dashboard.decrementLifes();

        break;
    }
    case cells::MORE_TIME_CELL:
    {
        /* plays the found time cell sound */
        sounds::SoundsManager::get().getFoundLifeOrTimeSound().play();

        /* increments the amount of watching time inside the dashboard */
        dashboard.increaseWatchingTime();

        break;
    }
    case cells::LESS_TIME_CELL:
    {
        /* plays the found less time cell sound */
        sounds::SoundsManager::get().getFoundDeadOrLessTimeSound().play();

        /* decrease the amount of watching time inside the dasboard */
        dashboard.decreaseWatchingTime();

        break;
    }
    case cells::STAIRS_UP_CELL:
    {
        /* check if the player can be moved to the next floor (maybe it cannot
           because he is already on the last floor) */
        if (level.movePlayerToNextFloor())
        {
            /* if the player can move, increment the current player floor */
            floor++;

            /* update the floor number inside the game dashboard */
            dashboard.updateCurrentFloor(floor);
        }

        break;
    }
    case cells::STAIRS_DOWN_CELL:
    {
        /* check if the player can be moved to the previous floor (maybe it
           cannot because he is already on the first floor) */
        if (level.movePlayerToPreviousFloor())
        {
            /* if the player can move, decrement the current player floor */
            floor--;

            /* update the floor number inside the game dashboard */
            dashboard.updateCurrentFloor(floor);
        }

        break;
    }
    case cells::ARRIVAL_CELL:
    {
        /* check if the all the star cells have been found */
        if (dashboard.getFoundStarsAmount() == level.getStarsAmount())
        {
            /* TODO: when the level is completed, the game goes back to the
               main menu; at this moment of course, the next level should be
               loaded */
            expectedControllerId = controllers::MAIN_MENU_CONTROLLER_ID;
        }

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

    /* check if the player cell is one of the types that are never deleted; we
       could use a test on an array here, but in order to improve visibility,
       we prefer these multiple conditions */
    if (
        playerCellType == cells::EMPTY_CELL ||
        playerCellType == cells::DEPARTURE_CELL ||
        playerCellType == cells::STAIRS_UP_CELL ||
        playerCellType == cells::STAIRS_DOWN_CELL ||
        playerCellType == cells::ARRIVAL_CELL
    )
    {
        /* immediately ends the function; the current cell does not need to
           be empty even if the player is leaving it */
        return;
    }

    /* empty the player cell type */
    level.emptyPlayerCell();
}

/**
 *
 */
void GameController::initializeGreyFilter()
{
    /* create the grey rectangle shape that is displayed when the player loses
       the current game */

    /* the position of the filter is the left top corner as it is displayed on
       the whole screen */
    greyFilter.setPosition(0.f, 0.f);

    /* the size of the filter is the whole window size */
    greyFilter.setSize(
        sf::Vector2f(
            window::WIDTH,
            window::HEIGHT
        )
    );

    /* the color of the grey filter is grey with a light transparency */
    greyFilter.setFillColor(
        colors::ColorsManager::get().getColorPartialDarkGrey()
    );
}

/**
 *
 */
void GameController::initializeLoseText()
{
    /* initialize the SFML text that is displayed when the player loses the
       game */

    /* the text is aligned at the center of the window */
    loseText.setPosition(
        400.f,
        200.f
    );

    /* the text contains the lose message */
    loseText.setString("You Lose !");

    /* the size of the lose message is the same as the title items sizes */
    loseText.setCharacterSize(fonts::TITLE_SIZE);

    /* the font of the lose message is the normal text font */
    loseText.setFont(fonts::FontsManager::get().getTextFont());

    /* the lose text is written in red color on the grey filter */
    loseText.setColor(colors::ColorsManager::get().getColorRed());
}

/**
 *
 */
void GameController::watchNextFloorOrHideLevel()
{
    /* check if the current displayed level is the last one to display; the
       'floor' variable contains the current floor index, the level public
       method returns an amount of floors, that's why we substract one */
    if (floor != level.getPlayableFloors() - 1)
    {
        /* increment the floor index to display the next floor cells */
        floor++;

        /* enable the animation of the floor transition */
        level.setAnimateFloorTransition(true);

        /* play the floor switch animation sound */
        sounds::SoundsManager::get().getFloorSwitchSound().play();

        /* update the floor number inside the game dashboard */
        dashboard.updateCurrentFloor(floor);

        /* reset the display level time with the current time to allow more
           watching time for the next floor watching period */
        displayLevelTime =
            utils::Context::get().getClockMillisecondsTime();

        /* ends the process here */
        return;
    }

    /* hide all the cells of the level */
    level.hideAllCellsExceptDeparture();

    /* plays the hide level sound */
    sounds::SoundsManager::get().getHideLevelSound().play();

    /* the watching mode is now terminated */
    watchingPeriod = false;

    /* the playing period starts now */
    playingPeriod = true;

    /* get the player floor index from the level */
    floor = level.getPlayerFloor();

    /* update the floor number inside the game dashboard */
    dashboard.updateCurrentFloor(floor);

    /* at this moment, we do not save the moment the animation ends; in
       fact, this is not a repeated action, there is no need to save
       the current time here */
}

/**
 *
 */
void GameController::handleLosePeriod()
{
    /* force the music to stop */
    utils::Context::get().stopMusic();

    /* force the timer to stop in the dashboard */
    dashboard.stopTimer();

    /* save when started the lose period time */
    startLosePeriodTime =
        utils::Context::get().getClockMillisecondsTime();
}

}
}
