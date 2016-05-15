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
void Level::initializeSomeCommonCells()
{
    departureCellIndex = 0;
    pPlayerCell = NULL;
    pSelectedCell = NULL;
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
        if (
            std::distance(cells.begin(), cell) >=
            floor * constants::Dimensions::LEVEL_CELLS_PER_FLOOR &&
            std::distance(cells.begin(), cell) <
            floor * constants::Dimensions::LEVEL_CELLS_PER_FLOOR +
            constants::Dimensions::LEVEL_CELLS_PER_FLOOR
        )
        {
            (*cell)->display(pContext);
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
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        if (
            std::distance(cells.begin(), cell) >=
            floor * constants::Dimensions::LEVEL_CELLS_PER_FLOOR &&
            std::distance(cells.begin(), cell) <
            floor * constants::Dimensions::LEVEL_CELLS_PER_FLOOR +
            constants::Dimensions::LEVEL_CELLS_PER_FLOOR
        )
        {
            if((*cell)->isMouseHover())
            {
                pSelectedCell = (*cell);
                return true;
            }
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
    short cellNumber = 0;
    uint16_t cellAddress = 0, currentLine = 0, currentColumn = 0;

    for (uint16_t i = 0; i < constants::Dimensions::CELLS_PER_LEVEL; i++)
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

        /* save the departure cell */
        if (pNewCell->IN_FILE_REPRESENTATION == "DP")
        {
            departureCellIndex = cellAddress;
        }

        cellAddress++;

        cells.push_back(pNewCell);

        currentLine++;
        if (currentLine >= constants::Dimensions::CELLS_PER_COLUMN)
        {
            currentLine = 0;

            currentColumn++;
            if (currentColumn >= constants::Dimensions::CELLS_PER_LINE)
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
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        (*cell)->setHidden(hidden);
    }
}

/**
 *
 */
void Level::setCellsCursorSensitivity(const bool& sensitivity)
{
    for (
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        (*cell)->setCursorSensitivity(sensitivity);
    }
}

/**
 *
 */
void Level::setPosition(
    const float_t& hPosition,
    const float_t& vPosition
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
    }

    /* the player cell is now at the new array position */
    pPlayerCell = cells[index];

    /* the player cell is selected and not hidden */
    pPlayerCell->setSelected(true);
    pPlayerCell->setHidden(false);

    /* execute the cell action */
    //pPlayerCell->performAction(pGameContext);
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
                   constants::Dimensions::CELLS_PER_COLUMN;
    }
    else
    {
        newIndex = currentIndex +
                   constants::Dimensions::CELLS_PER_COLUMN;
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
        currentIndex < constants::Dimensions::CELLS_PER_COLUMN
    )
    {
        return false;
    }

    /* check if the player can go on the right */
    if (
        direction == RIGHT &&
        currentIndex >=
        constants::Dimensions::LEVEL_CELLS_PER_FLOOR -
        constants::Dimensions::CELLS_PER_COLUMN &&
        currentIndex < constants::Dimensions::LEVEL_CELLS_PER_FLOOR
    )
    {
        return false;
    }

    /* check if the player can go up */
    if (
        direction == UP &&
        currentIndex % constants::Dimensions::CELLS_PER_COLUMN == 0
    )
    {
        return false;
    }

    /* check if the player can go down */
    if (
        direction == DOWN &&
        currentIndex % constants::Dimensions::CELLS_PER_COLUMN ==
        constants::Dimensions::CELLS_PER_COLUMN - 1
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
        std::vector<Cell*>::iterator cell = cells.begin();
        cell != cells.end();
        ++cell
    )
    {
        if ((*cell)->IN_FILE_REPRESENTATION == "SC")
        {
            starCellsAmount++;
        }
    }

    return starCellsAmount;
}

/**
 *
 */
void Level::setPlayerCellPtr(entities::Cell* ptrPlayerCell)
{
    pPlayerCell = ptrPlayerCell;
}

/**
 *
 */
entities::Cell* Level::getPlayerCellPtr() const
{
    return pPlayerCell;
}
