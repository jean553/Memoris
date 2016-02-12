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

#include "Cell.hpp"

#include "../utils/Context.hpp"

namespace entities {
class Level {

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
     * @brief used to destroy the cells pointers array
     */
    ~Level();

    /**
     * @brief display the level in a given context
     *
     * @param pContext pointer to a context
     */
    void displayAllCells(utils::Context* pContext);

private:

    std::vector<std::vector<Cell*>> cells;

    float horizontalPosition;
    float verticalPosition;
};
}

#endif