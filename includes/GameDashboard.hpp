/**
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
 * @file GameDashboard.hpp
 * @brief the displayed dashboard inside the game controller, containing the
 * countdown and all the information labels
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAMEDASHBOARD_H_
#define MEMORIS_GAMEDASHBOARD_H_

#include "TimerWidget.hpp"

namespace memoris
{
namespace utils
{

class GameDashboard
{

public:

    /**
     * @brief constructor, initialize the timer widget, all the dashboard
     * informations labels and all the labels images
     */
    GameDashboard();

    /**
     * @brief overwritte the method to display the dashboard
     */
    void display();

    /**
     * @brief increments the found stars amount and updates the displayed found
     * stars amount text; this function is called by the game controller when
     * one new star is found by the player
     */
    void incrementFoundStars();

    /**
     * @brief increments the found lifes amount and updates the displayed found
     * lifes amount text; this action is called by the game controller
     */
    void incrementLifes();

    /**
     * @brief decrements the amount of lifes and update the displayed lifes
     * amount; this action is called by the game controller
     */
    void decrementLifes();

    /**
     * @brief increase the amount of seconds of the watching time by 3 seconds
     */
    void increaseWatchingTime();

    /**
     * @brief decrease the amount of seconds of the watching time by 3 seconds
     */
    void decreaseWatchingTime();

private:

    /* the graphical timer widget of the game; renders the elapsed time since
       the beginning of the game */
    widgets::TimerWidget timer;

    /* displays the amount of found stars in the current level */
    sf::Text foundStarsAmount;

    /* displays the amount of lifes the user got until now */
    sf::Text lifesAmount;

    /* displays the total amount of stars to find on this level */
    sf::Text target;

    /* displays the watch time the user has when a new level starts */
    sf::Text time;

    /* displays the current player level */
    sf::Text floor;

    /* the sprites for all the information labels images of the dashboard */
    sf::Sprite spriteStar;
    sf::Sprite spriteLife;
    sf::Sprite spriteTarget;
    sf::Sprite spriteTime;
    sf::Sprite spriteFloor;

    /* the two SFML surfaces that are the two separators on both sides of the
       level cells */
    sf::RectangleShape leftSeparator;
    sf::RectangleShape rightSeparator;

    /* the amount of stars to display in the dashboard; set with 0 by default
       because when the level starts, the found stars amount is always 0 */
    unsigned short foundStars {0};

    /* the amount of lifes to display in the dashboard */
    /* TODO: #579 this amount is 0 by default for now, but the default value
       should be extracted from the serie file if the level is the first one of
       the serie; it it is not the first one, the amount of lifes should be the
       lifes left the user has */
    unsigned short lifes {0};

    /* the amount of seconds the user can watch the level before hidding it */
    /* TODO: #583 default value is 0 for now, this value should be specified
       into the serie file if the played level is the first one and should be
       got from previous level if the current level is not the first one of the
       serie */
    unsigned short watchingTime {3};
};

}
}

#endif
