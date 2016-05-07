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
 * Game interface.
 *
 * @file GameController.hpp
 * @brief main controller for the game
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_GAME_CONTROLLER
#define DEF_GAME_CONTROLLER

#include <SFML/Graphics.hpp>

#include "Controller.hpp"
#include "Level.hpp"
#include "CursorWidget.hpp"

namespace controllers
{
class GameController : public Controller
{
public:

    GameController();

    /**
     * @brief renders the game main screen
     *
     * @param pContext commons items for controller
     *
     * @return short    id of the new screen controller
     */
    unsigned short render(utils::Context* pContext);

private:

    /* do not use a const for casting problems with getElapsedTime().asMilliseconds() */
    static int32_t DEFAULT_WATCHING_TIME;

    static const std::string TEMPORARY_DEFAULT_LEVEL;

    /**
     * @enum GameController::GameStatus
     *
     * @brief gives information about the current status of the game
     */
    enum GameStatus
    {
        WATCHING, /* < the player is watching the level before playing */
        PLAYING /* < the player is playing the level and moving over the cells */
    };

    GameStatus status;

    entities::Level level;

    widgets::CursorWidget cursor;

    sf::Clock clock;
};
}

#endif
