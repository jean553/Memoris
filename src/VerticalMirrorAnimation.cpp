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
 * @file VerticalMirrorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "VerticalMirrorAnimation.hpp"

#include "SoundsManager.hpp"
#include "Level.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
void VerticalMirrorAnimation::renderAnimation(
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
void VerticalMirrorAnimation::playNextAnimationStep(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    if (animationSteps == 0)
    {
        context.getSoundsManager().playMirrorAnimationSound();
    }
    else if (animationSteps < 15 && animationSteps >= 10)
    {
        decreaseTransparency();

        updateLeftSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 15)
    {
        /* copy the right cells on the left side */
        executeMirrorMovement(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        increaseTransparency();

        updateLeftSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps >= 21 && animationSteps < 26)
    {
        sideMax = 16;

        decreaseTransparency();

        updateRightSideTransparency(
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

        updateRightSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 33)
    {
        /* set the new player cell index */
        level->setPlayerCellIndex(playerCellIndexAfterAnimation);

        /* force the new player cell to be shown, no matter if this cell was
           shown or hidden */
        level->getCells()[playerCellIndexAfterAnimation]->show(context);

        finished = true;
    }

    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    /* increments the animation step and update the last animation update
       time */
    incrementAnimationStep(context);
}

/**
 *
 */
void VerticalMirrorAnimation::executeMirrorMovement(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short index = floor * 256 + 8,
                   difference = 1,
                   end = floor * 256 + 255;

    while(index <= end)
    {
        /* the 'cells' array of the Level entity is a container of pointers;
           we really want to 'copy' the cells here, so we have to use '*' */
        savedCells.push(*(level->getCells()[index - difference]));

        if (index - difference == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index;
        }

        if (index  == level->getPlayerCellIndex())
        {
            playerCellIndexAfterAnimation = index - difference;
        }

        level->getCells()[index - difference]->setType(
            level->getCells()[index]->getType()
        );

        showOrHideCell(
            context,
            level,
            index - difference,
            level->getCells()[index]->isVisible()
        );

        index++;
        difference += 2;

        if (index % 16 == 0)
        {
            index += 8;
            difference = 1;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::executeReverseMirrorMovement(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) &
{
    unsigned short index = floor * 256 + 8,
                   it = 0,
                   end = floor * 256 + 255;

    while(index <= end)
    {
        level->getCells()[index]->setType(
            savedCells.front().getType()
        );

        showOrHideCell(
            context,
            level,
            index,
            savedCells.front().isVisible()
        );

        savedCells.pop();

        index++;
        it++;

        if (index % 16 == 0)
        {
            index += 8;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::updateLeftSideTransparency(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) const &
{
    unsigned short index = 256 * floor;

    while(index <= 256 * floor + 247)
    {
        applyTransparencyOnOneCell(
            context,
            level,
            index
        );

        index++;

        if(index % sideMax == 0 && index != 0)
        {
            index += 8;
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::updateRightSideTransparency(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) const &
{
    unsigned short index = 256 * floor + 8;

    while(index <= 256 * floor + 255)
    {
        applyTransparencyOnOneCell(
            context,
            level,
            index
        );

        index++;

        if(index % sideMax == 0 && index != 0)
        {
            index += 8;
        }
    }
}

}
}
