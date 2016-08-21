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

namespace memoris
{
namespace animations
{

/**
 *
 */
HorizontalMirrorAnimation::HorizontalMirrorAnimation(
    const std::shared_ptr<utils::Context>& context
)
{
    /* initialize the separator surface positions, sizes and color */
    separator.setPosition(300.f, 495.f);
    separator.setFillColor(context->getColorsManager().getColorRed());
    separator.setSize(sf::Vector2f(1000.f, 4.f));
}

/**
 *
 */
void HorizontalMirrorAnimation::playNextAnimationStep(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    unsigned short startingHighCellsIndex = floor * 320;
    unsigned short startingLowCellsIndex = startingHighCellsIndex + 160;

    /* NOTE: we do not use a switch/case here because we create conditions on
       ranges of steps, which is not handled by switch/case instructions */

    /* NOTE: during the 10 first steps, the animation does nothing except
       displaying the level with the red separator */

    /* progressively hides the bottom side of the level between the step 10
       and 15 */
    if (animationSteps < 15 && animationSteps >= 10)
    {
        /* we start at the index 160 * level (bottom side) and we reduce the
           alpha value of all the cells by TRANSPARENCY_UPDATE_AMOUNT at each
           iteration */
        setLevelSideCellsTransparency(
            context,
            level,
            startingLowCellsIndex,
            -TRANSPARENCY_UPDATE_AMOUNT
        );
    }
    /* when the bottom side is totally hidden, replace all the bottom side
       cells by the top side cells */
    else if (animationSteps == 15)
    {
        executeMirrorMovement(
            context,
            level,
            floor
        );
    }
    /* between the steps 16 and 21, progressively show back the bottom side
       cells with their new value; a mirror effect is visible for the user at
       this moment */
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        /* we start at the index 160 * floor (bottom side) and we increase the
           alpha value of all the cells by TRANSPARENCY_UPDATE_AMOUNT at each
           iteration */
        setLevelSideCellsTransparency(
            context,
            level,
            startingLowCellsIndex,
            TRANSPARENCY_UPDATE_AMOUNT
        );
    }
    /* between the steps 21 and 26, progressively hide the top side of the
       floor */
    else if (animationSteps >= 21 && animationSteps < 26)
    {
        /* starts at the cell 0 + floor * 320 (top side) and decrease the
           transparency value by TRANSPARENCY_UPDATE_AMOUNT at each iteration
           */
        setLevelSideCellsTransparency(
            context,
            level,
            startingHighCellsIndex,
            -TRANSPARENCY_UPDATE_AMOUNT
        );
    }
    /* replace all the cells of the top by the cells of the bottom when the
       top side is hidden */
    else if (animationSteps == 26)
    {
        /* replace the top cells by the bottom cells */
        executeReverseMirrorMovement(
            context,
            level,
            floor
        );
    }
    /* between the step 26 and 32, progressively show the top cells with their
       new textures */
    else if (animationSteps >= 26 && animationSteps < 32)
    {
        /* starts at the cell 0 + floor * 320 (top side) and increase the
           transparency value by TRANSPARENCY_UPDATE_AMOUNT at each iteration
           */
        setLevelSideCellsTransparency(
            context,
            level,
            startingHighCellsIndex,
            TRANSPARENCY_UPDATE_AMOUNT
        );
    }
    /* during the last step of the animation, the new player cell is
       displayed */
    else if (animationSteps == 33)
    {
        /* set the new player cell index */
        level->setPlayerCellIndex(playerCellIndexAfterAnimation);

        /* force the new player cell to be shown, no matter if this cell was
           shown or hidden */
        level->cells[playerCellIndexAfterAnimation]->show(context);

        /* set finished to true, the animation is terminated, no new iteration
           will be triggered */
        finished = true;
    }

    /* displays the level and the animation separator */
    displayLevelAndSeparator(
        context,
        level,
        floor
    );

    /* increments the animation step and update the last animation update
       time */
    incrementAnimationStep(context);
}

/**
 *
 */
void HorizontalMirrorAnimation::executeReverseMirrorMovement(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* this part replace all the cells of the top side of the floor by the
       cells contained into the lowCells container; visibility is also copied
    */

    unsigned short cursor = floor * 320 + 140, offset = 0;

    for (
        unsigned short index = 0;
        index < 160;
        index++
    )
    {
        if (offset == 20)
        {
            offset = 0;
            cursor -= 20;
        }

        level->cells[cursor + offset]->setType(
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
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* this part browse the bottom side of the floor and save all the cells
       , their disposition and their visibility inside two containers; these
       containers are used to copy the cells in the top side */

    unsigned short
    startingHighCellIndex = floor * 320,
    cursor = startingHighCellIndex + 300,
    startingLowCellIndex = startingHighCellIndex + 160,
    endingLowCellIndex = 320 * (floor + 1),
    offset = 0,
    diff = 20;

    for (
        unsigned short index = startingLowCellIndex;
        index < endingLowCellIndex;
        index++
    )
    {
        if (offset == 20)
        {
            offset = 0;
            diff += 40;
        }

        savedCells.push(*(level->cells[index]));

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
        if (offset == 20)
        {
            offset = 0;
            cursor -= 20;
        }

        level->cells[cursor + offset]->setType(
            level->cells[index]->getType()
        );

        showOrHideCell(
            context,
            level,
            cursor + offset,
            level->cells[index]->isVisible()
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
void HorizontalMirrorAnimation::setLevelSideCellsTransparency(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& startingLowCellsIndex,
    const float difference,
    ...
)
{
    animatedSideTransparency += difference;

    for (
        unsigned short index = startingLowCellsIndex;
        index < startingLowCellsIndex + 160;
        index++
    )
    {
        level->cells[index]->setCellColorTransparency(
            context,
            animatedSideTransparency
        );
    }
}

}
}