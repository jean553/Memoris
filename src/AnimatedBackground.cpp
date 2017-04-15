/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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

#include "cells.hpp"
#include "Cell.hpp"

namespace memoris
{
namespace utils
{

class AnimatedBackground::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
    {
    }

    std::vector<std::unique_ptr<entities::Cell>> cells;

    sf::Uint32 cellsMovementLastAnimation {0};

    const utils::Context& context;
};

/**
 *
 */
AnimatedBackground::AnimatedBackground(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    /* this is a complex initialization, 
       so it is handled by a dedicated method */
    initializeCells();
}

/**
 *
 */
AnimatedBackground::~AnimatedBackground() = default;

/**
 *
 */
void AnimatedBackground::render() const &
{
    const auto& context = impl->context;

    const auto& currentTime = context.getClockMillisecondsTime();
    auto& lastTime = impl->cellsMovementLastAnimation;

    auto& cells = impl->cells;

    auto moveCells = false;

    constexpr sf::Uint32 ANIMATION_INTERVAL {10};
    if(currentTime - lastTime > ANIMATION_INTERVAL)
    {
        moveCells = true;

        lastTime = currentTime;
    }

    for(const auto& cell : cells)
    {
        const auto& cellObject = *cell;

        if (moveCells)
        {
            cellObject.moveOnTheRight();
        }

        cellObject.display(context);
    }
}

/**
 *
 */
void AnimatedBackground::initializeCells() const &
{
    /* used for random value generation */
    srand(time(NULL));

    unsigned short currentLine {0}, currentColumn {0};

    constexpr unsigned short BACKGROUND_CELLS_AMOUNT {575};

    for (
        unsigned short index {0};
        index < BACKGROUND_CELLS_AMOUNT;
        index++
    )
    {
        currentLine++;

        constexpr unsigned short CELLS_PER_COLUMN {18};
        if (currentLine == CELLS_PER_COLUMN)
        {
            currentLine = 0;
            currentColumn++;
        }

        const auto cellType = getCellByRandomNumber(); 

        if (cellType == 0)
        {
            continue;
        }

        constexpr float CELL_PIXELS_DIMENSIONS {49.f};
        constexpr float CELLS_PIXELS_SEPARATION {1.f};
        auto cell = std::make_unique<entities::Cell>(
            impl->context,
            currentColumn *
            (
                CELL_PIXELS_DIMENSIONS +
                CELLS_PIXELS_SEPARATION
            ),
            currentLine *
            (
                CELL_PIXELS_DIMENSIONS +
                CELLS_PIXELS_SEPARATION
            ),
            cellType
        );

        impl->cells.push_back(std::move(cell));
    }
}

/**
 *
 */
const char AnimatedBackground::getCellByRandomNumber() const & noexcept
{
    using namespace cells;

    constexpr unsigned short MAXIMUM_RANDOM_NUMBER {28};
    const unsigned short random = rand() % MAXIMUM_RANDOM_NUMBER;

    switch(random)
    {
    case 0:
    {
        return EMPTY_CELL;
    }
    case 1:
    {
        return DEPARTURE_CELL;
    }
    case 2:
    {
        return ARRIVAL_CELL;
    }
    case 3:
    {
        return STAR_CELL;
    }
    case 4:
    {
        return MORE_LIFE_CELL;
    }
    case 5:
    {
        return LESS_LIFE_CELL;
    }
    case 6:
    {
        return MORE_TIME_CELL;
    }
    case 7:
    {
        return LESS_TIME_CELL;
    }
    case 8:
    {
        return WALL_CELL;
    }
    case 9:
    {
        return STAIRS_UP_CELL;
    }
    case 10:
    {
        return STAIRS_DOWN_CELL;
    }
    case 11:
    {
        return HORIZONTAL_MIRROR_CELL;
    }
    case 12:
    {
        return VERTICAL_MIRROR_CELL;
    }
    case 13:
    {
        return DIAGONAL_CELL;
    }
    case 14:
    {
        return LEFT_ROTATION_CELL;
    }
    case 15:
    {
        return RIGHT_ROTATION_CELL;
    }
    case 16:
    {
        return ELEVATOR_UP_CELL;
    }
    case 17:
    {
        return ELEVATOR_DOWN_CELL;
    }
    default:
    {
        return 0;
    }
    }
}

}
}
