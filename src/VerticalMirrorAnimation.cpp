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
 * @file VerticalMirrorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "VerticalMirrorAnimation.hpp"

#include "SoundsManager.hpp"
#include "ShapesManager.hpp"
#include "Level.hpp"
#include "Cell.hpp"
#include "dimensions.hpp"

namespace memoris
{
namespace animations
{

constexpr unsigned short CELLS_PER_LINE_PER_SIDE {8};
constexpr unsigned short LEFT_SIDE_LAST_CELL_INDEX {247};
constexpr unsigned short LINE_LAST_CELL_INDEX {15};

/**
 *
 */
VerticalMirrorAnimation::VerticalMirrorAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) :
    AbstractMirrorAnimation(
        context,
        level,
        floor
    )
{
}

/**
 *
 */
void VerticalMirrorAnimation::renderAnimation() &
{
    const auto& context = getContext();
    const auto& level = getLevel();

    constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};
    if (
        context.getClockMillisecondsTime() -
        getAnimationLastUpdateTime() < ANIMATION_STEPS_INTERVAL
    )
    {
        displayLevelAndVerticalSeparator();

        return;
    }

    const auto animationSteps = getAnimationSteps();

    if (animationSteps == 0)
    {
        context.getSoundsManager().playMirrorAnimationSound();
    }
    else if (animationSteps < 15 && animationSteps >= 10)
    {
        decreaseTransparency();

        updateLeftSideTransparency();
    }
    else if (animationSteps == 15)
    {
        setNoTransparent();
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        decreaseTransparency();

        updateRightSideTransparency();
    }
    else if (animationSteps == 21)
    {
        invertSides();

        setFullTransparent();
    }
    else if (animationSteps >= 22 && animationSteps < 27)
    {
        increaseTransparency();

        updateLeftSideTransparency();
    }
    else if (animationSteps == 27)
    {
        setFullTransparent();
    }
    else if (animationSteps >= 28 && animationSteps < 33)
    {
        increaseTransparency();

        updateRightSideTransparency();
    }
    else if (animationSteps == 33)
    {
        const auto updatedPlayerIndex = getUpdatedPlayerIndex();

        level->setPlayerCellIndex(updatedPlayerIndex);
        level->getCells()[updatedPlayerIndex]->show(context);

        endsAnimation();
    }

    displayLevelAndVerticalSeparator();

    incrementAnimationStep();
}

/**
 *
 */
void VerticalMirrorAnimation::invertSides() const &
{
    const auto& level = getLevel();

    const unsigned short firstIndex = getFloor() * dimensions::CELLS_PER_FLOOR;

    constexpr unsigned short LAST_FLOOR_CELL_INDEX {255};
    const unsigned short lastIndex = firstIndex + LAST_FLOOR_CELL_INDEX;

    const unsigned short previousPlayerCell = level->getPlayerCellIndex();

    unsigned short line {0};

    for (
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        if (index % dimensions::CELLS_PER_LINE >= CELLS_PER_LINE_PER_SIDE)
        {
            continue;
        }

        const char type = level->getCells()[index]->getType();
        const bool visible = level->getCells()[index]->isVisible();
        const unsigned short invertedIndex =
            findInvertedIndex(
                line,
                index
            );

        level->getCells()[index]->setType(
            level->getCells()[invertedIndex]->getType()
        );

        showOrHideCell(
            index,
            level->getCells()[invertedIndex]->isVisible()
        );

        level->getCells()[invertedIndex]->setType(type);

        showOrHideCell(
            invertedIndex,
            visible
        );

        if (previousPlayerCell == index)
        {
            setUpdatedPlayerIndex(
                findInvertedIndex(
                    line,
                    index
                )
            );
        } else if (
            previousPlayerCell ==
                findInvertedIndex(
                    line,
                    index
                )
        )
        {
            setUpdatedPlayerIndex(index);
        }

        constexpr unsigned short CELLS_PER_LINE_OFFSET {7};
        if (
            index and
            (index - CELLS_PER_LINE_OFFSET) % CELLS_PER_LINE_PER_SIDE == 0
        )
        {
            line++;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::updateLeftSideTransparency() const &
{
    const unsigned short firstIndex = dimensions::CELLS_PER_FLOOR * getFloor();
    const unsigned short lastIndex = firstIndex + dimensions::CELLS_PER_FLOOR;

    for(
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        if (index % dimensions::CELLS_PER_LINE < CELLS_PER_LINE_PER_SIDE)
        {
            applyTransparencyOnOneCell(index);
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::updateRightSideTransparency() const &
{
    const unsigned short firstIndex = dimensions::CELLS_PER_FLOOR * getFloor();
    const unsigned short lastIndex = firstIndex + dimensions::CELLS_PER_FLOOR;

    for(
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        if (index % dimensions::CELLS_PER_LINE >= CELLS_PER_LINE_PER_SIDE)
        {
            applyTransparencyOnOneCell(index);
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::displayLevelAndVerticalSeparator() const &
{
    const auto& context = getContext();

    getLevel()->display(
        context,
        getFloor(),
        &entities::Cell::display
    );

    context.getSfmlWindow().draw(
        context.getShapesManager().getVerticalSeparator()
    );
}

/**
 *
 */
const unsigned short VerticalMirrorAnimation::findInvertedIndex(
    const unsigned short& line,
    const unsigned short& index
) const & noexcept
{
    return dimensions::CELLS_PER_LINE * line +
        (LINE_LAST_CELL_INDEX - index % dimensions::CELLS_PER_LINE);
}

}
}
