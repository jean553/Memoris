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

#include <time.h>

#include "AnimatedBackground.hpp"
#include "Dimensions.hpp"
#include "CellFactory.hpp"
#include "CellsFileRepresentations.hpp"
#include "Window.hpp"

using namespace utils;

const uint16_t AnimatedBackground::TOTAL_CELLS_AMNT = 576;

const uint8_t AnimatedBackground::RANDOM_MAX = 16;
const uint8_t AnimatedBackground::LINES_AMNT = 18;
const uint8_t AnimatedBackground::COLS_AMNT = 32;
const uint8_t AnimatedBackground::ANIMATION_INTERVAL = 10;

const int8_t AnimatedBackground::CELL_ORIGINAL_HRTL_PSTN = -49;

/**
 *
 */
AnimatedBackground::AnimatedBackground()
{
    initializeCellsLib();
    initializeCells();
}

/**
 *
 */
void AnimatedBackground::animate(utils::Context* ctx)
{
    changeCellsPosition();

    for (
        std::vector<entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        cell->display(ctx);
    }
}

/**
 *
 */
void AnimatedBackground::initializeCells()
{
    uint16_t cellAddress = 0;
    uint8_t currentLine = 0, currentColumn = 0, rdm = 0;

    /* initialize random seed for random numbers */
    srand(time(NULL));

    for (uint16_t i = 0; i < TOTAL_CELLS_AMNT; i++)
    {
        entities::Cell cell;

        /* select a cell randomly */
        rdm = rand() % RANDOM_MAX;

        /* adapt the cell to display */
        rdm = ( rdm >= cellsLib.size() ? cellsLib.size() - 1 : rdm );

        cell =
            factories::CellFactory::getCellPointerByStringName(cellsLib[rdm]);

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

        cell.setLevelAddresses(cellAddress);
        cellAddress++;

        cells.push_back(cell);

        currentLine++;
        if (currentLine >= LINES_AMNT)
        {
            currentLine = 0;

            currentColumn++;
            if (currentColumn >= COLS_AMNT)
            {
                currentColumn = 0;
            }
        }
    }
}

/**
 *
 */
void AnimatedBackground::changeCellsPosition()
{
    if(clock.getElapsedTime().asMilliseconds() <= ANIMATION_INTERVAL)
    {
        return;
    }

    float_t hrtlPstn = 0, vrtlPstn = 0;

    for (
        std::vector<entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        hrtlPstn = cell->getHorizontalPosition();
        vrtlPstn = cell->getVerticalPosition();

        hrtlPstn += 1;

        /* put back the cell at the beginning if the cell is out of the screen */
        if (hrtlPstn > constants::Window::WIDTH)
        {
            hrtlPstn = CELL_ORIGINAL_HRTL_PSTN;
        }

        cell->setPosition(hrtlPstn, vrtlPstn);
    }

    clock.restart();
}

/**
 *
 */
void AnimatedBackground::initializeCellsLib()
{
    cellsLib =
    {
        constants::CellsFileRepresentations::DEPARTURE_CELL,
        constants::CellsFileRepresentations::ARRIVAL_CELL,
        constants::CellsFileRepresentations::STAR_CELL,
        constants::CellsFileRepresentations::EMPTY_CELL,
        constants::CellsFileRepresentations::LIFE_CELL,
        constants::CellsFileRepresentations::DAMAGE_CELL,
        constants::CellsFileRepresentations::WALL_CELL,
        constants::CellsFileRepresentations::NULL_CELL
    };
}
