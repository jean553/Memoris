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
 * @file GameController.hpp
 * @brief main game controller, renders the map and let the user play
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAMECONTROLLER_H_
#define MEMORIS_GAMECONTROLLER_H_

#include "Controller.hpp"

#include "Level.hpp"
#include "TimerWidget.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace memoris
{
namespace controllers
{

class GameController : public Controller
{
public:

    /**
     * @brief constructor
     */
    GameController();

    /**
     * @brief renders the game main screen
     *
     * @return unsigned short id of the new screen controller
     */
    unsigned short render();

private:

    /**
     * @brief tries to move the player in the given direction
     * only if the status of the game is playing
     *
     * @param direction specific direction
     */
    void movePlayer(PlayerDirection direction);

    /**
     * @brief checks the new player cell, trigger event according to this cell
     */
    void executeCellAction();

    /**
     * @brief set and increment the displayed value of the star counter
     */
    void updateStarCntStr();

    /**
     * @brief update the lifes string according to the lifes amount
     */
    void updateLifesCntStr();

    /**
     * @brief set and increment the displayed value of the watching time counter
     */
    void updateWatchingTimeStr();

    /**
     * @brief force the level to be updated according to a recent update
     * of the player position : the current cell is not animated anymore
     * but a new cell given as parameter is animated, selected and shown
     *
     * @param currCell pointer to the current cell to animate
     * @param newCell pointer to a new cell to animate
     */
    void selectNewCell(
        entities::Cell* currCell,
        entities::Cell* newCell
    );

    /* contains the exact time when the level is displayed to the player; this
       is used for the "hide level" animation; we have to know when the level
       is rendered to calculate when we have to hide it */
    /* NOTE: we do not initialize this variable here because the level opening
       time is got inside the constructor and assigned to the variable; that
       kind of action cannot be done in the header */
    sf::Uint32 displayLevelTime;

    /* the graphical timer widget of the game; renders the elapsed time since
       the beginning of the game */
    widgets::TimerWidget timer;

    /**
     * @enum GameController::GameStatus
     *
     * @brief gives information about the current status of the game
     */
    enum GameStatus
    {
        WATCHING, /* < the player is watching the level before playing */
        PLAYING, /* < the player is playing the level and moving over the cells */
        PLAYING_AND_WATCHING /* < the player just took a light bonus, he can move and watch */
    };

    uint16_t starCellsAmount;
    uint16_t foundStarCellsAmount;
    uint16_t lifesAmount;

    uint8_t floor;
    uint8_t watchTime;

    bool terminateGame;

    GameStatus status;

    entities::Level level;

    sf::Text foundStarsAmntStr;
    sf::Text lifesAmntStr;
    sf::Text targetStr;
    sf::Text timeStr;
    sf::Text floorStr;

    sf::Sprite spriteStar;
    sf::Sprite spriteLife;
    sf::Sprite spriteTarget;
    sf::Sprite spriteTime;
    sf::Sprite spriteFloor;

    sf::RectangleShape leftSeparator;
    sf::RectangleShape rightSeparator;
};

}
}

#endif
