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

#include "cells.hpp"
#include "window.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "animations.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
GameController::GameController(
    const std::shared_ptr<utils::Context>& context,
    std::shared_ptr<entities::Level> levelPtr
) :
    Controller(context),
    timer(
        context,
        295.f,
        10.f
    ),
    dashboard(context),
    watchingPeriodTimer(context),
    level(levelPtr)
{
    /* update the dashboard total stars amount according to the value returned
       by the level->object */
    /* TODO: #592 this way to do is bad: we got data from one object to
       directly set it as a value of another object, should be refactored */
    dashboard.updateTotalStarsAmountSurface(level->getStarsAmount());

    /* set the values inside the game timer countdown */
    timer.setMinutesAndSeconds(
        level->getMinutes(),
        level->getSeconds()
    );

    /* initialize the lose grey filter surface */
    initializeGreyFilter(context);

    /* initialize the lose text */
    initializeLoseText(context);

    /* initialize the win text */
    initializeWinText(context);

    /* apply the floors amount on the watching time */
    watchingPeriodTimer.applyFloorsAmount(level->getPlayableFloors());
}

/**
 *
 */
unsigned short GameController::render(
    const std::shared_ptr<utils::Context>& context
)
{
    /* check if the display level->time is equal to 0; if it is equal to 0,
       that means the level->just opened and this level->time has to be set */
    if (displayLevelTime == 0)
    {
        displayLevelTime = context->getClockMillisecondsTime();
    }

    /* displays the game dashboard */
    dashboard.display(context);

    /* displays the countdown widget */
    timer.display(context);

    /* displays the watching period timer if started */
    if (watchingPeriodTimer.isStarted())
    {
        watchingPeriodTimer.display(context);
    }

    /* starts the lose period if the countdown is finished; checks that the
       starting lose period time has not been set yet */
    if (timer.isFinished() && endPeriodStartTime == 0)
    {
        /* ends the level with the lose period */
        endLevel(context);
    }

    /* check if the level is currently rendering a floor switch animation */
    if (level->getAnimateFloorTransition())
    {
        /* renders the floor animation */
        level->playFloorTransitionAnimation(context);
    }
    /* if an animation is currently rendering, the rendering animation has to
       display the level during the whole animation time, that's why we do
       not call the display() function of the level but the display()
       method of the animation instead; if an animation is rendering, the
       animation pointer is pointing on something */
    else if (animation != nullptr)
    {
        /* the animation rendering method is called instead of the level
           rendering method; the animation has to handle this task during the
           whole animation process */
        animation->renderAnimation(
            context,
            level,
            floor
        );

        /* checks if the animation is terminated, if yes delete the
           animation */
        if (animation->isFinished())
        {
            /* some animations require a specific end */
            if (movePlayerToNextFloor)
            {
                /* increments the floor value */
                floor++;

                /* update the displayed floor value on the game dashboard */
                dashboard.updateCurrentFloor(floor);

                /* reset the boolean */
                movePlayerToNextFloor = false;
            }
            else if (movePlayerToPreviousFloor)
            {
                /* increments the floor value */
                floor--;

                /* update the displayed floor value on the game dashboard */
                dashboard.updateCurrentFloor(floor);

                /* reset the boolean */
                movePlayerToPreviousFloor = false;
            }

            /* reset() deletes the pointed object and set back the unique
               pointer to nullptr */
            animation.reset();
        }
    }
    else
    {
        /* renders a static playable level->if no animation are playing */
        level->display(
            context,
            floor
        );
    }

    /* displays all the cells of the level during the time of the watching
       period */
    /* TODO: #547 6000 ms is a default value, should be the actual bonus
       watching time of the player */
    if (
        watchingPeriod &&
        (
            context->getClockMillisecondsTime() -
            displayLevelTime >
            context->getPlayingSerieManager().getWatchingTime() * 1000
        )
    )
    {
        /* call the private method that display the next floor of the level
           in watching mode if necessary or stops the watching mode if all
           the playable floors have been watched */
        watchNextFloorOrHideLevel(context);
    }

    /* if the current game status is playing, the player cell has to be
       animated; we check if no animation is currently played; if an animation
       is playing, the player cursor is not animated at all */
    if (
        playingPeriod &&
        animation == nullptr &&
        (
            context->getClockMillisecondsTime() -
            playerCellAnimationTime > 100
        )
    )
    {
        /* increment the value of the transparency with the value 64; */
        playerCellTransparency += 64;

        /* modifies the transparency of the player cell color */
        level->setPlayerCellTransparency(
            context,
            playerCellTransparency
        );

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
            context->getClockMillisecondsTime();
    }

    /* check if the current game status is the win phase */
    if (endPeriodStartTime)
    {
        /* display the grey filter */
        context->getSfmlWindow().draw(greyFilter);

        /* display the win text or the lose text */
        if (win)
        {
            context->getSfmlWindow().draw(winText);
            context->getSfmlWindow().draw(winInformationText);

            /* animate the left levels amount surface */
            animateLeftLevelsAmount(context);
        }
        else
        {
            context->getSfmlWindow().draw(loseText);
        }

        /* check if the lose period is finished; the lose period duration is
           5 seconds */
        if (
            context->getClockMillisecondsTime() -
            endPeriodStartTime > 5000
        )
        {
            /* change the expected controller id according to the level
               status */
            expectedControllerId = win ?
                                   controllers::GAME_CONTROLLER_ID:
                                   controllers::MAIN_MENU_CONTROLLER_ID;
        }
    }

    /* used for the screen switch transition animation */
    nextControllerId = animateScreenTransition(context);

    /* the events loop of the game controller */
    while(context->getSfmlWindow().pollEvent(event))
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
                handlePlayerMovement(
                    context,
                    -20
                );

                break;
            }
            /* the down key is pressed down */
            case sf::Keyboard::Down:
            {
                handlePlayerMovement(
                    context,
                    20
                );

                break;
            }
            /* the left key is pressed down */
            case sf::Keyboard::Left:
            {
                handlePlayerMovement(
                    context,
                    -1
                );

                break;
            }
            /* the right key is pressed down */
            case sf::Keyboard::Right:
            {
                handlePlayerMovement(
                    context,
                    1
                );

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
                   the level-> even if the cells are not displayed during the
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
void GameController::handlePlayerMovement(
    const std::shared_ptr<utils::Context>& context,
    const short& movement
)
{
    /* NOTE: we voluntary do not refactor the two following conditions or use
       short-circuiting on them; in fact, we really want check the movement
       allowance first and end the function if the movement cannot be perfored,
       without starting to check the second condition */

    /* check if the game is in watching or lose period; in both cases, the
       movement is directly canceled; if an animation is currently rendering,
       the movement is forbidden too */
    if (
        watchingPeriod ||
        endPeriodStartTime ||
        animation != nullptr
    )
    {
        /* ends the current function and the movement is not allowed */
        return;
    }

    /* checks if the movement is actually allowed before performing it; we
       check if the player is not already on level->borders and is trying to
       move to the outside of the playable area */
    if (!level->allowPlayerMovement(movement, floor))
    {
        /* plays the collision sound */
        context->getSoundsManager().getCollisionSound().play();

        /* stop the process and do not move if the movement is not allowed */
        return;
    }

    /* check if the player is against a wall during the movement; if there is
       a collision, the wall is displayed by the condition function and the
       movement is cancelled */
    if (level->detectWalls(context, movement))
    {
        /* plays the collision sound */
        context->getSoundsManager().getCollisionSound().play();

        /* the movement is cancelled if the player is against a wall */
        return;
    }

    /* empty the current player cell before moving; some types are not cleared,
       that's what the function has to check */
    emptyPlayerCell(context);

    /* move the player, display walls if there are some collisions and show
       the new cell */
    level->movePlayer(
        context,
        movement
    );

    /* execute the action of the new player cell right after the movement */
    executePlayerCellAction(context);
}

/**
 *
 */
void GameController::executePlayerCellAction(
    const std::shared_ptr<utils::Context>& context
)
{
    /* create an alias on the new player cell type, returned as a reference
       by the level->getter */
    const char& newPlayerCellType = level->getPlayerCellType();

    /* NOTE: this switch only contains one case for now but expects to get
       almost one case per cell type */

    switch(newPlayerCellType)
    {
    case cells::STAR_CELL:
    {
        /* plays the found star cell sound */
        context->getSoundsManager().getFoundStarSound().play();

        /* increments the amount of found stars inside the dashboard */
        dashboard.incrementFoundStars();

        break;
    }
    case cells::MORE_LIFE_CELL:
    {
        /* plays the found life cell sound */
        context->getSoundsManager().getFoundLifeOrTimeSound().play();

        /* increments the amount of lifes inside the dashboard */
        dashboard.incrementLifes();

        break;
    }
    case cells::LESS_LIFE_CELL:
    {
        /* plays the sound of a dead cell */
        context->getSoundsManager().getFoundDeadOrLessTimeSound().play();

        /* check if the lose period must be started */
        if (dashboard.getLifesAmount() == 0)
        {
            endLevel(context);
        }

        /* decrement the amount of lifes */
        dashboard.decrementLifes();

        break;
    }
    case cells::MORE_TIME_CELL:
    {
        /* plays the found time cell sound */
        context->getSoundsManager().getFoundLifeOrTimeSound().play();

        /* increments the amount of watching time inside the dashboard */
        dashboard.increaseWatchingTime();

        break;
    }
    case cells::LESS_TIME_CELL:
    {
        /* plays the found less time cell sound */
        context->getSoundsManager().getFoundDeadOrLessTimeSound().play();

        /* decrease the amount of watching time inside the dasboard */
        dashboard.decreaseWatchingTime();

        break;
    }
    case cells::STAIRS_UP_CELL:
    {
        /* check if the player can be moved to the next floor (maybe it cannot
           because he is already on the last floor) */
        if (level->movePlayerToNextFloor(context))
        {
            /* set the animation value; for the stairs cells, the animation
               is a simple waiting period */
            animation = animations::getAnimationByCellType(
                            context,
                            newPlayerCellType
                        );

            /* remember that we have ot move the player on the next floor at
               the end of the animation */
            movePlayerToNextFloor = true;
        }

        break;
    }
    case cells::STAIRS_DOWN_CELL:
    {
        /* check if the player can be moved to the previous floor (maybe it
           cannot because he is already on the first floor) */
        if (level->movePlayerToPreviousFloor(context))
        {
            /* set the animation value; for the stairs cells, the animation
               is a simple waiting period */
            animation = animations::getAnimationByCellType(
                            context,
                            newPlayerCellType
                        );

            /* remember that we have ot move the player on the next floor at
               the end of the animation */
            movePlayerToPreviousFloor = true;
        }

        break;
    }
    case cells::ARRIVAL_CELL:
    {
        /* check if the all the star cells have been found */
        if (dashboard.getFoundStarsAmount() == level->getStarsAmount())
        {
            /* set the level as won */
            win = true;

            /* check if the loaded serie has a next level->to play */
            if (context->getPlayingSerieManager().hasNextLevel())
            {
                /* displays the win level screen */
                endLevel(context);
            }
            else
            {
                /* if the serie is finished, go back to the main menu */
                /* TODO: should go to another screen as a win screen */
                expectedControllerId = controllers::MAIN_MENU_CONTROLLER_ID;
            }
        }

        break;
    }
    /* all the animation cells are specified into this case; we do not create
       a case for each animation cell */
    case cells::HORIZONTAL_MIRROR_CELL:
    case cells::VERTICAL_MIRROR_CELL:
    case cells::DIAGONAL_CELL:
    case cells::LEFT_ROTATION_CELL:
    {
        /* starts the level animation according to the current player cell */
        animation = animations::getAnimationByCellType(
                        context,
                        newPlayerCellType
                    );

        break;
    }
    }
}

/**
 *
 */
void GameController::emptyPlayerCell(
    const std::shared_ptr<utils::Context>& context
)
{
    /* create an alias on the new player cell type, returned as a reference
       by the level->getter */
    const char& playerCellType = level->getPlayerCellType();

    /* check if the player cell is one of the types that are never deleted; we
       could use a test on an array here, but in order to improve visibility,
       we prefer these multiple conditions */
    if (
        playerCellType == cells::EMPTY_CELL ||
        playerCellType == cells::DEPARTURE_CELL ||
        playerCellType == cells::STAIRS_UP_CELL ||
        playerCellType == cells::STAIRS_DOWN_CELL ||
        playerCellType == cells::ARRIVAL_CELL ||
        playerCellType == cells::HORIZONTAL_MIRROR_CELL ||
        playerCellType == cells::VERTICAL_MIRROR_CELL ||
        playerCellType == cells::DIAGONAL_CELL
    )
    {
        /* immediately ends the function; the current cell does not need to
           be empty even if the player is leaving it */
        return;
    }

    /* empty the player cell type */
    level->emptyPlayerCell(context);
}

/**
 *
 */
void GameController::initializeGreyFilter(
    const std::shared_ptr<utils::Context>& context
)
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
        context->getColorsManager().getColorPartialDarkGrey()
    );
}

/**
 *
 */
void GameController::initializeLoseText(
    const std::shared_ptr<utils::Context>& context
)
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
    loseText.setFont(context->getFontsManager().getTextFont());

    /* the lose text is written in red color on the grey filter */
    loseText.setColor(context->getColorsManager().getColorRed());
}

/**
 *
 */
void GameController::initializeWinText(
    const std::shared_ptr<utils::Context>& context
)
{
    /* initialize the SFML text that is displayed when the player loses the
       game */

    winText.setPosition(
        480.f,
        100.f
    );
    winText.setString("You Win !");
    winText.setCharacterSize(fonts::TITLE_SIZE);
    winText.setFont(context->getFontsManager().getTextFont());
    winText.setColor(context->getColorsManager().getColorGreen());

    leftLevelsAmountText.setPosition(
        700.f,
        200.f
    );
    leftLevelsAmountText.setString(
        std::to_string(
            context->getPlayingSerieManager().getRemainingLevelsAmount()
        )
    );
    leftLevelsAmountText.setCharacterSize(fonts::LEVELS_COUNTDOWN_SIZE);
    leftLevelsAmountText.setFont(context->getFontsManager().getTextFont());
    leftLevelsAmountText.setColor(context->getColorsManager().getColorWhite());

    winInformationText.setPosition(
        560.f,
        650.f
    );
    winInformationText.setString("levels left");
    winInformationText.setCharacterSize(fonts::SUB_TITLE_SIZE);
    winInformationText.setFont(context->getFontsManager().getTextFont());
    winInformationText.setColor(
        context->getColorsManager().getColorDarkGreen()
    );
}

/**
 *
 */
void GameController::watchNextFloorOrHideLevel(
    const std::shared_ptr<utils::Context>& context
)
{
    /* check if the current displayed level->is the last one to display; the
       'floor' variable contains the current floor index, the level->public
       method returns an amount of floors, that's why we substract one */
    if (floor != level->getPlayableFloors() - 1)
    {
        /* increment the floor index to display the next floor cells */
        floor++;

        /* enable the animation of the floor transition */
        level->setAnimateFloorTransition(true);

        /* play the floor switch animation sound */
        context->getSoundsManager().getFloorSwitchSound().play();

        /* update the floor number inside the game dashboard */
        dashboard.updateCurrentFloor(floor);

        /* reset the display level->time with the current time to allow more
           watching time for the next floor watching period */
        displayLevelTime =
            context->getClockMillisecondsTime();

        /* ends the process here */
        return;
    }

    /* hide all the cells of the level->*/
    level->hideAllCellsExceptDeparture(context);

    /* plays the hide level->sound */
    context->getSoundsManager().getHideLevelSound().play();

    /* the watching mode is now terminated */
    watchingPeriod = false;

    /* the playing period starts now */
    playingPeriod = true;

    /* get the player floor index from the level->*/
    floor = level->getPlayerFloor();

    /* update the floor number inside the game dashboard */
    dashboard.updateCurrentFloor(floor);

    /* starts the countdown */
    timer.start();

    /* at this moment, we do not save the moment the animation ends; in
       fact, this is not a repeated action, there is no need to save
       the current time here */
}

/**
 *
 */
void GameController::endLevel(
    const std::shared_ptr<utils::Context>& context
)
{
    /* stop the music or play a specific sound according if the player has
       just won or lost */
    if (win)
    {
        /* plays the win level sound */
        context->getSoundsManager().getWinLevelSound().play();
    }
    else
    {
        /* force the music to stop */
        context->stopMusic();

        /* plays the time over sound */
        context->getSoundsManager().getTimeOverSound().play();
    }

    /* call the method to stop the timer */
    timer.stop();

    /* save when started the lose period time */
    endPeriodStartTime = context->getClockMillisecondsTime();
}

/**
 *
 */
void GameController::animateLeftLevelsAmount(
    const std::shared_ptr<utils::Context>& context
)
{
    /* display the amount of left levels */
    context->getSfmlWindow().draw(leftLevelsAmountText);

    /* check if at least 50 milliseconds elapsed between the last animation
       of the text surface */
    if (
        context->getClockMillisecondsTime() -
        leftLevelsAmountLastAnimationTime < 50
    )
    {
        /* does nothing if not enough time elapsed */
        return;
    }

    /* this part updates the transparency of the SFML surface */

    /* update the transparency of the surface, add or substract the current
       left amount animation direction */
    leftLevelsAmountTransparency += leftLevelsAmountDirection;

    /* toggle the direction of the animation if the alpha value is equal to 0
       or 255 (borders values) */
    if (
        leftLevelsAmountTransparency == 0 ||
        leftLevelsAmountTransparency == 255
    )
    {
        leftLevelsAmountDirection *= -1;
    }

    /* copy the color of the text from the colors manager; we have to do a
       copy because the transparency will be updated for the animation
       purposes */
    sf::Color color = context->getColorsManager().getColorWhiteCopy();

    /* change the alpha value of the SFML color */
    color.a = leftLevelsAmountTransparency;

    /* update the color */
    leftLevelsAmountText.setColor(color);

    /* store the time of the end of the animation update for the next
       update */
    leftLevelsAmountLastAnimationTime = context->getClockMillisecondsTime();
}

}
}
