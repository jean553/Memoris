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
#include "ControllerFactory.hpp"
#include "FileWriter.hpp"
#include "Sounds.hpp"
#include "CellsFileRepresentations.hpp"
#include "CellFactory.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"

using namespace controllers;

const std::string GameController::TEMPORARY_DEFAULT_LEVEL = "data/levels/1.level";

const float_t GameController::LEVEL_HORIZONTAL_POSITION = 300;
const float_t GameController::LEVEL_VERTICAL_POSITION = 100;

int32_t GameController::DEFAULT_WATCHING_TIME = 5000;

const uint8_t GameController::TIMER_ITRVL = 10;

const uint16_t GameController::TIMER_HRTL_PSTN = 295;
const uint16_t GameController::TIMER_VRTL_PSTN = 10;

/**
 *
 */
GameController::GameController() : Controller(), level(0, 0)
{
    timeMilli = 0;
    timeSec = 0;
    timeMin = 0;

    fontTime.loadFromFile(constants::Fonts::getTextFontPath());

    colorTime.r = constants::Colors::COLOR_WHITE_RED;
    colorTime.g = constants::Colors::COLOR_WHITE_GREEN;
    colorTime.b = constants::Colors::COLOR_WHITE_BLUE;
    colorTime.a = constants::Colors::COLOR_ALPHA_FULL;

    time.setFont(fontTime);
    time.setString("00 : 00 : 00");
    time.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    time.setColor(colorTime);
    time.setPosition(
        TIMER_HRTL_PSTN,
        TIMER_VRTL_PSTN
    );

    level.setPosition(
        LEVEL_HORIZONTAL_POSITION,
        LEVEL_VERTICAL_POSITION
    );

    /* TODO: use a constant level name for now... */
    level.loadCells(utils::FileWriter::readFile(TEMPORARY_DEFAULT_LEVEL));

    level.setCellsCursorSensitivity(false);

    status = WATCHING;

    starCellsAmount = level.getStarCellsAmount();
    foundStarCellsAmount = 0;

    terminateGame = false;

    soundBuffer.loadFromFile(constants::Sounds::HIDE_LEVEL_SOUND_PATH);
    soundHideLevel.setBuffer(soundBuffer);
}

/**
 *
 */
unsigned short GameController::render(utils::Context* pContext)
{
    /* TODO: only displays the first floor, default value of
     * the second parameter is 0, should be able to switch */
    level.displayAllCellsByFloor(pContext);

    displayTime(pContext);

    if (
        status == WATCHING &&
        clock.getElapsedTime().asMilliseconds() >
        DEFAULT_WATCHING_TIME
    )
    {
        /* hide all the cells except departure */
        level.setAllCellsVisibility(true);
        level.setDepartureCellAsEnabled();

        soundHideLevel.play();

        status = PLAYING;
        clock.restart();
    }

    nextControllerId = animateScreenTransition(pContext);

    while(pContext->getWindow()->pollEvent(event))
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
                    factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

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
            }
        }
        }
    }

    /* check if the game has to be finished according to the context */
    if (terminateGame)
    {
        nextControllerId =
            factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
    }

    return nextControllerId;
}

/**
 *
 */
void GameController::movePlayer(PlayerDirection direction)
{
    /* try to move the player only if the current status is playing */
    if (status != PLAYING)
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
    entities::Cell* prevCell = level.getPreviousPlayerCellPtr();
    entities::Cell* currCell = level.getPlayerCellPtr();

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

    /* delete the star if the previous cell was a star */
    if (prevCell->getStringRepresentation() ==
            constants::CellsFileRepresentations::STAR_CELL)
    {
        prevCell->setStringRepresentation(
            constants::CellsFileRepresentations::EMPTY_CELL
        );
        prevCell->setPicturePath(
            factories::CellFactory::EMPTY_CELL_PICTURE_PATH
        );
    }
}

/**
 *
 */
void GameController::displayTime(utils::Context* ctx)
{
    /* update the time every 10 milliseconds, keep number
     * directly inside the code because they never change
     * according to the purposes of the function */
    if(timeClck.getElapsedTime().asMilliseconds() >= TIMER_ITRVL)
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
        timeClck.restart();
    }

    ctx->getWindow()->draw(time);
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
