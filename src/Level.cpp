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
 * @file Level.cpp
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Level.hpp"
#include "EmptyCell.hpp"
#include "Dimensions.hpp"
#include "CellFactory.hpp"

using namespace entities;

const unsigned short Level::CELLS_STRING_STEP = 2;

/**
 *
 */
Level::Level(
    float hPosition,
    float vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    loadCells();

    pSelectedCell = NULL;
}

/**
 *
 */
Level::Level(const Level &level)
{
    name = level.name;

    /* TODO: the copy constructor does not copy the cells array,
    I need to investigate how to do it properly. By the way,
    I think I will change from a multi-dimensional array to
    a one-dimension array... */
    loadCells();

    horizontalPosition = level.horizontalPosition;
    verticalPosition = level.verticalPosition;
}

/**
 *
 */
Level::~Level()
{
    for (
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        delete (*cell);
    }
}

/**
 *
 */
void Level::displayAllCellsByFloor(
    utils::Context* pContext,
    short floor
)
{
    for (
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        /* TODO: useless check, just to avoid to change the function signature,
         * the floors are not browsed anymore, I have to check what later...*/
        if (floor > 10)
        {
            continue;
        }

        (*cell)->display(pContext);
    }
}

/**
 *
 */
void Level::setName(std::string levelName)
{
    name = levelName;
}

/**
 *
 */
std::string Level::getName() const
{
    return name;
}

/**
 *
 */
bool Level::isMouseHover(short floor)
{
    for (
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        /* TODO: use a fixed value for now, should be set according
         * to the current selected floor... */
        if (std::distance(cells.begin(), cell) >= 320 * (floor + 1))
        {
            continue;
        }

        if((*cell)->isMouseHover())
        {
            pSelectedCell = (*cell);
            return true;
        }
    }

    return false;
}

/**
 *
 */
entities::Cell* Level::getSelectedCellPointer() const
{
    return pSelectedCell;
}

/**
 *
 */
std::vector<Cell*>* Level::getPointerCells()
{
    return &cells;
}

/**
 *
 */
std::string Level::getCellsAsString()
{
    std::string cellsAsString;

    for (
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        cellsAsString += (*cell)->IN_FILE_REPRESENTATION;
    }

    return cellsAsString;
}

/**
 *
 */
void Level::loadCells(const std::string& levelString)
{
    float currentColumn = 0, currentLine = 0;
    short cellNumber = 0;
    uint16_t cellAddress = 0;

    for (uint16_t i = 0; i < constants::Dimensions::LEVEL_CELLS_PER_FLOOR; i++)
    {
        Cell* pNewCell = NULL;

        if (levelString.empty())
        {
            pNewCell = new EmptyCell();
        }
        else
        {
            pNewCell = factories::CellFactory::getCellPointerByStringName(
                           levelString.substr(static_cast<size_t>(cellNumber), 2)
                       );
        }

        pNewCell->setPosition(
            horizontalPosition +
            currentColumn *
            (
                constants::Dimensions::CELL_PIXELS_DIMENSIONS +
                constants::Dimensions::CELLS_PIXELS_SEPARATION
            ),
            verticalPosition +
            currentLine *
            (
                constants::Dimensions::CELL_PIXELS_DIMENSIONS +
                constants::Dimensions::CELLS_PIXELS_SEPARATION
            )
        );

        pNewCell->setLevelAddresses(cellAddress);
        cellAddress++;

        cells.push_back(pNewCell);

        currentLine++;
        if (currentLine >= constants::Dimensions::CELLS_PER_COLUMN)
        {
            currentLine = 0;
            currentColumn++;
        }

        cellNumber += CELLS_STRING_STEP;
    }
}
