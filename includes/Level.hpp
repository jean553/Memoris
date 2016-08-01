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
     * @param string reference to the level file path, this path is got from
     * the playing serie manager; we do not directly get it inside the
     * constructor because we will have two constructors for the level; one
     * to initialize a level from a file (this one) and one to initialize an
     * empty level
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    Level(const std::string& path);

    /**
     * @brief render the level and all the cells of the given floor; this
     * method is optimized and only calculate/render/display the cells of
     * the given floor; the other cells are totally ignored
     *
     * @param floor the floor to render
     */
    void display(const unsigned short& floor) const;

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

private:

    /* container of unique pointers of cells; we use unique pointers because
       pointers are fast to copy/move instead of a whole cell object; we use
       a unique pointer to make the pointer as restrictif as possible, in fact,
       we only use dynamic allocation to make the program run faster, so this
       is always better to limit the freedom of variables */
    std::vector<std::unique_ptr<Cell>> cells;

    /* the index of the current player cell; the position of the player in
       the level; the variable is 0 by default; */
    unsigned short playerIndex {0};
};

}
}

#endif
