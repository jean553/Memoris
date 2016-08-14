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

#include "Context.hpp"
#include "PlayingSerieManager.hpp"
#include "cells.hpp"

#include <fstream>

namespace memoris
{
namespace entities
{

/**
 *
 */
Level::Level(const std::shared_ptr<utils::Context>& context)
{
    /* create a file object to read the level file and load the cells */
    std::ifstream file(series::PlayingSerieManager::get().getNextLevelName());

    /* check if the file is opened correctly */
    if (!file.is_open())
    {
        /* TODO: #561 - check PlayingSerieManager.cpp for details */
        throw std::invalid_argument("Cannot open the given level file");
    }

    /* positions cursor used to keep trace of the initialized cell position
       when initializing every cell one by one */
    unsigned short horizontalPositionCursor {0}, verticalPositionCursor {0};

    /* boolean used to remember if one cell is at least non empty on the
       current loaded floor; used to increment the amount of playable floors */
    bool emptyFloor = true;

    /* save the minutes and seconds of the current level into the dedicated
       attributes */

    /* FIXME: if the minutes/seconds are not specified or partially specified,
       the behavior is unmanaged */
    file >> minutes;
    file >> seconds;

    /* there are 3200 cells per level, 320 per floor, there are 10 floors */
    for(unsigned short index {0}; index < 3200; index++)
    {
        /* declare a new character at each loop iteration; initialize it with
           an empty cell; this character contains the type of the current
           iterated cell into the level file */
        char cellType = cells::EMPTY_CELL;

        /* check if the read of the file is finished; by doing this way, we are
           sure that a valid level can still be loaded in memory (with empty
           cells), even if the given file is damaged */
        if (!file.eof())
        {
            /* if the file is not finished, read the next character from it */
            cellType = file.get();
        }

        /* create an unique pointer to a cell object; the horizontal position
           of a cell is equal to 300 (horizontal position of the grid) + 50
           (cell width including separator) * the horizontal position cursor;
           the vertical position of a cell is equal to 98 (vertical position of
           the grid) + 50 (cell height including separator) * the vertical
           position cursor; the data type expected by the Cell constructor for
           the position is a float; this is faster to calculate positions with
           unsigned shorts, and cast them to float at the end when setting
           the data; this is not a problem to cast as we always manipulate
           integer values anyway */
        std::unique_ptr<Cell> cell(
            std::make_unique<Cell>(
                context,
                300.f + 50.f * static_cast<float>(horizontalPositionCursor),
                98.f + 50.f * static_cast<float>(verticalPositionCursor),
                cellType
            )
        );

        switch(cellType)
        {
        case cells::DEPARTURE_CELL:
        {
            /* store the current cell index into the player cell index if the
               current cell is a departure cell; this will be the starting cell
               of the player */
            playerIndex = index;

            break;
        }
        case cells::STAR_CELL:
        {
            /* increment the amount of stars on the level if the current cell
               is a star cell */
            starsAmount++;

            break;
        }
        }

        /* set the current floor as playable if the current cell is not
           empty and if no non-empty cell has already been found */
        if (cellType != cells::EMPTY_CELL && emptyFloor)
        {
            emptyFloor = false;
        }

        /* increment the horizontal position cursor */
        horizontalPositionCursor++;

        /* the cells are created line by line; when one line is finished
           (modulo 20, there are 20 cells per line), jump to the next line
           and reset the horizontal position cursor; we do not use !() but
           == 0 instead: we really want make this test explicit */
        if (horizontalPositionCursor % 20 == 0)
        {
            /* reset the horizontal position cursor */
            horizontalPositionCursor = 0;

            /* increment the vertical position cursor */
            verticalPositionCursor++;

            /* reset the vertical position cursor if the current vertical
               position is equal to the last one (16) */
            if (verticalPositionCursor % 16 == 0)
            {
                verticalPositionCursor = 0;

                /* check if the floor is playable or not */
                if (!emptyFloor)
                {
                    /* if the current floor is not empty, increment the amount
                       of playable floors */
                    playableFloors++;

                    /* reset the boolean to check properly the next floor */
                    emptyFloor = true;
                }
            }
        }

        /* move the unique pointer into the cells unique pointers container */
        cells.push_back(std::move(cell));
    }

    /* we do not manually close the std::ifstream object, this object is
       automatically destroyed when it goes out of the scope */
}

/**
 *
 */
void Level::display(
    const std::shared_ptr<utils::Context>& context,
    const unsigned short& floor
) const
{
    /* calculate the index of the first cell of the given floor */
    const unsigned short firstCellIndex = floor * 320;

    /* calculate the index of the last cell of the given floor */
    const unsigned short lastCellIndex = floor * 320 + 320;

    /* only display the cells of the given floor; all the other cells of the
       level are ignored */
    for(
        unsigned short index = firstCellIndex;
        index < lastCellIndex;
        index++
    )
    {
        /* get an unique pointer, get the cell object from this pointer */
        (*cells[index]).display(context);
    }
}

/**
 *
 */
void Level::hideAllCellsExceptDeparture(
    const std::shared_ptr<utils::Context>& context
)
{
    /* iterates all the cells of the array one by one */
    for(unsigned short index = 0; index < 3200; index++)
    {
        /* check if the type of the current cell is the departure cell type */
        if ((*cells[index]).getType() == cells::DEPARTURE_CELL)
        {
            /* force the cell to be shown; this is to ensure that whatever
               happened to the level before (animation, floor switch) that
               occured hide/show cells actions, we still show the departure
               cell anyway */
            (*cells[index]).show(context);

            /* do nothing and continue to iterate if the type is the departure
               cell; in fact, any departure cell stays visible */
            continue;
        }

        (*cells[index]).hide(context);
    }
}

/**
 *
 */
void Level::setPlayerCellTransparency(
    const std::shared_ptr<utils::Context>& context,
    const sf::Uint8& alpha
)
{
    /* update the cell color with the index equals to the player index */
    (*cells[playerIndex]).setCellColorTransparency(
        context,
        alpha
    );
}

/**
 *
 */
void Level::movePlayer(
    const std::shared_ptr<utils::Context>& context,
    const short& movement
)
{
    /* reset the current player cell transparency */
    setPlayerCellTransparency(
        context,
        255
    );

    /* apply the movement value to the current player index to change his
       position on the level */
    playerIndex += movement;

    /* show the player cell */
    (*cells[playerIndex]).show(context);
}

/**
 *
 */
bool Level::allowPlayerMovement(
    const short& movement,
    const unsigned short& floor
) const
{
    /* calculate the expected new player position */
    short expectedIndex = playerIndex + movement;

    /* we check if the player does not move up if already at the top; cannot
       move down if already at the bottom; cannot move left if already on the
       left; cannot move right if already on the right */
    if (
        expectedIndex < 320 * floor ||
        expectedIndex >= (320 * floor) + 320 ||
        (playerIndex % 20 == 19 && movement == 1) ||
        (playerIndex % 20 == 0 && movement == -1)
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
bool Level::detectWalls(
    const std::shared_ptr<utils::Context>& context,
    const short& movement
) const
{
    /* check if the expected cell is a wall cell */
    if((*cells[playerIndex + movement]).getType() == cells::WALL_CELL)
    {
        /* show the concerned wall cell */
        (*cells[playerIndex + movement]).show(context);

        return true;
    }

    return false;
}

/**
 *
 */
const char& Level::getPlayerCellType()
{
    return (*cells[playerIndex]).getType();
}

/**
 *
 */
void Level::emptyPlayerCell(const std::shared_ptr<utils::Context>& context)
{
    /* empty the player cell */
    (*cells[playerIndex]).empty();

    /* reload the cell texture reference */
    (*cells[playerIndex]).show(context);
}

/**
 *
 */
bool Level::movePlayerToNextFloor(
    const std::shared_ptr<utils::Context>& context
)
{
    /* calculate the expected new index of the player after his movement; use
       an unsigned variable as the user cannot have an index less than 0 at
       this moment and because this is the expected data type for the player
       index */
    unsigned short newIndex = playerIndex + 320;

    /* check if the expected index is less than 3200 (outside of the level) */
    if (newIndex > 3200)
    {
        /* if the next index is too hight, the player is not moved */
        return false;
    }

    /* if the player can be moved, the index is updated */
    playerIndex = newIndex;

    /* the texture of the new player cell is loaded */
    (*cells[playerIndex]).show(context);

    return true;
}

/**
 *
 */
bool Level::movePlayerToPreviousFloor(
    const std::shared_ptr<utils::Context>& context
)
{
    /* calculate the expected new index of the player after his movement; use
       a signed variable because at this moment, the player can be on the
       first level and the expected index can be less than 0 */
    short newIndex = playerIndex - 320;

    /* check if the expected new cell is less than 0 */
    if (newIndex < 0)
    {
        /* if the next index is too low, the player is not moved */
        return false;
    }

    /* no problem to cast the value; this variable is never less than 0 here
       and cannot be more than ~32000 (65536/2) anyway */
    playerIndex = static_cast<unsigned short>(newIndex);

    /* the texture of the new player cell is loaded */
    (*cells[playerIndex]).show(context);

    return true;
}

/**
 *
 */
const unsigned short& Level::getStarsAmount()
{
    return starsAmount;
}

/**
 *
 */
const unsigned short& Level::getPlayableFloors()
{
    return playableFloors;
}

/**
 *
 */
const unsigned short Level::getPlayerFloor()
{
    /* divide the current player index by 320 (cells per floor) and truncate
       the result as the result type is an unsigned short */
    return playerIndex / 320;
}

/**
 *
 */
void Level::playFloorTransitionAnimation(
    const std::shared_ptr<utils::Context>& context
)
{
    /* NOTE: this function only applies the horizontal transition animation
       for now */

    /* browse the 320 cells of the current floor */
    for(
        unsigned short i = 0;
        animationFloor * 320 + i < animationFloor * 320 + 320;
        i++
    )
    {
        /* check if the cell is on the left side of the limit column; in that
           case, the displayed cell must be the one at the same position on
           the next level */
        if (i % 20 < animationColumn)
        {
            /* displays the cell at the same position but on the next level;
               each level contains 320 cell, so the cell at the same position
               that this one on the next level is 320 cells after... */
            (*cells[animationFloor * 320 + i + 320]).display(context);

            /* directly increment the loop from here */
            continue;
        }

        /* check if the cell is on the limit column; in that case, the current
           cell is hidden to display the limitation column */
        if (i % 20 == animationColumn)
        {
            (*cells[animationFloor * 320 + i]).hide(context);
        }

        /* if the cell is on the limitation column or if the cell is on the
           right of the limitation column (current floor), the current cell
           is just displayed */
        (*cells[animationFloor * 320 + i]).display(context);
    }

    /* the switch floor animation is updated every 25 milliseconds until the
       end of the animation */
    if (
        context->getClockMillisecondsTime() -
        lastAnimationTime > 25
    )
    {
        /* increment the animation column; this column is used as a limitation
           column and this variable is its index; we increment the index to
           move the current limitation column on the floor */
        animationColumn++;

        /* the animation stops when the animation column is 20: means outside
           of the level */
        if (animationColumn == 20)
        {
            /* stops the floor transition animation */
            animateFloorTransition = false;

            /* reset the animation column for a future animation if it
               happens... */
            animationColumn = 0;

            /* increments the animation floor for a future animation */
            animationFloor++;
        }

        /* update the last animation update time to ensure the whole animation
           rendering */
        lastAnimationTime = context->getClockMillisecondsTime();
    }
}

/**
 *
 */
void Level::setAnimateFloorTransition(const bool& animate)
{
    animateFloorTransition = animate;
}

/**
 *
 */
const bool& Level::getAnimateFloorTransition()
{
    return animateFloorTransition;
}

/**
 *
 */
const unsigned short& Level::getMinutes() const
{
    return minutes;
}

/**
 *
 */
const unsigned short& Level::getSeconds() const
{
    return seconds;
}

}
}
