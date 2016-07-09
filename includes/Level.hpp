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
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_LEVEL
#define DEF_LEVEL

#include <vector>
#include <string>

#include "Cell.hpp"
#include "Context.hpp"
#include "HiddenCellPicture.hpp"

enum PlayerDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

namespace entities
{
class Level
{
    static const unsigned short CELLS_STRING_STEP;

public:

    /**
     * @brief position setter function
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     *
     * NOTE: the cells are not initialized inside
     * the constructor, the caller controller has
     * to call the loadCells method
     */
    Level(
        float hPosition,
        float vPosition
    );

    /**
     * @brief copy constructor
     *
     * @param context current context reference
     * @param level reference to the level to copy
     *
     * TODO: the cells are not copied for now, all the cells are created as Empty Cells
     */
    Level(
        memoris::utils::Context& context,
        const Level &level
    );

    /**
     * @brief used to destroy the cells pointers array
     */
    ~Level();

    /**
     * @brief display all the cells of one floor
     *
     * @param context pointer to a context
     * @param floor number
     */
    void displayAllCellsByFloor(
        memoris::utils::Context& context,
        const uint8_t& floor = 0
    );

    /**
     * @brief name setter
     *
     * @param levelName name of the level
     */
    void setName(std::string levelName);

    /**
     * @brief name getter
     *
     * @return string
     */
    std::string getName() const;

    /**
     * @brief check if the mouse is hover one of the level cells
     *
     * @param floor number
     *
     * @return bool returns true if the mouse is hover the level area
     */
    bool isMouseHover(short floor);

    /**
     * @brief returns a pointer to the current selected cell
     *
     * @return pointer to the current selected cell
     */
    entities::Cell* getSelectedCellPointer() const;

    /**
     * @brief returns cells array pointer
     *
     * @return vector pointer containing cells objects pointers
     */
    std::vector<Cell>* getPointerCells();

    /**
     * @brief returns all the level cells as string
     *
     * @return string all cells IN_FILE_REPRESENTATION values
     */
    std::string getCellsAsString();

    /**
     * @brief set level cells from given string, load empty
     * cells level if no string are specified
     *
     * @param levelString string representation of the level
     */
    void loadCells(
        memoris::utils::Context& context,
        const std::string& levelString = ""
    );

    /**
     * @brief hide all the cells of the level
     *
     * @param hidden true if the cells are hidden
     */
    void setAllCellsVisibility(const bool& hidden);

    /**
     * @brief set the cursor sensitivity of all the level's cells
     *
     * @param sensitivity true if the level's cells are sensible to the cursor
     */
    void setCellsCursorSensitivity(const bool& sensitivity);

    /**
     * @brief setter for the level position
     *
     * @param vPosition horizontal position
     * @param hPosition vertical position
     */
    void setPosition(
        const float& hPosition,
        const float& vPosition
    );

    /**
     * @brief set the departure cell as enabled,
     * should be used when the level is hidden
     */
    void setDepartureCellAsEnabled();

    /**
     * @brief change the position of the player cell,
     * according to the given array index
     *
     * @param index current position in the cells array
     */
    void setPlayerCellIndex(const uint16_t& index);

    /**
     * @brief mode down player position
     */
    void movePlayer(const PlayerDirection& direction);

    /**
     * @brief check if the move of the player is possible
     * according to its current location and the given direction
     *
     * @param direction specified direction
     * @param currentIndex current position of the player
     *
     * @return bool
     */
    bool playerIsMovable(
        const PlayerDirection& direction,
        const uint16_t& currentIndex
    );

    /**
     * @brief returns the amount of star cells
     *
     * @return uint16_t
     */
    uint16_t getStarCellsAmount();

    /**
     * @brief setter for the current player position cell
     *
     * @param Cell* pointer to a cell
     */
    void setPlayerCellPtr(entities::Cell* ptrPlayerCell);

    /**
     * @brief getter for the player cell pointer
     *
     * @return Cell*
     */
    entities::Cell* getPlayerCellPtr() const;

    /**
     * @brief getter for the previous player cell pointer
     *
     * @return Cell*
     */
    entities::Cell* getPreviousPlayerCellPtr() const;

    /**
     * @brief set the current player cell as enabled
     */
    void setPlayerCellAsEnabled();

private:

    /**
     * @brief initialize basic attributes
     */
    void initializeSomeCommonCells();

    float horizontalPosition;
    float verticalPosition;

    std::string name;

    Cell* pSelectedCell;

    uint16_t departureCellIndex;

    std::vector<Cell> cells;

    /* pointer to the current player position cell */
    Cell* pPlayerCell;

    /* pointer to the previous cell where was the player,
     * useful when the content of the cell has to disapeared
     * after found */
    Cell* pPreviousPlayerCell;
};
}

#endif
