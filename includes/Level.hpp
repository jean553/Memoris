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
 * @file Level.hpp
 * @brief level entity, contains all the cells
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVEL_H_
#define MEMORIS_LEVEL_H_

#include "Cell.hpp"

#include <vector>
#include <memory>

namespace memoris
{
namespace entities
{

class Level
{

public:

    /**
     * @brief constructor, initialize all the cells of the level according to
     * the given level file path
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    Level();

    /**
     * @brief render the level and all the cells of the given floor; this
     * method is optimized and only calculate/render/display the cells of
     * the given floor; the other cells are totally ignored
     *
     * @param context shared pointer to the current context to use
     * @param floor the floor to render
     */
    void display(
        std::shared_ptr<utils::Context> context,
        const unsigned short& floor
    ) const;

    /**
     * @brief hides all the cells of the level, call the method (hide()) for
     * all of them except for departure cell(s)
     */
    void hideAllCellsExceptDeparture();

    /**
     * @brief update the transparency value of the current player color
     *
     * @param alpha the current player cell transparency value; we use a
     * sf::Uint8 value as this is the type used to set the colors of a
     * sf::Color object
     */
    void setPlayerCellTransparency(const sf::Uint8& alpha);

    /**
     * @brief move the player down if possible
     *
     * @param move the value (positive or negative) to apply on the current
     * player index; defines the mouvement of the player
     */
    void movePlayer(const short& movement);

    /**
     * @brief check if the player is allowed to perform the given movement;
     * this function is called from the game controller each time the player
     * trigger an event to move on the level
     *
     * @param move the value (positive or negative) to apply on the current
     * player index; defines the mouvement of the player; this check is
     * separated into a dedicated method for better code organisation
     * @param floor the current player floor number
     *
     * @return bool
     */
    bool allowPlayerMovement(
        const short& movement,
        const unsigned short& floor
    ) const;

    /**
     * @brief get the current player cell type; this getter is used into the
     * game controller to execute the correct current player cell event action
     *
     * @return const char&
     */
    const char& getPlayerCellType();

    /**
     * @brief check if the expected cell after the movement is a wall cell,
     * if yes, show the wall cell and forbid the movement; this function is
     * called by the game controller when the player is allowed to move, we
     * check if the user is currently in collision with a wall; if there is
     * a collision, the wall is shown
     *
     * @param movement the movement direction, the same as movePlayer()
     *
     * @return bool
     */
    bool detectWalls(const short& movement) const;

    /**
     * @brief updates the current player cell to an empty cell, whatever the
     * previous type; this method is called by the game controller to empty
     * a cell when the player leaves it; this method automatically forces the
     * load of a new texture for the player cell
     */
    void emptyPlayerCell();

    /**
     * @brief moves the current player to the next floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the next floor
     *
     * @bool true if the player moved to the next floor
     */
    bool movePlayerToNextFloor();

    /**
     * @brief moves the current player to the previous floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the previous floor
     *
     * @bool true if the player moved to the previous floor
     */
    bool movePlayerToPreviousFloor();

    /**
     * @brief getter of the total stars amount in the level; this is used by
     * the game controller to check when the user got all the stars of the
     * current played level
     *
     * @return const unsigned short&
     */
    const unsigned short& getStarsAmount();

    /**
     * @brief getter for the amount of playable floors; this is used to select
     * which floors have to be displayed during the watching period; this
     * amount is generated during the loading process of the level; it contains
     * the amount of floors (from the first one included) that contains at
     * least one non-empty cell
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayableFloors();

    /**
     * @brief getter for the current player floor index; we do not return
     * a reference because there is no attribute to store the player floor
     *
     * @return const unsigned short
     */
    const unsigned short getPlayerFloor();

    /**
     * @brief plays the floor transition animation; for now, the unique
     * animation renders a verical column that scroll the whole floor and
     * displays the next floor;
     *
     * NOTE: this method must be called instead of 'display()' during the
     * animation
     */
    void playFloorTransitionAnimation();

    /**
     * @brief setter for the animation boolean
     *
     * @param animate true if the animation must be rendered; the animation
     * can be displayed using the method playFloorTransitionAnimation()
     */
    void setAnimateFloorTransition(const bool& animate);

    /**
     * @brief getter for the animation boolean
     *
     * @return const bool&
     */
    const bool& getAnimateFloorTransition();

    /**
     * @brief getter for the minutes amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getMinutes() const;

    /**
     * @brief getter for the seconds amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getSeconds() const;

private:

    /* shared pointer to the context to use for rendering */
    std::shared_ptr<utils::Context> context;

    /* container of unique pointers of cells; we use unique pointers because
       pointers are fast to copy/move instead of a whole cell object; we use
       a unique pointer to make the pointer as restrictif as possible, in fact,
       we only use dynamic allocation to make the program run faster, so this
       is always better to limit the freedom of variables */
    std::vector<std::unique_ptr<Cell>> cells;

    /* the index of the current player cell; the position of the player in
       the level; the variable is 0 by default; */
    unsigned short playerIndex {0};

    /* the total amount of stars on the level; the default amount is 0 before
       the level file is loaded */
    unsigned short starsAmount {0};

    /* contains the amount of floors that are playable in this level; a
       playable floor is a floor with at least one cell non empty; this is
       used to select which floor to display during the watching period */
    unsigned short playableFloors {0};

    /* the amount of minutes loaded from the file for the current level */
    unsigned short minutes {0};

    /* the amount of seconds loaded from the file for the current level */
    unsigned short seconds {0};

    /* this boolean is true when a switch level animation is currently playing;
       this boolean is used by the game controller to starts the floor switch
       animation but also to know when the animate has been terminated by the
       level (using setter and getter) */
    bool animateFloorTransition {false};

    /* this is a SFML unsigned integer used to store the last update time of
       the current level animation; this variable can be used for any kind
       of level animation as only one animation can occure at a time */
    sf::Uint32 lastAnimationTime {0};

    /* the following variables are used for level animation and effects */

    /* the current column index on which one the animation occures; for
       example, during a floor switch animation, each column is hidden one
       by one and the content of the next level progressively appears; this
       variable is used to store the current 'breaking' column of the effect */
    unsigned short animationColumn {0};

    /* the current floor index is stored inside this variable when the switch
       floor animation occures; this is used by the animation; */
    unsigned short animationFloor {0};
};

}
}

#endif
