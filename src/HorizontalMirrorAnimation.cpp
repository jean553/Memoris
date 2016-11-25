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
 Â* along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
#include "Context.hpp"
#include "Cell.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
void HorizontalMirrorAnimation::renderAnimation(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) &
{
    if (
        context.getClockMillisecondsTime() -
        lastAnimationUpdateTime < ANIMATION_STEPS_INTERVAL
    )
    {
        displayLevelAndHorizontalSeparator(
            context,
            level,
            floor
        );

        return;
    }

    /* we do not use a switch/case here because we create conditions on
       ranges of steps, which is not handled by switch/case instructions */

    /* during the 10 first steps, the animation does nothing except
       displaying the level with the red separator */

    if (animationSteps == 0)
    {
        context.getSoundsManager().playMirrorAnimationSound();
    }
    else if (animationSteps >= 10 && animationSteps < 15)
    {
        decreaseTransparency();

        updateBottomSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 15)
    {
        setNoTransparent();
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        decreaseTransparency();

        updateTopSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 21)
    {
        invertSides(
            context,
            level,
            floor
        );

        setFullTransparent();
    }
    else if (animationSteps >= 22 && animationSteps < 27)
    {
        increaseTransparency();

        updateTopSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 27)
    {
        setFullTransparent();
    }
    else if (animationSteps >= 28 && animationSteps < 33)
    {
        increaseTransparency();

        updateBottomSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 33)
    {
        movePlayer(
            context,
            level
        );

        finished = true;
    }

    displayLevelAndHorizontalSeparator(
        context,
        level,
        floor
    );

    incrementAnimationStep(context);
}

/**
 *
 */
void HorizontalMirrorAnimation::invertSides(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) &
{
    const unsigned short firstIndex = floor * CELLS_PER_FLOOR;
    const unsigned short lastIndex = firstIndex + TOP_SIDE_LAST_CELL_INDEX;
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
            context,
            level,
            index,
            level->getCells()[invertedIndex]->isVisible()
        );

        level->getCells()[invertedIndex]->setType(type);

        showOrHideCell(
            context,
            level,
            invertedIndex,
            visible
        );

        if (previousPlayerCell == index)
        {
            updatedPlayerIndex =
                findInvertedIndex(
                    line,
                    index
                );
        } else if (
            previousPlayerCell ==
                findInvertedIndex(
                    line,
                    index
                )
        )
        {
            updatedPlayerIndex = index;
        }

        if (index != 0 && index % CELLS_PER_LINE == 0)
        {
            line++;
        }
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateTopSideTransparency(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) const &
{
    const unsigned short floorFirstCellIndex = floor * CELLS_PER_FLOOR;
    const unsigned short floorLastCellIndex =
        floorFirstCellIndex + TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = floorFirstCellIndex;
        index < floorLastCellIndex;
        index++
    )
    {
        applyTransparencyOnOneCell(
            context,
            level,
            index
        );
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateBottomSideTransparency(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) const &
{
    const unsigned short floorSideFirstCellIndex =
        floor * CELLS_PER_FLOOR + TOP_SIDE_LAST_CELL_INDEX;
    const unsigned short floorSideLastCellIndex =
        (floor + 1) * CELLS_PER_FLOOR;

    for (
        unsigned short index = floorSideFirstCellIndex;
        index < floorSideLastCellIndex;
        index++
    )
    {
        applyTransparencyOnOneCell(
            context,
            level,
            index
        );
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::displayLevelAndHorizontalSeparator(
    const utils::Context& context,
    const Level& level,
    const unsigned short& floor
) const &
{
    level->display(
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
    /* this calculation can work with negative value, but at the end,
       the result should always be more than 0 to prevent seg fault */
    return INVERTED_CELL_INDEX_OFFSET - LINE_CELLS_FACTOR * line + index;
}

}
}
