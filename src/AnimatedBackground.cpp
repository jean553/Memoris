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
#include "cells.hpp"

#include <time.h>

namespace memoris
{
namespace utils
{

/**
 *
 */
AnimatedBackground::AnimatedBackground(
    const std::shared_ptr<utils::Context>& context
)
{
    /* initialize all the cells */
    initializeCells(context);
}

/**
 *
 */
void AnimatedBackground::render(const std::shared_ptr<utils::Context>& context)
{
    /* move the cells every 30 milliseconds */
    if(
        (
            context->getClockMillisecondsTime() -
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
        cellsMovementLastAnimation = context->getClockMillisecondsTime();
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
        (**cell).display(context);
    }
}

/**
 *
 */
void AnimatedBackground::initializeCells(
    const std::shared_ptr<utils::Context>& context
)
{
    /* a container containing all the cells characters that can be used to
       randomly select the animated background cells; we declare this array
       using the annotation const char name[]: this creates only one object
       containing all the cells characters, existing only in the current
       variable scope and not in read-only */
    /* TODO: #488 bad idea, we have to update this container manually everytime
       we add new cells types */
    const char cellsLib[] =
    {
        cells::EMPTY_CELL,
        cells::DEPARTURE_CELL,
        cells::ARRIVAL_CELL,
        cells::STAR_CELL,
        cells::MORE_LIFE_CELL,
        cells::LESS_LIFE_CELL,
        cells::MORE_TIME_CELL,
        cells::LESS_TIME_CELL,
        cells::WALL_CELL,
        cells::STAIRS_UP_CELL,
        cells::STAIRS_DOWN_CELL
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

    /* initialize the random seed */
    srand(time(NULL));

    /* we browse the array of cells; there are 575 cells to create ( 576 (the
       total of displayed cells on the screen) - 1 because the first one is
       never drawn (top left corner) */
    for (unsigned int i = 0; i < 575; i++)
    {
        /* select a cell randomly; the maximum value of the generated number
           is 17 even if there are only 11 different cells to generate; if the
           random number is more than 11, the 11 value will be used anyway, so
           there are more chances to get the value 11; this is because it is
           better to have manu "null cells" ( black cells ), to generate a
           beautiful background */
        randomNumber = rand() % 17;

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

        /* the random number can be up to 16, there is no so much available
           cells type in the cells library; if the number is more than 16,
           the position is incremented for the next cell but the cell at the
           current position is not created; this is used to show some blank
           black spaces into the background; this is optimized because we
           do not create any useless cell (cell that is not displayed); we
           get the total size of the cells lib in bytes, divided by the size
           of one char type in bytes; like that, we can get the number of items
           into the cells lib automatically */
        if(randomNumber >= (sizeof(cellsLib) / sizeof(char)))
        {
            continue;
        }

        /* generate a new cell object, pointed by an unique pointer */
        std::unique_ptr<entities::Cell> cell(
            new entities::Cell(
                context,
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
    }
}

}
}
