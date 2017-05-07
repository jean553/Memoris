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
 * @file HorizontalMirrorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "HorizontalMirrorAnimation.hpp"

#include "SoundsManager.hpp"
#include "ShapesManager.hpp"
#include "Level.hpp"
#include "Cell.hpp"
#include "dimensions.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
HorizontalMirrorAnimation::HorizontalMirrorAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level
) :
    AbstractMirrorAnimation(
        context,
        level
    )
{
}

/**
 *
 */
void HorizontalMirrorAnimation::renderAnimation(const unsigned short& floor) &
{
    const auto& context = getContext();

    constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};
    if (
        context.getClockMillisecondsTime() -
        getAnimationLastUpdateTime() < ANIMATION_STEPS_INTERVAL
    )
    {
        displayLevelAndHorizontalSeparator(floor);

        return;
    }

    const auto animationSteps = getAnimationSteps();

    if (animationSteps == 0)
    {
        context.getSoundsManager().playMirrorAnimationSound();
    }
    else if (animationSteps >= 10 && animationSteps < 15)
    {
        decreaseTransparency();

        updateBottomSideTransparency(floor);
    }
    else if (animationSteps == 15)
    {
        setNoTransparent();
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        decreaseTransparency();

        updateTopSideTransparency(floor);
    }
    else if (animationSteps == 21)
    {
        invertSides(floor);

        setFullTransparent();
    }
    else if (animationSteps >= 22 && animationSteps < 27)
    {
        increaseTransparency();

        updateTopSideTransparency(floor);
    }
    else if (animationSteps == 27)
    {
        setFullTransparent();
    }
    else if (animationSteps >= 28 && animationSteps < 33)
    {
        increaseTransparency();

        updateBottomSideTransparency(floor);
    }
    else if (animationSteps == 33)
    {
        movePlayer();

        endsAnimation();
    }

    displayLevelAndHorizontalSeparator(floor);

    incrementAnimationStep();
}

/**
 *
 */
void HorizontalMirrorAnimation::invertSides(const unsigned short& floor)
    const &
{
    const auto& level = getLevel();

    const unsigned short firstIndex = floor * dimensions::CELLS_PER_FLOOR;
    const unsigned short lastIndex = firstIndex +
        dimensions::TOP_SIDE_LAST_CELL_INDEX;
    const unsigned short previousPlayerCell = level->getPlayerCellIndex();

    unsigned short line {0};

    for (
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
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

        if (index != 0 && index % dimensions::CELLS_PER_LINE == 0)
        {
            line++;
        }
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateTopSideTransparency(
    const unsigned short& floor
) const &
{
    const unsigned short floorFirstCellIndex =
        floor * dimensions::CELLS_PER_FLOOR;
    const unsigned short floorLastCellIndex =
        floorFirstCellIndex + dimensions::TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = floorFirstCellIndex;
        index < floorLastCellIndex;
        index++
    )
    {
        applyTransparencyOnOneCell(index);
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateBottomSideTransparency(
    const unsigned short& floor
) const &
{
    const unsigned short floorSideFirstCellIndex =
        floor * dimensions::CELLS_PER_FLOOR +
            dimensions::TOP_SIDE_LAST_CELL_INDEX;
    const unsigned short floorSideLastCellIndex =
        (floor + 1) * dimensions::CELLS_PER_FLOOR;

    for (
        unsigned short index = floorSideFirstCellIndex;
        index < floorSideLastCellIndex;
        index++
    )
    {
        applyTransparencyOnOneCell(index);
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::displayLevelAndHorizontalSeparator(
    const unsigned short& floor
) const &
{
    const auto& context = getContext();

    getLevel()->display(
        context,
        floor,
        &entities::Cell::display
    );

    context.getSfmlWindow().draw(
        context.getShapesManager().getHorizontalSeparator()
    );
}

/**
 *
 */
const unsigned short HorizontalMirrorAnimation::findInvertedIndex(
    const unsigned short& line,
    const unsigned short& index
) const & noexcept
{
    constexpr unsigned short INVERTED_CELL_INDEX_OFFSET {240};
    constexpr unsigned short LINE_CELLS_FACTOR {32};

    /* this calculation can work with negative value, but at the end,
       the result should always be more than 0 to prevent seg fault */
    return INVERTED_CELL_INDEX_OFFSET - LINE_CELLS_FACTOR * line + index;
}

}
}
