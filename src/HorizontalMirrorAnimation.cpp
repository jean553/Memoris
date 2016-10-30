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
#include "Level.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
void HorizontalMirrorAnimation::renderAnimation(
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

        /* TODO: #863 displays the vertical or horizontal separator; we do not
           display them for now because we have no way here to know if the
           child is a horizontal or vertical animation */

        return;
    }

    playNextAnimationStep(
        context,
        level,
        floor
    );
}


/**
 *
 */
void HorizontalMirrorAnimation::playNextAnimationStep(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
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
        executeMirrorMovement(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        increaseTransparency();

        updateBottomSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 21 && animationSteps < 26)
    {
        decreaseTransparency();

        updateTopSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 26)
    {
        executeReverseMirrorMovement(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 26 && animationSteps < 32)
    {
        increaseTransparency();

        updateTopSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 33)
    {
        level->setPlayerCellIndex(playerCellIndexAfterAnimation);

        level->getCells()[playerCellIndexAfterAnimation]->show(context);

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
void HorizontalMirrorAnimation::executeReverseMirrorMovement(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    /* this part replace all the cells of the top side of the floor by the
       cells contained into the lowCells container; visibility is also copied
    */

    unsigned short cursor = floor * 256 + 112, offset = 0;

    for (
        unsigned short index = 0;
        index < 128;
        index++
    )
    {
        if (offset == 16)
        {
            offset = 0;
            cursor -= 16;
        }

        level->getCells()[cursor + offset]->setType(
            savedCells.front().getType()
        );

        showOrHideCell(
            context,
            level,
            cursor + offset,
            savedCells.front().isVisible()
        );

        savedCells.pop();

        if (
            cursor + offset == playerCellIndexAfterAnimation &&
            playerCellIndexAfterAnimation != -1
        )
        {
            playerCellIndexAfterAnimation = cursor + offset;
        }

        offset++;
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::executeMirrorMovement(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    /* this part browse the bottom side of the floor and save all the cells
       , their disposition and their visibility inside two containers; these
       containers are used to copy the cells in the top side */

    unsigned short startingHighCellIndex = floor * 256,
                   cursor = startingHighCellIndex + 240,
                   startingLowCellIndex = startingHighCellIndex + 128,
                   endingLowCellIndex = 256 * (floor + 1),
                   offset = 0,
                   diff = 16;

    for (
        unsigned short index = startingLowCellIndex;
        index < endingLowCellIndex;
        index++
    )
    {
        if (offset == 16)
        {
            offset = 0;
            diff += 32;
        }

        savedCells.push(*(level->getCells()[index]));

        if (index == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index - diff;
        }

        offset++;
    }

    /* this part replaces the cells of the bottom part by the cells of the
       top part */

    offset = 0;

    for (
        unsigned short index = startingHighCellIndex;
        index < startingLowCellIndex;
        index++
    )
    {
        if (offset == 16)
        {
            offset = 0;
            cursor -= 16;
        }

        level->getCells()[cursor + offset]->setType(
            level->getCells()[index]->getType()
        );

        showOrHideCell(
            context,
            level,
            cursor + offset,
            level->getCells()[index]->isVisible()
        );

        if (index == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = cursor + offset;
        }

        offset++;
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateTopSideTransparency(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
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
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) const &
{
    const unsigned short floorSideFirstCellIndex =
        floor * CELLS_PER_FLOOR + TOP_SIDE_LAST_CELL_INDEX;
    const unsigned short floorSideLastCellIndex =
        floor * CELLS_PER_FLOOR + BOTTOM_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = floorSideFirstCellIndex;
        index <= floorSideLastCellIndex;
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

}
}
