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

#include "TimerWidget.hpp"
#include "GameDashboard.hpp"

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

    /* contains the exact time when the level is displayed to the player; this
       is used for the "hide level" animation; we have to know when the level
       is rendered to calculate when we have to hide it */
    /* NOTE: we do not initialize this variable here because the level opening
       time is got inside the constructor and assigned to the variable; that
       kind of action cannot be done in the header */
    sf::Uint32 displayLevelTime;

    /* the top dashboard that displays the countdown timer and all the
       current game information labels */
    utils::GameDashboard dashboard;

    /* NOTE: the use a watching and a playing boolean; we use two different
       booleans; we might think that one boolean is enough to handle the
       actions (the player is watching or playing), but in fact, it can be
       necessary to display all the cells for a short time when the user is
       playing, for example, when the user got a visibility bonus */

    /* boolean that is true if all the cells of the level have to be
       displayed; by default, the watching period is enabled and the
       boolean is equal to true */
    bool watchingPeriod {true};
};

}
}

#endif
