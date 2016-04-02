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

namespace entities
{
class Level
{

public:

    /**
     * @brief position setter function
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
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
     * @brief display the level in a given context
     *
     * @param pContext pointer to a context
     */
    void displayAllCells(utils::Context* pContext);

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
     * @return bool returns true if the mouse is hover the level area
     */
    bool isMouseHover();

    /**
     * @brief returns a pointer to the current selected cell
     *
     * @return pointer to the current selected cell
     */
    entities::Cell* getSelectedCellPointer() const;

    /**
     * @brief returns cells array pointer
     *
     * @return double dimension vector pointer containing cells objects pointers
     */
    std::vector<std::vector<Cell*>>* getPointerCells();

    /**
     * @brief returns all the level cells as string
     *
     * @return string all cells IN_FILE_REPRESENTATION values
     */
    std::string getCellsAsString();

private:

    float horizontalPosition;
    float verticalPosition;

    std::string name;

    entities::Cell* pSelectedCell;

    std::vector<std::vector<Cell*>> cells;

    /**
     * @brief initialize the level cells to empty cell
     */
    void initializeWithEmptyCells();
};
}

#endif
