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

class AnimatedBackground::Impl
{

public:

    std::vector<std::unique_ptr<entities::Cell>> cells;

    sf::Uint32 cellsMovementLastAnimation {0};
};

/**
 *
 */
AnimatedBackground::AnimatedBackground(utils::Context& context) :
    impl(std::make_unique<Impl>())
{
    initializeCells(context);
}

/**
 *
 */
AnimatedBackground::~AnimatedBackground() noexcept = default;

/**
 *
 */
void AnimatedBackground::render(const utils::Context& context) const &
{
    if(
        (
            context.getClockMillisecondsTime() -
            impl->cellsMovementLastAnimation
        ) > 10
    )
    {
        for(auto& cell : impl->cells) // auto->std::unique_ptr<entities::Cell>&
        {
            (*cell).moveOnTheRight();
        }

        impl->cellsMovementLastAnimation = context.getClockMillisecondsTime();
    }

    for(auto& cell : impl->cells) // auto->std::unique_ptr<entities::Cell>&
    {
        (*cell).display(context);
    }
}

/**
 *
 */
void AnimatedBackground::initializeCells(utils::Context& context) &
{
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

    unsigned short currentLine {0}, currentColumn {0};

    /* the rand() function to generate random numbers return an integer; we
       use an integer because the rand() function returns an integer; we
       unsigned the integer because of the comparison between this variable
       and the available cells array size (unsigned integer) */
    unsigned int randomNumber {0};

    srand(time(NULL));

    for (unsigned int i = 0; i < 575; i++)
    {
        /* select a cell randomly; the maximum value of the generated number
           is 17 even if there are only 11 different cells to generate; if the
           random number is more than 11, the 11 value will be used anyway, so
           there are more chances to get the value 11; this is because it is
           better to have manu "null cells" ( black cells ), to generate a
           beautiful background */
        randomNumber = rand() % 17;

        currentLine++;

        if (currentLine == 18)
        {
            currentLine = 0;

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

        impl->cells.push_back(std::move(cell));
    }
}

}
}
