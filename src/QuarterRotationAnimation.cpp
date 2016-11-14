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
 * @file QuarterRotationAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "QuarterRotationAnimation.hpp"

#include "Context.hpp"
#include "SoundsManager.hpp"
#include "Level.hpp"
#include "Cell.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace animations
{

constexpr unsigned short LevelAnimation::TOP_SIDE_LAST_CELL_INDEX;
constexpr unsigned short LevelAnimation::CELLS_PER_LINE;

class QuarterRotationAnimation::Impl
{

public:

    unsigned short translationSteps {0};
};

/**
 *
 */
QuarterRotationAnimation::QuarterRotationAnimation() noexcept :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
QuarterRotationAnimation::~QuarterRotationAnimation() noexcept = default;

/**
 *
 */
void QuarterRotationAnimation::renderAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    if (
        context.getClockMillisecondsTime() -
        lastAnimationUpdateTime < ANIMATION_STEPS_INTERVAL
    )
    {
        level->display(
            context,
            floor,
            &entities::Cell::display
        );

        return;
    }

    if (animationSteps == 0)
    {
        context.getSoundsManager().playFloorMovementAnimationSound();
    }

    moveAllQuarters(
        context,
        level,
        floor
    );

    impl->translationSteps++;

    if (impl->translationSteps == ANIMATION_STEPS)
    {
        updateCells(
            level,
            floor
        );

        finished = true;
    }

    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    incrementAnimationStep(context);
}

/**
 *
 */
void QuarterRotationAnimation::moveAllQuarters(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) const &
{
    using MovementDirection = entities::Cell::MovementDirection;

    const unsigned short firstIndex = CELLS_PER_FLOOR * floor;
    const unsigned short lastIndex = firstIndex + CELLS_PER_FLOOR;
    const unsigned short topSideLastIndex =
        firstIndex + TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        const unsigned short horizontalSide = index % CELLS_PER_LINE;
        MovementDirection direction {MovementDirection::LEFT};

        if (
            horizontalSide < HALF_CELLS_PER_LINE and
            index < topSideLastIndex
        )
        {
            direction = MovementDirection::DOWN;
        }
        else if (
            horizontalSide >= HALF_CELLS_PER_LINE and
            index >= topSideLastIndex
        )
        {
            direction = MovementDirection::UP;
        }
        else if (
            horizontalSide < HALF_CELLS_PER_LINE and
            index >= topSideLastIndex
        )
        {
            direction = MovementDirection::RIGHT;
        }

        level->getCells()[index]->moveInDirection(direction);
    }
}

/**
 *
 */
void QuarterRotationAnimation::updateCells(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) const & noexcept
{
    const unsigned short firstIndex = CELLS_PER_FLOOR * floor;
    const unsigned short lastIndex = firstIndex + CELLS_PER_FLOOR;
    const unsigned short topSideLastIndex =
        firstIndex + TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        const unsigned short horizontalSide = index % CELLS_PER_LINE;

        if (
            horizontalSide < HALF_CELLS_PER_LINE and
            index < topSideLastIndex
        )
        {
            invertCells(
                level,
                index,
                TOP_SIDE_LAST_CELL_INDEX
            );
        }
        else if (
            horizontalSide >= HALF_CELLS_PER_LINE and
            index >= topSideLastIndex
        )
        {
            invertCells(
                level,
                index,
                -TOP_SIDE_LAST_CELL_INDEX
            );
        }
        else if (
            horizontalSide < HALF_CELLS_PER_LINE and
            index >= topSideLastIndex
        )
        {
            invertCells(
                level,
                index,
                CELLS_PER_LINE
            );
        }
        else
        {
            invertCells(
                level,
                index,
                -CELLS_PER_LINE
            );
        }
    }
}

/**
 *
 */
void QuarterRotationAnimation::invertCells(
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& index,
    const unsigned short& modification
) const & noexcept
{
    const unsigned short newIndex = index + modification;

    level->getCells()[newIndex]->setType(
        level->getCells()[newIndex]->getType()
    );

    level->getCells()[newIndex]->setIsVisible(
        level->getCells()[newIndex]->isVisible()
    );
}

}
}
