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
#include "ShapesManager.hpp"
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
        displayLevelAndVerticalSeparator(
            context,
            level,
            floor
        );

        return;
    }

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
        setNoTransparent();
    }
    else if (animationSteps >= 16 && animationSteps < 21)
    {
        decreaseTransparency();

        updateRightSideTransparency(
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

        updateLeftSideTransparency(
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

        updateRightSideTransparency(
            context,
            level,
            floor
        );
    }
    else if (animationSteps == 33)
    {
        level->setPlayerCellIndex(updatedPlayerIndex);
        level->getCells()[updatedPlayerIndex]->show(context);

        finished = true;
    }

    displayLevelAndVerticalSeparator(
        context,
        level,
        floor
    );

    incrementAnimationStep(context);
}

/**
 *
 */
void VerticalMirrorAnimation::invertSides(
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
            updatedPlayerIndex = index;
        }

        if (index  == level->getPlayerCellIndex())
        {
            updatedPlayerIndex = index - difference;
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

    sideMax = 16;

    index = floor * 256 + 8;
    end = floor * 256 + 255;
    unsigned short it = 0;

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
    const unsigned short firstIndex = CELLS_PER_FLOOR * floor;
    const unsigned short lastIndex = firstIndex + CELLS_PER_FLOOR;

    for(
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        if (index % CELLS_PER_LINE < CELLS_PER_LINE_PER_SIDE)
        {
            applyTransparencyOnOneCell(
                context,
                level,
                index
            );
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
    const unsigned short firstIndex = CELLS_PER_FLOOR * floor;
    const unsigned short lastIndex = firstIndex + CELLS_PER_FLOOR;

    for(
        unsigned short index = firstIndex;
        index < lastIndex;
        index++
    )
    {
        if (index % CELLS_PER_LINE >= CELLS_PER_LINE_PER_SIDE)
        {
            applyTransparencyOnOneCell(
                context,
                level,
                index
            );
        }
    }
}

/**
 *
 */
void VerticalMirrorAnimation::displayLevelAndVerticalSeparator(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
) const &
{
    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    context.getSfmlWindow().draw(
        context.getShapesManager().getVerticalSeparator()
    );
}

}
}
