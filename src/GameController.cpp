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

using namespace controllers;

const std::string GameController::TEMPORARY_DEFAULT_LEVEL = "data/levels/1.level";

const float_t GameController::LEVEL_HORIZONTAL_POSITION = 320;
const float_t GameController::LEVEL_VERTICAL_POSITION = 50;

int32_t GameController::DEFAULT_WATCHING_TIME = 5000;

/**
 *
 */
GameController::GameController() : Controller(), level(0, 0)
{
    level.setPosition(
        LEVEL_HORIZONTAL_POSITION,
        LEVEL_VERTICAL_POSITION
    );

    /* TODO: use a constant level name for now... */
    level.loadCells(utils::FileWriter::readFile(TEMPORARY_DEFAULT_LEVEL));

    level.setCellsCursorSensitivity(false);

    status = WATCHING;
}

/**
 *
 */
unsigned short GameController::render(utils::Context* pContext)
{
    /* TODO: only displays the first floor, default value of
     * the second parameter is 0, should be able to switch */
    level.displayAllCellsByFloor(pContext);

    if (
        status == WATCHING &&
        clock.getElapsedTime().asMilliseconds() >
        DEFAULT_WATCHING_TIME
    )
    {
        level.hideAllCells();
        level.setDepartureCellAsEnabled();

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
                level.movePlayer(UP);

                break;
            }
            case sf::Keyboard::Down:
            {
                level.movePlayer(DOWN);

                break;
            }
            case sf::Keyboard::Left:
            {
                level.movePlayer(LEFT);

                break;
            }
            case sf::Keyboard::Right:
            {
                level.movePlayer(RIGHT);

                break;
            }
            }
        }
        }
    }

    return nextControllerId;
}
