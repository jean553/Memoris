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

using namespace entities;

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

    initializeWithEmptyCells();

    pSelectedCell = NULL;
}

/**
 *
 */
Level::Level(const Level &level)
{
    name = level.name;

    //TODO: should not be empty cells but given level cells
    initializeWithEmptyCells();

    horizontalPosition = level.horizontalPosition;
    verticalPosition = level.verticalPosition;
}

/**
 *
 */
Level::~Level()
{
    for (std::vector<std::vector<Cell*>>::iterator line = cells.begin();
            line != cells.end(); ++line)
    {
        for (std::vector<Cell*>::iterator cell = line->begin();
                cell != line->end(); ++cell)
        {
            delete (*cell);
        }
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
    // cast as the index of a vector is always unsigned long
    std::vector<Cell*> line = cells[static_cast<unsigned long>(floor)];

    for (std::vector<Cell*>::iterator cell = line.begin();
            cell != line.end(); ++cell)
    {
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
    // cast as the index of a vector is always unsigned long
    std::vector<Cell*> line = cells[static_cast<unsigned long>(floor)];

    for (std::vector<Cell*>::iterator cell = line.begin();
            cell != line.end(); ++cell)
    {
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
void Level::initializeWithEmptyCells()
{
    float currentColumn = 0, currentLine = 0;
    short floorAddress = 0, cellAddress = 0;

    cells.resize(constants::Dimensions::LEVEL_FLOORS);
    for (std::vector<std::vector<Cell*>>::iterator line = cells.begin();
            line != cells.end(); ++line)
    {

        line->resize(constants::Dimensions::LEVEL_CELLS_PER_FLOOR);

        for (std::vector<Cell*>::iterator cell = line->begin();
                cell != line->end(); ++cell)
        {

            (*cell) = new EmptyCell();

            (*cell)->setPosition(
                horizontalPosition +
                currentColumn *
                (constants::Dimensions::CELL_PIXELS_DIMENSIONS + constants::Dimensions::CELLS_PIXELS_SEPARATION),
                verticalPosition +
                currentLine *
                (constants::Dimensions::CELL_PIXELS_DIMENSIONS + constants::Dimensions::CELLS_PIXELS_SEPARATION)
            );

            (*cell)->setLevelAddresses(
                floorAddress,
                cellAddress
            );

            currentLine++;

            if (currentLine >= constants::Dimensions::CELLS_PER_COLUMN)
            {
                currentLine = 0;
                currentColumn++;
            }

            cellAddress++;
        }

        floorAddress++;
        cellAddress = 0;

        currentColumn = 0;
        currentLine = 0;
    }
}

/**
 *
 */
std::vector<std::vector<Cell*>>* Level::getPointerCells()
{
    return &cells;
}

/**
 *
 */
std::string Level::getCellsAsString()
{
    std::string cellsAsString;

    for (std::vector<std::vector<Cell*>>::iterator line = cells.begin();
            line != cells.end(); ++line)
    {
        for (std::vector<Cell*>::iterator cell = line->begin();
                cell != line->end(); ++cell)
        {
            cellsAsString += (*cell)->IN_FILE_REPRESENTATION;
        }
    }

    return cellsAsString;
}
