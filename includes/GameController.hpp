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
#include "Level.hpp"
#include "WatchingPeriodTimer.hpp"
#include "LevelAnimation.hpp"
#include "TutorialWidget.hpp"

namespace memoris
{
namespace controllers
{

class GameController : public Controller
{

public:

    /**
     * @brief constructor, call the Level constructor that loads and create
     * the game level; initialize the watching time of the game
     *
     * @param context reference to the current context
     * @param levelPtr shared pointer to the level object to use
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    GameController(
        utils::Context& context,
        std::shared_ptr<entities::Level> levelPtr
    );

    /**
     * @brief renders the game main screen
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short& id of the new screen controller
     */
    virtual const unsigned short& render(utils::Context& context) & override 
        final;

private:

    /**
     * @brief function that refectors all the management related to the player
     * movement; this action is called everytime the player makes a move on
     * the level; it checks if the movement is allowed, move the player on
     * the level and executes the player's new cell action
     *
     * @param context reference to the current context to use
     * @param the numeric representation of the movement's direction,
     * the delta between the current player cell and the destination cell
     *
     * NOTE: the user can only moves to the left, right, top or bottom; that's
     * why the only possible values here are -20, 20, -1 and 1. These values
     * are not checked when the function is executed.
     */
    void handlePlayerMovement(
        utils::Context& context,
        const short& movement
    );

    /**
     * @brief applies the action of the new player cell; this method is called
     * immediately after the player moved
     *
     * @param context shared pointer to the context to use
     */
    void executePlayerCellAction(
        utils::Context& context
    );

    /**
     * @brief empties the player cell (the current player cell is switched to
     * an empty cell); this action is triggered everytime the player leaves
     * a cell; some types are never deleted from their original cell, this
     * function also checks that
     *
     * @param context shared pointer to the context to use
     */
    void emptyPlayerCell(utils::Context& context);

    /**
     * @brief initialize the grey filter surface that is displayed if the
     * player loses the game; this private method is called by the constructor;
     * the content of this method could be inside the controller itself, but
     * we put it inside a separated method for better organization
     *
     * @param context reference to the current context of the game
     */
    void initializeGreyFilter(utils::Context& context);

    /**
     * @brief initialize the lose text that is displayed when the player loses
     * the current game; this private method is called by the constructor;
     * the content of this method could be inside the controller itself, but
     * we put it inside a separated method for better organization
     *
     * @param context reference to the current context of the game
     */
    void initializeLoseText(utils::Context& context);

    /**
     * @brief initialize the win text that is displayed when the player wins
     *
     * @param context reference to the current context of the game
     */
    void initializeWinText(utils::Context& context);

    /**
     * @brief this method is called during the watching mode by the main
     * display method to jump to the next floor if the next floor is a playable
     * floor or to stop the watching period if there is no playable floor
     * anymore; this function is called at each 'watching time interval'
     *
     * @param context shared pointer to the context to use
     */
    void watchNextFloorOrHideLevel(
        utils::Context& context
    );

    /**
     * @brief this method ends the level, it displays the win or lose screen
     * according if the player has just won or lost the current level
     *
     * @param context shared pointer to the context to use
     */
    void endLevel(utils::Context& context);

    /**
     * @brief animate the displayed left level amount on the win screen
     *
     * @param context shared pointer to the context to use
     */
    void animateLeftLevelsAmount(
        utils::Context& context
    );

    /* the graphical timer widget of the game; renders the elapsed time since
       the beginning of the game */
    widgets::TimerWidget timer;

    /* contains the exact time when the level is displayed to the player; this
       is used for the "hide level" animation; we have to know when the level
       is rendered to calculate when we have to hide it; by default, the
       display level time is equal to 0, that means that the level has not been
       opened yet */
    sf::Uint32 displayLevelTime {0};

    /* the time of the last animation of the player cell animation */
    sf::Uint32 playerCellAnimationTime {0};

    /* the time of the last animation of the left levels amount on the win
       screen */
    sf::Uint32 leftLevelsAmountLastAnimationTime {0};

    /* this SFML variable contains when the lose period started; because this
       period is limited in time, this is used to make calculation and decide
       when the lose period stops, and when the current game stops; this
       variable is also used to check if the game is currently inside the
       lose period; if the lose period is enabled, this variable is positive
       for sure */
    sf::Uint32 endPeriodStartTime {0};

    /* the top dashboard that displays the countdown timer and all the
       current game information labels */
    utils::GameDashboard dashboard;

    /* the timer that is displayed on both of the left and right sides of the
       level during the watching period */
    utils::WatchingPeriodTimer watchingPeriodTimer;

    /* the level that contains all the cells to display */
    std::shared_ptr<entities::Level> level;

    /* pointer to the animation to play; there is no animation by default, so
       the pointer is null; the pointer is set back to null when an animation
       is finished */
    std::unique_ptr<animations::LevelAnimation> animation {nullptr};

    /* NOTE: the use a watching and a playing boolean; we use two different
       booleans; we might think that one boolean is enough to handle the
       actions (the player is watching or playing), but in fact, it can be
       necessary to display all the cells for a short time when the user is
       playing, for example, when the user got a visibility bonus */

    /* boolean that is true if all the cells of the level have to be
       displayed; by default, the watching period is enabled and the
       boolean is equal to true */
    bool watchingPeriod {true};

    /* this boolean is used to indicate when the current game period is playing
       and when the player can move over the cells; we do not only use one
       boolean even if we have only two states because we can have some special
       cases (visibility bonus for example: the cells are all hidden, so
       watching, but the player can still move, so playing); when the game
       starts, the player is watching the level, so the status is playing is
       false */
    bool playingPeriod {false};

    /* this boolean is used to remember if the user has just took a stairs up
       cell; if yes, we animate the level and then move the player; by default,
       the player does not move, so the boolean is false */
    bool movePlayerToNextFloor {false};
    bool movePlayerToPreviousFloor {false};

    /* this boolean is true when the player has just won the current level */
    bool win {false};

    /* the transparency of the player cell color; used to animate the current
       player cell with a flashing animation; we use a sf::Uint8 type because
       this is the one expected by the sf::Color object; the variable is
       initialized with the value 64 and switches between 64 and 128 */
    sf::Uint8 playerCellTransparency {64};

    /* the transparency of the left levels amount SFML text that is displayed
       on the win screen; used to animate it */
    sf::Uint8 leftLevelsAmountTransparency {255};

    /* used to update the transparency of the SFML surface, this value is
       continually updated between a signed and unsigned value */
    sf::Int8 leftLevelsAmountDirection {-17};

    /* the current floor of the player, by default for now, this current floor
       is the first floor (so number 0);*/
    /* TODO: #589 the default value of the current floor should be the
       departure cell floor value */
    unsigned short floor {0};

    /* the rectangle shape to apply and display on the screen during a short
       time when the player just lost the current playing game */
    sf::RectangleShape greyFilter;

    /* the SFML surfaces that are displayed when the player loses/wins the
       game */

    sf::Text loseText;
    sf::Text winText;
    sf::Text winInformationText;
    sf::Text leftLevelsAmountText;

    std::unique_ptr<widgets::TutorialWidget> tutorialWidget {nullptr};
};

}
}

#endif
