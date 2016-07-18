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
#include "dimensions.hpp"
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
    /* move the cells every 30 milliseconds */
    if(
        (
            utils::Context::get().getClockMillisecondsTime() -
            cellsMovementLastAnimation
        ) > 10
    )
    {
        for(
            std::vector<std::unique_ptr<entities::Cell>>::iterator cell =
                cells.begin();
            cell != cells.end();
            ++cell
        )
        {
            (**cell).moveOnTheRight();
        }

        /* update the new cells movement animation time with the new time */
        cellsMovementLastAnimation =
            utils::Context::get().getClockMillisecondsTime();
    }

    /* iterate all the cells and display them one by one; we use a reference
       because we do not copy the cells during the iteration */
    for(
        std::vector<std::unique_ptr<entities::Cell>>::iterator cell =
            cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        (**cell).display();
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
    unsigned short currentLine {0}, currentColumn {0};

    /* the rand() function to generate random numbers return an integer; we
       use an integer because the rand() function returns an integer; we
       unsigned the integer because of the comparison between this variable
       and the available cells array size (unsigned integer) */
    unsigned int randomNumber {0};

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
        /* NOTE: there is no need to cast the rand() value here, rand()
           returned a integer with a minimum of 0 (unsigned). */
        randomNumber = rand() % 16;
        randomNumber = (
                           randomNumber >= cellsLib.size() ?
                           cellsLib.size() - 1 :
                           randomNumber
                       );

        /* generate a new cell object, pointed by an unique pointer */
        std::unique_ptr<entities::Cell> cell(
            new entities::Cell(
                currentColumn *
                (
                    dimensions::CELL_PIXELS_DIMENSIONS +
                    dimensions::CELLS_PIXELS_SEPARATION
                ),
                currentLine *
                (
                    dimensions::CELL_PIXELS_DIMENSIONS +
                    dimensions::CELLS_PIXELS_SEPARATION
                ),
                cellsLib[randomNumber]
            )
        );

        /* move the cell object unique pointer into the container */
        cells.push_back(std::move(cell));

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
