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
 * @file AnimatedBackground.cpp
 * @brief background animation
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AnimatedBackground.hpp"

#include "Context.hpp"
#include "Dimensions.hpp"
#include "CellFactory.hpp"
#include "CellsFileRepresentations.hpp"

#include <time.h>

namespace memoris
{
namespace utils
{

/**
 *
 */
AnimatedBackground& AnimatedBackground::AnimatedBackground::get()
{
    /* create the unique animated background instance */
    static AnimatedBackground singleton;

    /* return the unique singleton; as it is static, the unique one is always
       returned */
    return singleton;
}

/**
 *
 */
AnimatedBackground::AnimatedBackground() :
    others::NotCopiable()
{
    /* initialize all the cells */
    initializeCells();
}

/**
 *
 */
void AnimatedBackground::render()
{
    /* iterate all the cells and display them one by one; we use a reference
       because we do not copy the cells during the iteration */
    for (entities::Cell& cell : cells)
    {
        cell.display(utils::Context::get());
    }
}

/**
 *
 */
void AnimatedBackground::initializeCells()
{
    /* a container containing all the cells strings that can be used to
       randomly select the animated background cells */
    /* TODO: #488 bad idea, we have to update this container manually everytime
       we add new cells types */
    std::vector<std::string> cellsLib =
    {
        constants::CellsFileRepresentations::DEPARTURE_CELL,
        constants::CellsFileRepresentations::ARRIVAL_CELL,
        constants::CellsFileRepresentations::STAR_CELL,
        constants::CellsFileRepresentations::EMPTY_CELL,
        constants::CellsFileRepresentations::LIFE_CELL,
        constants::CellsFileRepresentations::DAMAGE_CELL,
        constants::CellsFileRepresentations::WALL_CELL,
        constants::CellsFileRepresentations::MORE_TIME_CELL,
        constants::CellsFileRepresentations::LESS_TIME_CELL,
        constants::CellsFileRepresentations::NULL_CELL,
    };

    /* the current line and the current column are used during the generation
       of all the cells of the background; they indicate the current address
       of the generated cell */
    unsigned short currentLine = 0, currentColumn = 0;

    /* the rand() function to generate random numbers return an integer */
    int randomNumber = 0;

    /* initialize random to generate random numbers */
    srand(time(NULL));

    /* we browse the array of cells; there are 576 cells to create */
    for (unsigned int i = 0; i < 576; i++)
    {
        /* select a cell randomly; the maximum value of the generated number
           is 16 even if there are only 10 different cells to generate; if the
           random number is more than 10, the 10 value will be used anyway, so
           there are more chances to get the value 10; this is because it is
           better to have manu "null cells" ( black cells ), to generate a
           beautiful background */
        randomNumber = rand() % 16;
        randomNumber = (
                           randomNumber >= cellsLib.size() ?
                           cellsLib.size() - 1 :
                           randomNumber
                       );

        /* generate the cell object from the cells factory according to the
           random number */
        entities::Cell cell =
            factories::CellFactory::getCellByStringName(
                cellsLib[randomNumber]
            );

        /* set the current cell position, calculated using the constant fixed
           dimensions of the cell and the current column/line of the
           iteration */
        cell.setPosition(
            currentColumn *
            (
                constants::Dimensions::CELL_PIXELS_DIMENSIONS +
                constants::Dimensions::CELLS_PIXELS_SEPARATION
            ),
            currentLine *
            (
                constants::Dimensions::CELL_PIXELS_DIMENSIONS +
                constants::Dimensions::CELLS_PIXELS_SEPARATION
            )
        );

        /* copy the cell object inside the cells container */
        cells.push_back(cell);

        /* increment the current line */
        currentLine++;

        /* the the current line is equal to the last line index, we reset the
           line index and we increment the column index; in fact, we start to
           generate cells in the next column */
        if (currentLine == 18)
        {
            /* reset the current line index */
            currentLine = 0;

            /* increment the current column */
            currentColumn++;
        }
    }
}

}
}
