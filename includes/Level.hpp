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
     * TODO: the cells are not copied for now, all the cells are created as Empty Cells
     */
    Level(const Level &level);

    /**
     * @brief used to destroy the cells pointers array
     */
    ~Level();

    /**
     * @brief display all the cells of one floor
     *
     * @param pContext pointer to a context
     * @param floor number
     */
    void displayAllCellsByFloor(
        utils::Context* pContext,
        short floor = 0
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
    std::vector<Cell*>* getPointerCells();

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
    void loadCells(const std::string& levelString = "");

    /**
     * @brief hide all the cells of the level
     */
    void hideAllCells();

private:

    float horizontalPosition;
    float verticalPosition;

    std::string name;

    Cell* pSelectedCell;

    std::vector<Cell*> cells;
};
}

#endif
