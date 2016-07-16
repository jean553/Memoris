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

#include "FileWriter.hpp"
#include "CellsFileRepresentations.hpp"
#include "controllers.hpp"
#include "SoundsManager.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
GameController::GameController() :
    Controller(),
    level(
        300,
        100
    )
{
    /* load all the cells of the level from the required level file */
    /* TODO: to refactor, this call construction is really bad... */
    level.loadCells(
        utils::FileWriter::readFile(
            utils::Context::get().getNextLevelPathString()
        )
    );

    /* do not change the color of a cell when the cursor mouse hover it */
    /* TODO: this should be the default behavior of the cells */
    level.setCellsCursorSensitivity(false);

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

    /* display all the cells of the player current floor */
    level.displayAllCellsByFloor(floor);

    /* displays all the cells of the level during the time of the watching
       period */
    /* TODO: 5000 ms is a default value, should be the actual bonus watching
       time of the player */
    if (
        watchingPeriod &&
        (
            utils::Context::get().getClockMillisecondsTime() -
            displayLevelTime > 5000
        )
    )
    {
        /* hide all the cells except departure */
        level.setAllCellsVisibility(true);

        /* when the game starts, the playing period is disabled; this is the
           first time we hide all the cells; when we hide all the cells for
           this first time, the player position is set on the departure cell;
           sometimes during the game, all the cells are displayed for a short
           time; when the cells are hidden again, we do not force the player
           to come back on the departure cell */
        if (!playingPeriod)
        {
            level.setDepartureCellAsEnabled();
        }

        /* plays the hide level sound */
        sounds::SoundsManager::get().getHideLevelSound().play();

        /* the watching mode is now terminated */
        watchingPeriod = false;

        /* the playing mode starts now */
        playingPeriod = true;

        /* at this moment, we do not save the moment the animation ends; in
           fact, this is not a repeated action, there is no need to save
           the current time here */
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
            /* the up key is pressed down */
            case sf::Keyboard::Up:
            {
                /* move up the player */
                movePlayer(UP);

                break;
            }
            /* the down key is pressed down */
            case sf::Keyboard::Down:
            {
                /* move down the player */
                movePlayer(DOWN);

                break;
            }
            /* the left key is pressed down */
            case sf::Keyboard::Left:
            {
                /* move the player on the left */
                movePlayer(LEFT);

                break;
            }
            /* the right key is pressed down */
            case sf::Keyboard::Right:
            {
                /* move the player on the right */
                movePlayer(RIGHT);

                break;
            }
            /* TODO: this is a cheat function, only in order to help during
               the game development and display all the cells; this function
               will be deleted */
            case sf::Keyboard::V:
            {
                level.setAllCellsVisibility(false);

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

    /* this condition checks if the game has to come back to the main menu
       controller page, if all the levels of the serie have been played and
       won by the user */
    if (terminateGame)
    {
        nextControllerId = MAIN_MENU_CONTROLLER_ID;
    }

    return nextControllerId;
}

/**
 *
 */
void GameController::movePlayer(PlayerDirection direction)
{
    /* when the current status of the game is not the 'playing' one; the
       player is not allowed to move at all */
    if (!playingPeriod)
    {
        return;
    }

    /* if the player is allowd to move, we call a level function to move him
       in the expected direction and update the level cells status */
    level.movePlayer(direction);

    /* execute the action of the new cell */
    executeCellAction();
}

/**
 *
 */
void GameController::executeCellAction()
{
    entities::Cell *prevCell = level.getPreviousPlayerCellPtr(),
                    *currCell = level.getPlayerCellPtr();
    std::vector<entities::Cell>* cells = level.getPointerCells();
    uint16_t addr = (level.getPlayerCellPtr())->getAddress();
    int8_t floorMvt = 0;

    if (prevCell == NULL || currCell == NULL)
    {
        return;
    }

    std::string currCellStrRep = currCell->getStringRepresentation();

    /* terminates the game if the player is on the arrival cell */
    if (
        currCellStrRep == constants::CellsFileRepresentations::ARRIVAL_CELL &&
        foundStarCellsAmount == starCellsAmount
    )
    {
        terminateGame = true;
    }

    /* increment the amount of found stars if a star is found */
    if (currCellStrRep == constants::CellsFileRepresentations::STAR_CELL)
    {
        foundStarCellsAmount++;
    }

    /* increment the amount of life cells if a life cell is found */
    if (currCellStrRep == constants::CellsFileRepresentations::LIFE_CELL)
    {
        lifesAmount++;
    }

    /* decrement the amount of life cells if a life cell is found */
    if (currCellStrRep == constants::CellsFileRepresentations::DAMAGE_CELL)
    {
        /* stop the game if the user has no life anymore */
        if (!lifesAmount)
        {
            terminateGame = true;
            return;
        }

        lifesAmount--;
    }

    /* add three seconds if the cell is a time bonus */
    if (currCellStrRep == constants::CellsFileRepresentations::MORE_TIME_CELL)
    {
        watchTime += 3;
    }

    /* delete three seconds if the cell is a time malus */
    if (currCellStrRep == constants::CellsFileRepresentations::LESS_TIME_CELL)
    {
        watchTime -= 3;

        /* the watch time cannot be less than 3 */
        watchTime =
            watchTime < 3 ? 3 : watchTime;
    }

    /* put back the player on the previous cell if the cell is a wall */
    if (currCellStrRep == constants::CellsFileRepresentations::WALL_CELL)
    {
        level.setPlayerCellPtr(prevCell);

        /* force the animation to stop on wall cell */
        currCell->setIsAnimated(false);
        currCell->setSelected(false);

        /* force animation on the previous cell */
        prevCell->setIsAnimated(true);
        prevCell->setSelected(true);
    }

    /* make the game visible during five seconds */
    if (currCellStrRep == constants::CellsFileRepresentations::LIGHT_CELL)
    {
        level.setAllCellsVisibility(false);

        /* all the level is now visible, the watching period is temporary
           enabled */
        watchingPeriod = true;

        /* save the current time, this is used to show the level cells only
           during a dedicated period of time */
        displayLevelTime = utils::Context::get().getClockMillisecondsTime();
    }

    /* update the current display floor and player position if the cell is a stair cell */
    if (currCellStrRep == constants::CellsFileRepresentations::FLOOR_UP_CELL)
    {
        floorMvt = 1;
    }

    if (currCellStrRep == constants::CellsFileRepresentations::FLOOR_DOWN_CELL)
    {
        floorMvt = -1;
    }

    if (floorMvt != 0)
    {
        floor += floorMvt;

        selectNewCell(
            currCell,
            &(*cells)[addr + 320 * floorMvt]
        );
    }

    /* delete the star if the previous cell was a star */
    if (
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::STAR_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::LIFE_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::DAMAGE_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::MORE_TIME_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::LESS_TIME_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::LIGHT_CELL
    )
    {
        prevCell->setStringRepresentation(
            constants::CellsFileRepresentations::EMPTY_CELL
        );
    }
}

/**
 *
 */
void GameController::selectNewCell(
    entities::Cell* currCell,
    entities::Cell* newCell
)
{
    level.setPlayerCellPtr(newCell);

    currCell->setIsAnimated(false);
    currCell->setSelected(false);

    newCell->setIsAnimated(true);
    newCell->setSelected(true);
    newCell->setHidden(false);
}

}
}
