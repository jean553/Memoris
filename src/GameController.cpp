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
#include "Window.hpp"

using namespace controllers;

const std::string GameController::TEMPORARY_DEFAULT_LEVEL = "data/levels/1.level";
const std::string GameController::STAR_IMG_PATH = "res/images/star.png";
const std::string GameController::LIFE_IMG_PATH = "res/images/life.png";
const std::string GameController::TOTAL_STARS_IMG_PATH = "res/images/target.png";
const std::string GameController::TIME_IMG_PATH = "res/images/timer.png";
const std::string GameController::FLOOR_IMG_PATH = "res/images/floor.png";

const float_t GameController::LEVEL_HORIZONTAL_POSITION = 300;
const float_t GameController::LEVEL_VERTICAL_POSITION = 100;

int32_t GameController::DEFAULT_WATCHING_TIME = 5000;

const uint8_t GameController::TIMER_ITRVL = 10;
const uint8_t GameController::WATCH_TIME_INCREMENTATION = 3;

const uint16_t GameController::TIMER_HRTL_PSTN = 295;
const uint16_t GameController::TIMER_VRTL_PSTN = 10;
const uint16_t GameController::STAR_HRTL_PSTN = 1250;
const uint16_t GameController::STAR_VRTL_PSTN = 0;
const uint16_t GameController::LIFE_HRTL_PSTN = 1250;
const uint16_t GameController::LIFE_VRTL_PSTN = 50;
const uint16_t GameController::FOUND_STAR_CELLS_HRTL_PSTN = 1200;
const int16_t GameController::FOUND_STAR_CELLS_VRTL_PSTN = -10;
const uint16_t GameController::LIFES_HRTL_PSTN = 1200;
const uint16_t GameController::LIFES_VRTL_PSTN = 35;

const float_t GameController::TOTAL_STARS_HRTL_PSTN = 1050;
const float_t GameController::TOTAL_STARS_VRTL_PSTN = -10;
const float_t GameController::TARGET_HRTL_PSTN = 1100;
const float_t GameController::TARGET_VRTL_PSTN = 0;
const float_t GameController::TIME_HRTL_PSTN = 1050;
const float_t GameController::TIME_VRTL_PSTN = 35;
const float_t GameController::TIME_IMG_HRTL_PSTN = 1100;
const float_t GameController::TIME_IMG_VRTL_PSTN = 50;
const float_t GameController::LEFT_SEPARATOR_PSTN = 290;
const float_t GameController::RIGHT_SEPARATOR_PSTN = 1308;
const float_t GameController::FLOOR_HRTL_PSTN = 900;
const float_t GameController::FLOOR_VRTL_PSTN = -10;
const float_t GameController::FLOOR_IMG_HRTL_PSTN = 950;
const float_t GameController::FLOOR_IMG_VRTL_PSTN = 0;

/**
 *
 */
GameController::GameController() : Controller(), level(0, 0)
{
    starCellsAmount = 0;
    lifesAmount = 0;
    foundStarCellsAmount = 0;

    terminateGame = false;

    timeMilli = 0;
    timeSec = 0;
    timeMin = 0;
    floor = 0;

    /* TODO: depends of previous levels */
    watchTime = 5;

    status = WATCHING;

    level.setPosition(
        LEVEL_HORIZONTAL_POSITION,
        LEVEL_VERTICAL_POSITION
    );

    /* TODO: use a constant level name for now... */
    level.loadCells(utils::FileWriter::readFile(TEMPORARY_DEFAULT_LEVEL));
    level.setCellsCursorSensitivity(false);

    fontTime.loadFromFile(constants::Fonts::getTextFontPath());

    colorItems.r = constants::Colors::COLOR_WHITE_RED;
    colorItems.g = constants::Colors::COLOR_WHITE_GREEN;
    colorItems.b = constants::Colors::COLOR_WHITE_BLUE;
    colorItems.a = constants::Colors::COLOR_ALPHA_FULL;

    time.setFont(fontTime);
    time.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    time.setColor(colorItems);
    time.setPosition(
        TIMER_HRTL_PSTN,
        TIMER_VRTL_PSTN
    );

    /* TODO: set a constant string for now, should change
     * according to the found stars... */
    foundStarsAmntStr.setFont(fontTime);
    foundStarsAmntStr.setString("0");
    foundStarsAmntStr.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    foundStarsAmntStr.setColor(colorItems);
    foundStarsAmntStr.setPosition(
        FOUND_STAR_CELLS_HRTL_PSTN,
        FOUND_STAR_CELLS_VRTL_PSTN
    );

    /* TODO: set a constant string for now, should change
     * according to the amount of lifes */
    lifesAmntStr.setFont(fontTime);
    lifesAmntStr.setString(std::to_string(lifesAmount));
    lifesAmntStr.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    lifesAmntStr.setColor(colorItems);
    lifesAmntStr.setPosition(
        LIFES_HRTL_PSTN,
        LIFES_VRTL_PSTN
    );

    timeStr.setFont(fontTime);
    timeStr.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    timeStr.setColor(colorItems);
    timeStr.setPosition(
        TIME_HRTL_PSTN,
        TIME_VRTL_PSTN
    );

    /* TODO: static string for now... */
    floorStr.setFont(fontTime);
    floorStr.setString(std::to_string(floor));
    floorStr.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    floorStr.setColor(colorItems);
    floorStr.setPosition(
        FLOOR_HRTL_PSTN,
        FLOOR_VRTL_PSTN
    );

    starCellsAmount = level.getStarCellsAmount();

    targetStr.setFont(fontTime);
    targetStr.setString(std::to_string(starCellsAmount));
    targetStr.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    targetStr.setColor(colorItems);
    targetStr.setPosition(
        TOTAL_STARS_HRTL_PSTN,
        TOTAL_STARS_VRTL_PSTN
    );

    soundBuffer.loadFromFile(constants::Sounds::HIDE_LEVEL_SOUND_PATH);
    soundHideLevel.setBuffer(soundBuffer);

    textureStar.loadFromFile(STAR_IMG_PATH);
    textureLife.loadFromFile(LIFE_IMG_PATH);
    textureTarget.loadFromFile(TOTAL_STARS_IMG_PATH);
    textureTime.loadFromFile(TIME_IMG_PATH);
    textureFloor.loadFromFile(FLOOR_IMG_PATH);

    spriteStar.setTexture(textureStar, true);
    spriteStar.setPosition(
        STAR_HRTL_PSTN,
        STAR_VRTL_PSTN
    );

    spriteFloor.setTexture(textureFloor, true);
    spriteFloor.setPosition(
        FLOOR_IMG_HRTL_PSTN,
        FLOOR_IMG_VRTL_PSTN
    );

    spriteLife.setTexture(textureLife, true);
    spriteLife.setPosition(
        LIFE_HRTL_PSTN,
        LIFE_VRTL_PSTN
    );

    spriteTarget.setTexture(textureTarget, true);
    spriteTarget.setPosition(
        TARGET_HRTL_PSTN,
        TARGET_VRTL_PSTN
    );

    spriteTime.setTexture(textureTime, true);
    spriteTime.setPosition(
        TIME_IMG_HRTL_PSTN,
        TIME_IMG_VRTL_PSTN
    );

    leftSeparator.setSize(
        sf::Vector2f(
            1,
            constants::Window::HEIGHT
        )
    );

    rightSeparator.setSize(
        sf::Vector2f(
            1,
            constants::Window::HEIGHT
        )
    );

    leftSeparator.setPosition(
        LEFT_SEPARATOR_PSTN,
        0
    );

    rightSeparator.setPosition(
        RIGHT_SEPARATOR_PSTN,
        0
    );

    leftSeparator.setFillColor(colorItems);
    rightSeparator.setFillColor(colorItems);

    updateWatchingTimeStr();
}

/**
 *
 */
unsigned short GameController::render(utils::Context* pContext)
{
    /* TODO: only displays the first floor, default value of
     * the second parameter is 0, should be able to switch */
    level.displayAllCellsByFloor(pContext);

    /* update and display the timer */
    displayTime(pContext);

    pContext->getWindow()->draw(spriteStar);
    pContext->getWindow()->draw(spriteLife);
    pContext->getWindow()->draw(spriteTarget);
    pContext->getWindow()->draw(spriteTime);
    pContext->getWindow()->draw(spriteFloor);
    pContext->getWindow()->draw(foundStarsAmntStr);
    pContext->getWindow()->draw(lifesAmntStr);
    pContext->getWindow()->draw(targetStr);
    pContext->getWindow()->draw(timeStr);
    pContext->getWindow()->draw(floorStr);
    pContext->getWindow()->draw(leftSeparator);
    pContext->getWindow()->draw(rightSeparator);

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
        watchTime += WATCH_TIME_INCREMENTATION;
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

    /* delete the star if the previous cell was a star */
    if (
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::STAR_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::LIFE_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::DAMAGE_CELL ||
        prevCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::MORE_TIME_CELL
    )
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
