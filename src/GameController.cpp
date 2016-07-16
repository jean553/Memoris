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
#include "CellFactory.hpp"
#include "fonts.hpp"
#include "window.hpp"
#include "controllers.hpp"
#include "SoundsManager.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "TexturesManager.hpp"

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
    /* TODO: use a constant level name for now... */
    level.loadCells(
        utils::Context::get(),
        ::utils::FileWriter::readFile(utils::Context::get().getNextLevelPathString())
    );
    level.setCellsCursorSensitivity(false);

    /* save the exact time the level starts to be displayed */
    displayLevelTime = utils::Context::get().getClockMillisecondsTime();
}

/**
 *
 */
unsigned short GameController::render()
{
    /* displays the game dashboard */
    dashboard.display();

    level.displayAllCellsByFloor(
        utils::Context::get(),
        floor
    );

    if (
        (status == WATCHING || status == PLAYING_AND_WATCHING) &&
        (
            utils::Context::get().getClockMillisecondsTime() -
            displayLevelTime > 5000
        )
    )
    {
        /* hide all the cells except departure */
        level.setAllCellsVisibility(true);

        /* set the player position on the departure only if
         * the game starts */
        if (status == WATCHING)
        {
            level.setDepartureCellAsEnabled();
        }
        else
        {
            level.setPlayerCellAsEnabled();
        }

        sounds::SoundsManager::get().getHideLevelSound().play();

        status = PLAYING;
    }

    nextControllerId = animateScreenTransition();

    while(utils::Context::get().getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                expectedControllerId =
                    MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Up:
            {
                movePlayer(UP);

                break;
            }
            case sf::Keyboard::Down:
            {
                movePlayer(DOWN);

                break;
            }
            case sf::Keyboard::Left:
            {
                movePlayer(LEFT);

                break;
            }
            case sf::Keyboard::Right:
            {
                movePlayer(RIGHT);

                break;
            }
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

    /* check if the game has to be finished according to the utils::Context::get() */
    if (terminateGame)
    {
        nextControllerId =
            MAIN_MENU_CONTROLLER_ID;
    }

    return nextControllerId;
}

/**
 *
 */
void GameController::movePlayer(PlayerDirection direction)
{
    /* try to move the player only if the current status is playing */
    if (
        status != PLAYING &&
        status != PLAYING_AND_WATCHING
    )
    {
        return;
    }

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

        status = PLAYING_AND_WATCHING;
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
