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

#include "dimensions.hpp"
#include "CellFactory.hpp"
#include "CellsFileRepresentations.hpp"
#include "Context.hpp"

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
    initializeSomeCommonCells();

    horizontalPosition = hPosition;
    verticalPosition = vPosition;
}

/**
 *
 */
Level::Level(const Level &level)
{
    initializeSomeCommonCells();

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
void Level::initializeSomeCommonCells()
{
    departureCellIndex = 0;
    pPlayerCell = NULL;
    pSelectedCell = NULL;
    pPreviousPlayerCell = NULL;
}

/**
 *
 */
Level::~Level()
{
}

/**
 *
 */
void Level::displayAllCellsByFloor(const uint8_t& floor)
{
    for (
        std::vector<memoris::entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        if (
            std::distance(cells.begin(), cell) >=
            floor * memoris::dimensions::LEVEL_CELLS_PER_FLOOR &&
            std::distance(cells.begin(), cell) <
            floor * memoris::dimensions::LEVEL_CELLS_PER_FLOOR +
            memoris::dimensions::LEVEL_CELLS_PER_FLOOR
        )
        {
            cell->display(memoris::utils::Context::get());
        }
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
        std::vector<memoris::entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        if (
            std::distance(cells.begin(), cell) >=
            floor * memoris::dimensions::LEVEL_CELLS_PER_FLOOR &&
            std::distance(cells.begin(), cell) <
            floor * memoris::dimensions::LEVEL_CELLS_PER_FLOOR +
            memoris::dimensions::LEVEL_CELLS_PER_FLOOR
        )
        {
            if(cell->isMouseHover())
            {
                /* yeah... we want the address of the cell pointed by the cell iterator... */
                pSelectedCell = &*cell;
                return true;
            }
        }
    }

    return false;
}

/**
 *
 */
memoris::entities::Cell* Level::getSelectedCellPointer() const
{
    return pSelectedCell;
}

/**
 *
 */
std::vector<memoris::entities::Cell>* Level::getPointerCells()
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
        std::vector<memoris::entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        cellsAsString += cell->getStringRepresentation();
    }

    return cellsAsString;
}

/**
 *
 */
void Level::loadCells(const std::string& levelString)
{
    short cellNumber = 0;
    uint16_t cellAddress = 0, currentLine = 0, currentColumn = 0;

    for (uint16_t i = 0; i < memoris::dimensions::CELLS_PER_LEVEL; i++)
    {
        memoris::entities::Cell newCell(memoris::utils::Context::get());

        if (levelString.empty())
        {
            newCell.setStringRepresentation(constants::CellsFileRepresentations::EMPTY_CELL);
        }
        else
        {
            newCell = factories::CellFactory::getCellByStringName(
                          levelString.substr(static_cast<size_t>(cellNumber), 2)
                      );
        }

        newCell.setPosition(
            horizontalPosition +
            currentColumn *
            (
                memoris::dimensions::CELL_PIXELS_DIMENSIONS +
                memoris::dimensions::CELLS_PIXELS_SEPARATION
            ),
            verticalPosition +
            currentLine *
            (
                memoris::dimensions::CELL_PIXELS_DIMENSIONS +
                memoris::dimensions::CELLS_PIXELS_SEPARATION
            )
        );

        newCell.setLevelAddresses(cellAddress);

        /* save the departure cell */
        if (
            newCell.getStringRepresentation() ==
            constants::CellsFileRepresentations::DEPARTURE_CELL
        )
        {
            departureCellIndex = cellAddress;
        }

        cellAddress++;

        cells.push_back(newCell);

        currentLine++;
        if (currentLine >= memoris::dimensions::CELLS_PER_COLUMN)
        {
            currentLine = 0;

            currentColumn++;
            if (currentColumn >= 20)
            {
                currentColumn = 0;
            }
        }

        cellNumber += CELLS_STRING_STEP;
    }
}

/**
 *
 */
void Level::setAllCellsVisibility(const bool& hidden)
{
    for (
        std::vector<memoris::entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        cell->setHidden(hidden);
    }
}

/**
 *
 */
void Level::setCellsCursorSensitivity(const bool& sensitivity)
{
    for (
        std::vector<memoris::entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        cell->setCursorSensitivity(sensitivity);
    }
}

/**
 *
 */
void Level::setPosition(
    const float& hPosition,
    const float& vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;
}

/**
 *
 */
void Level::setDepartureCellAsEnabled()
{
    /* the player cell position is the same as the departure one */
    setPlayerCellIndex(departureCellIndex);
}

/**
 *
 */
void Level::setPlayerCellIndex(const uint16_t& index)
{
    /* the player cell pointer is null the first
     * time the method is called */
    if (pPlayerCell != NULL)
    {
        pPlayerCell->setSelected(false);

        /* set the previous player cell only if cell is not null */
        pPreviousPlayerCell = pPlayerCell;
    }

    /* the player cell is now at the new array position */
    pPlayerCell = &cells[index];

    /* the player cell is selected and not hidden */
    pPlayerCell->setSelected(true);
    pPlayerCell->setHidden(false);
    pPlayerCell->setIsAnimated(true);
}

/**
 *
 */
void Level::movePlayer(const PlayerDirection& direction)
{
    const uint16_t currentIndex =
        pPlayerCell->getAddress();
    uint16_t newIndex = 0;

    /* do not move the player if the player is not movable */
    if (!playerIsMovable(direction, currentIndex))
    {
        return;
    }

    /* change the position of the player according
     * to the selected direction */
    if (direction == DOWN)
    {
        newIndex = currentIndex + 1;
    }
    else if (direction == UP)
    {
        newIndex = currentIndex - 1;
    }
    else if (direction == LEFT)
    {
        newIndex = currentIndex -
                   memoris::dimensions::CELLS_PER_COLUMN;
    }
    else
    {
        newIndex = currentIndex +
                   memoris::dimensions::CELLS_PER_COLUMN;
    }

    setPlayerCellIndex(newIndex);
}

/**
 *
 */
bool Level::playerIsMovable(
    const PlayerDirection& direction,
    const uint16_t& currentIndex
)
{
    /* The conditions are not refactored, I'm gonna
     * to change this part anyway when I will integrate
     * the multi-floor feature... */

    /* check if the player can go on the left */
    if (
        direction == LEFT &&
        currentIndex < memoris::dimensions::CELLS_PER_COLUMN
    )
    {
        return false;
    }

    /* check if the player can go on the right */
    if (
        direction == RIGHT &&
        currentIndex >=
        memoris::dimensions::LEVEL_CELLS_PER_FLOOR -
        memoris::dimensions::CELLS_PER_COLUMN &&
        currentIndex < memoris::dimensions::LEVEL_CELLS_PER_FLOOR
    )
    {
        return false;
    }

    /* check if the player can go up */
    if (
        direction == UP &&
        currentIndex % memoris::dimensions::CELLS_PER_COLUMN == 0
    )
    {
        return false;
    }

    /* check if the player can go down */
    if (
        direction == DOWN &&
        currentIndex % memoris::dimensions::CELLS_PER_COLUMN ==
        memoris::dimensions::CELLS_PER_COLUMN - 1
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
uint16_t Level::getStarCellsAmount()
{
    uint16_t starCellsAmount = 0;

    /* TODO: maybe is there a better solution than iterate the array... ? */
    for (
        std::vector<memoris::entities::Cell>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        if (
            cell->getStringRepresentation() ==
            constants::CellsFileRepresentations::STAR_CELL
        )
        {
            starCellsAmount++;
        }
    }

    return starCellsAmount;
}

/**
 *
 */
void Level::setPlayerCellPtr(memoris::entities::Cell* ptrPlayerCell)
{
    pPlayerCell = ptrPlayerCell;
}

/**
 *
 */
memoris::entities::Cell* Level::getPlayerCellPtr() const
{
    return pPlayerCell;
}

/**
 *
 */
memoris::entities::Cell* Level::getPreviousPlayerCellPtr() const
{
    return pPreviousPlayerCell;
}

/**
 *
 */
void Level::setPlayerCellAsEnabled()
{
    pPlayerCell->setHidden(false);
}
