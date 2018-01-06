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
 * @file RotateFloorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "RotateFloorAnimation.hpp"

#include "SoundsManager.hpp"
#include "Cell.hpp"
#include "Level.hpp"
#include "Context.hpp"
#include "dimensions.hpp"

namespace memoris
{
namespace animations
{

class RotateFloorAnimation::Impl
{

public:

    Impl(const MovementDirection& moveDirection)
    {
        /* TODO: #1250 check if the direction variable can be deleted and
           if only the enumeration can be used */
        if (moveDirection == MovementDirection::Left)
        {
            direction = -1;
        }
        else
        {
            direction = 1;
        }
    }

    short direction;
};

/**
 *
 */
RotateFloorAnimation::RotateFloorAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor,
    const MovementDirection& moveDirection
) : 
    LevelAnimation(
        context,
        level,
        floor
    ),
    impl(std::make_unique<Impl>(moveDirection))
{
}

/**
 *
 */
RotateFloorAnimation::~RotateFloorAnimation() = default;

/**
 *
 */
void RotateFloorAnimation::renderAnimation() &
{
    const auto& context = getContext();
    const auto& level = getLevel();
    const auto& floor = getFloor();

    level->display(floor);

    constexpr sf::Uint32 ANIMATION_INTERVAL {50};
    if (
        context.getClockMillisecondsTime() - 
        getAnimationLastUpdateTime() < ANIMATION_INTERVAL
    )
    {
        return;
    }

    playNextAnimationStep();

    if (getAnimationSteps() == 18)
    {
        level->deleteTransform();

        endsAnimation();

        rotateCells();
    }

    incrementAnimationStep();
}

/**
 *
 */
void RotateFloorAnimation::playNextAnimationStep() const &
{
    const auto& level = getLevel();

    if (getAnimationSteps() == 0)
    {
        getContext().getSoundsManager().playFloorMovementAnimationSound();

        level->createTransform();
    }

    constexpr unsigned short ROTATION_STEP {5};
    level->rotateAllCells(ROTATION_STEP * impl->direction);
}

/**
 *
 */
void RotateFloorAnimation::rotateCells() const &
{
    constexpr unsigned short CELLS_PER_SIDE = dimensions::CELLS_PER_FLOOR / 2;
    constexpr unsigned short HALF_CELLS_PER_LINE =
        dimensions::CELLS_PER_LINE / 2;
    const auto& cells = getLevel()->getCells();

    std::vector<std::unique_ptr<entities::Cell>> rightQuarterCells;

    for (
        unsigned short index = 0;
        index < CELLS_PER_SIDE;
        index += 1
    )
    {
        if (index % dimensions::CELLS_PER_LINE < HALF_CELLS_PER_LINE)
        {
            continue;
        }

        /* there is no need to have a specific cell position;
           this container is only used to store the cell type and visibility */
        std::unique_ptr<entities::Cell> cell =
            std::make_unique<entities::Cell>(
                getContext(),
                0,
                0,
                cells[index]->getType()
            );

        cell->setIsVisible(cells[index]->isVisible());

        rightQuarterCells.push_back(std::move(cell));
    }

    std::vector<std::unique_ptr<entities::Cell>> leftBottomQuarterCells;

    for (
        unsigned short index = 128;
        index < dimensions::CELLS_PER_FLOOR;
        index += 1
    )
    {
        if (index % dimensions::CELLS_PER_LINE >= HALF_CELLS_PER_LINE)
        {
            continue;
        }

        /* there is no need to have a specific cell position;
           this container is only used to store the cell type and visibility */
        std::unique_ptr<entities::Cell> cell =
            std::make_unique<entities::Cell>(
                getContext(),
                0,
                0,
                cells[index]->getType()
            );

        cell->setIsVisible(cells[index]->isVisible());

        leftBottomQuarterCells.push_back(std::move(cell));
    }

    for (
        unsigned short index = 0;
        index < CELLS_PER_SIDE;
        index += 1
    )
    {
        if (index % dimensions::CELLS_PER_LINE >= HALF_CELLS_PER_LINE)
        {
            continue;
        }

        rotateCell(index);
    }

    for (
        unsigned short index = CELLS_PER_SIDE;
        index < dimensions::CELLS_PER_FLOOR;
        index += 1
    )
    {
        if (index % dimensions::CELLS_PER_LINE < HALF_CELLS_PER_LINE)
        {
            continue;
        }

        rotateCell(index);
    }

    constexpr unsigned short CELLS_PER_QUARTER = CELLS_PER_SIDE / 2;

    for (
        unsigned short index = 0;
        index < CELLS_PER_QUARTER;
        index += 1
    )
    {
        rotateCellFromQuarter(
            index,
            (
                dimensions::CELLS_PER_LINE * (
                    index / HALF_CELLS_PER_LINE
                ) + HALF_CELLS_PER_LINE + (
                    index % HALF_CELLS_PER_LINE
                )
            ),
            rightQuarterCells
        );
    }

    unsigned short convertedIndex = CELLS_PER_SIDE;

    for (
        unsigned short index = 0;
        index < CELLS_PER_QUARTER;
        index += 1
    )
    {
        if (
            index % HALF_CELLS_PER_LINE == 0 and
            index != 0
        )
        {
            convertedIndex += HALF_CELLS_PER_LINE;
        }

        rotateCellFromQuarter(
            index,
            convertedIndex,
            leftBottomQuarterCells
        );

        convertedIndex += 1;
    }

    const auto& level = getLevel();
    const unsigned short currentPlayerIndex = level->getPlayerCellIndex();
    const std::pair<short, short> coordinates =
        getCoordinatesFromIndex(currentPlayerIndex);

    short x = coordinates.second;
    short y = coordinates.first;

    if (impl->direction == -1)
    {
        y *= -1;
    }
    else
    {
        x *= -1;
    }

    const auto destinationPlayerIndex = getIndexFromCoordinates(x, y);
    level->setPlayerCellIndex(destinationPlayerIndex);
}

/**
 *
 */
void RotateFloorAnimation::rotateCell(const unsigned short& index) const &
{
    const auto& cells = getLevel()->getCells();
    const auto& cell = cells[index];
    const auto type = cell->getType();
    const std::pair<short, short> coordinates =
        getCoordinatesFromIndex(index);

    /* rotate (x,y) around the origin (0, 0) results into (-y, x) */
    short x = coordinates.second;
    short y = coordinates.first;

    if (impl->direction == -1)
    {
        y *= -1;
    }
    else
    {
        x *= -1;
    }

    const auto destinationIndex = getIndexFromCoordinates(x, y);
    const auto& destinationCell = cells[destinationIndex];
    destinationCell->setType(type);

    const auto& context = getContext();
    if (cell->isVisible())
    {
        destinationCell->show(context);
    }
    else
    {
        destinationCell->hide(context);
    }
}

/**
 *
 */
void RotateFloorAnimation::rotateCellFromQuarter(
    const unsigned short& index,
    const unsigned short& convertedIndex,
    const std::vector<std::unique_ptr<entities::Cell>>& cellsCopy
) const &
{
    const auto& cell = cellsCopy[index];
    const auto type = cell->getType();
    const std::pair<short, short> coordinates =
        getCoordinatesFromIndex(convertedIndex);

    /* rotate (x,y) around the origin (0, 0) results into (-y, x) */
    short x = coordinates.second;
    short y = coordinates.first;

    if (impl->direction == -1)
    {
        y *= -1;
    }
    else
    {
        x *= -1;
    }

    const auto& cells = getLevel()->getCells();
    const auto destinationIndex = getIndexFromCoordinates(x, y);
    const auto& destinationCell = cells[destinationIndex];

    destinationCell->setType(type);

    const auto& context = getContext();
    if (cell->isVisible())
    {
        destinationCell->show(context);
    }
    else
    {
        destinationCell->hide(context);
    }
}

/**
 *
 */
std::pair<short, short>
RotateFloorAnimation::getCoordinatesFromIndex(const unsigned short& index)
const & noexcept
{
    /* every line contains 16 cells, so the middle is at index 8 */
    short x = (index % dimensions::CELLS_PER_LINE) - 8;
    short y = (index / dimensions::CELLS_PER_LINE) - 8;

    /* we increment the coordinates in order
       to have orthogonal coordinates rotable around the origin */

    if (x >= 0)
    {
        x += 1;
    }

    if (y >= 0)
    {
        y += 1;
    }

    return std::pair<short, short>(x, y);
}

/**
 *
 */
unsigned short RotateFloorAnimation::getIndexFromCoordinates(
    short x,
    short y
) const & noexcept
{
    if (x > 0)
    {
        x -= 1;
    }

    if (y > 0)
    {
        y -= 1;
    }

    x += 8;
    y += 8;

    return y * dimensions::CELLS_PER_LINE + x;
}

}
}
