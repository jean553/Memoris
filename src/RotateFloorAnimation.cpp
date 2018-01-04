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
    /* TODO: #1194 numbers literals should be constant expressions */

    std::vector<std::vector<entities::Cell>> horizontalLines;

    unsigned short playerColumn {0};
    unsigned short playerIndex {0};

    const auto& level = getLevel();
    const auto& context = getContext();
    const auto& floor = getFloor();

    unsigned short destination = floor * 256 + 255;

    if(impl->direction == -1)
    {
        destination = floor * 256 + 240;

        for (
            unsigned short lines = 0;
            lines < 16;
            lines++
        )
        {
            std::vector<entities::Cell> line;

            for (
                unsigned short index = 0;
                index < 16;
                index++
            )
            {
                entities::Cell cell(
                    context,
                    0.f,
                    0.f,
                    level->getCells()[lines * 16 + index]->getType()
                );

                cell.setIsVisible(
                    level->getCells()[lines * 16 + index]->isVisible()
                );

                line.push_back((*level->getCells()[lines * 16 + index]));

                if (lines * 16 + index == level->getPlayerCellIndex())
                {
                    playerColumn = lines;
                    playerIndex = index;
                }
            }

            horizontalLines.push_back(line);
        }

        for (unsigned short column = 0; column < 16; column++)
        {
            for (unsigned short index = 0; index < 16; index++)
            {
                level->getCells()[destination]->setType(
                    horizontalLines[column][index].getType()
                );

                if (horizontalLines[column][index].isVisible())
                {
                    level->getCells()[destination]->show(context);
                }
                else
                {
                    level->getCells()[destination]->hide(context);
                }

                if (column == playerColumn && index == playerIndex)
                {
                    level->setPlayerCellIndex(destination);
                }

                if (destination >= 16)
                {
                    destination -= 16;
                }
            }

            if (destination != 15)
            {
                destination += 241;
            }
        }
    }
    else
    {
        destination = floor * 256 + 255;

        for (
            unsigned short lines = 0;
            lines < 16;
            lines++
        )
        {
            unsigned short offset = 0;

            std::vector<entities::Cell> line;

            for (
                short index = 15;
                index >= 0;
                index--
            )
            {
                entities::Cell cell(
                    context,
                    0.f,
                    0.f,
                    level->getCells()[lines * 16 + index]->getType()
                );

                cell.setIsVisible(
                    level->getCells()[lines * 16 + index]->isVisible()
                );

                line.push_back((*level->getCells()[lines * 16 + index]));

                if (lines * 16 + index == level->getPlayerCellIndex())
                {
                    playerColumn = lines;
                    playerIndex = offset;
                }

                offset++;
            }

            horizontalLines.push_back(line);
        }

        for (short column = 0; column < 16; column++)
        {
            for (unsigned short index = 0; index < 16; index++)
            {
                level->getCells()[destination]->setType(
                    horizontalLines[column][index].getType()
                );

                if (horizontalLines[column][index].isVisible())
                {
                    level->getCells()[destination]->show(context);
                }
                else
                {
                    level->getCells()[destination]->hide(context);
                }

                if (column == playerColumn && index == playerIndex)
                {
                    level->setPlayerCellIndex(destination);
                }

                if (destination >= 16)
                {
                    destination -= 16;
                }
            }

            if (destination != 0)
            {
                destination += 239;
            }
        }
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
