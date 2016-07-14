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
 * Game main screen.
 *
 * @file GameController.cpp
 * @brief game main screen
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

namespace memoris
{
namespace controllers
{

/**
 *
 */
GameController::GameController() :
    Controller(),
    level(0, 0)
{
    displayLevelTime = utils::Context::get().getClockMillisecondsTime();

    starCellsAmount = 0;
    lifesAmount = 0;
    foundStarCellsAmount = 0;

    terminateGame = false;

    timeMilli = 0;
    timeSec = 0;
    timeMin = 0;
    floor = 0;

    /* TODO: depends of previous levels */
    watchTime = 6;

    status = WATCHING;

    level.setPosition(
        300,
        100
    );

    /* TODO: use a constant level name for now... */
    level.loadCells(
        utils::Context::get(),
        ::utils::FileWriter::readFile(utils::Context::get().getNextLevelPathString())
    );
    level.setCellsCursorSensitivity(false);

    time.setFont(memoris::fonts::FontsManager::get().getTextFont());
    time.setCharacterSize(memoris::fonts::TEXT_SIZE);
    time.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    time.setPosition(
        295,
        10
    );

    /* TODO: set a constant string for now, should change
     * according to the found stars... */
    foundStarsAmntStr.setFont(memoris::fonts::FontsManager::get().getTextFont());
    foundStarsAmntStr.setString("0");
    foundStarsAmntStr.setCharacterSize(memoris::fonts::TEXT_SIZE);
    foundStarsAmntStr.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    foundStarsAmntStr.setPosition(
        1200,
        -10
    );

    lifesAmntStr.setFont(memoris::fonts::FontsManager::get().getTextFont());
    lifesAmntStr.setString(std::to_string(lifesAmount));
    lifesAmntStr.setCharacterSize(memoris::fonts::TEXT_SIZE);
    lifesAmntStr.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    lifesAmntStr.setPosition(
        1200,
        35
    );

    timeStr.setFont(memoris::fonts::FontsManager::get().getTextFont());
    timeStr.setCharacterSize(memoris::fonts::TEXT_SIZE);
    timeStr.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    timeStr.setPosition(
        1050,
        35
    );

    /* TODO: static string for now... */
    floorStr.setFont(memoris::fonts::FontsManager::get().getTextFont());
    floorStr.setString(std::to_string(floor));
    floorStr.setCharacterSize(memoris::fonts::TEXT_SIZE);
    floorStr.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    floorStr.setPosition(
        900,
        -10
    );

    starCellsAmount = level.getStarCellsAmount();

    targetStr.setFont(memoris::fonts::FontsManager::get().getTextFont());
    targetStr.setString(std::to_string(starCellsAmount));
    targetStr.setCharacterSize(memoris::fonts::TEXT_SIZE);
    targetStr.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    targetStr.setPosition(
        1050,
        -10
    );

    textureStar.loadFromFile("res/images/star.png");
    textureLife.loadFromFile("res/images/life.png");
    textureTarget.loadFromFile("res/images/target.png");
    textureTime.loadFromFile("res/images/timer.png");
    textureFloor.loadFromFile("res/images/floor.png");

    spriteStar.setTexture(textureStar, true);
    spriteStar.setPosition(
        1250,
        0
    );

    spriteFloor.setTexture(textureFloor, true);
    spriteFloor.setPosition(
        950,
        0
    );

    spriteLife.setTexture(textureLife, true);
    spriteLife.setPosition(
        1250,
        50
    );

    spriteTarget.setTexture(textureTarget, true);
    spriteTarget.setPosition(
        1100,
        0
    );

    spriteTime.setTexture(textureTime, true);
    spriteTime.setPosition(
        1100,
        50
    );

    leftSeparator.setSize(
        sf::Vector2f(
            1,
            window::HEIGHT
        )
    );

    rightSeparator.setSize(
        sf::Vector2f(
            1,
            window::HEIGHT
        )
    );

    leftSeparator.setPosition(
        290,
        0
    );

    rightSeparator.setPosition(
        1308,
        0
    );

    leftSeparator.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());
    rightSeparator.setFillColor(memoris::colors::ColorsManager::get().getColorWhite());

    updateWatchingTimeStr();
}

/**
 *
 */
unsigned short GameController::render()
{
    level.displayAllCellsByFloor(
        utils::Context::get(),
        floor
    );

    /* update and display the timer */
    displayTime();

    utils::Context::get().getSfmlWindow().draw(spriteStar);
    utils::Context::get().getSfmlWindow().draw(spriteLife);
    utils::Context::get().getSfmlWindow().draw(spriteTarget);
    utils::Context::get().getSfmlWindow().draw(spriteTime);
    utils::Context::get().getSfmlWindow().draw(spriteFloor);
    utils::Context::get().getSfmlWindow().draw(foundStarsAmntStr);
    utils::Context::get().getSfmlWindow().draw(lifesAmntStr);
    utils::Context::get().getSfmlWindow().draw(targetStr);
    utils::Context::get().getSfmlWindow().draw(timeStr);
    utils::Context::get().getSfmlWindow().draw(floorStr);
    utils::Context::get().getSfmlWindow().draw(leftSeparator);
    utils::Context::get().getSfmlWindow().draw(rightSeparator);

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
        updateStarCntStr();
    }

    /* increment the amount of life cells if a life cell is found */
    if (currCellStrRep == constants::CellsFileRepresentations::LIFE_CELL)
    {
        lifesAmount++;
        updateLifesCntStr();
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
        updateLifesCntStr();
    }

    /* add three seconds if the cell is a time bonus */
    if (currCellStrRep == constants::CellsFileRepresentations::MORE_TIME_CELL)
    {
        watchTime += 3;
        updateWatchingTimeStr();
    }

    /* delete three seconds if the cell is a time malus */
    if (currCellStrRep == constants::CellsFileRepresentations::LESS_TIME_CELL)
    {
        watchTime -= 3;

        /* the watch time cannot be less than 3 */
        watchTime =
            watchTime < 3 ? 3 : watchTime;

        updateWatchingTimeStr();
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
void GameController::displayTime()
{
    /* update the time every 10 milliseconds, keep number
     * directly inside the code because they never change
     * according to the purposes of the function */
    if(
        utils::Context::get().getClockMillisecondsTime() -
        lastTimerUpdateTime > 10
    )
    {

        timeMilli++;
        if (timeMilli == 100)
        {
            timeMilli = 0;
            timeSec++;
            if (timeSec == 60)
            {
                timeSec = 0;
                timeMin++;
            }
        }

        time.setString(updateTimeStr());

        /* update the last timer update time with the current time at the
           end of the animation */
        lastTimerUpdateTime = utils::Context::get().getClockMillisecondsTime();
    }

    utils::Context::get().getSfmlWindow().draw(time);
}

/**
 *
 */
std::string GameController::updateTimeStr()
{
    std::string milliStr, minStr, secStr;

    /* directly use the number 10 as this value never
     * changes according to the purposes of the function */
    if (timeMilli < 10)
    {
        milliStr = "0" + std::to_string(timeMilli);
    }
    else
    {
        milliStr = std::to_string(timeMilli);
    }

    if (timeSec < 10)
    {
        secStr = "0" + std::to_string(timeSec);
    }
    else
    {
        secStr = std::to_string(timeSec);
    }

    if (timeMin < 10)
    {
        minStr = "0" + std::to_string(timeMin);
    }
    else
    {
        minStr = std::to_string(timeMin);
    }

    return minStr + " : " + secStr + " : " + milliStr;
}

/**
 *
 */
void GameController::updateStarCntStr()
{
    foundStarsAmntStr.setString(std::to_string(foundStarCellsAmount));
}

/**
 *
 */
void GameController::updateLifesCntStr()
{
    lifesAmntStr.setString(std::to_string(lifesAmount));
}

/**
 *
 */
void GameController::updateWatchingTimeStr()
{
    timeStr.setString(std::to_string(watchTime));
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
