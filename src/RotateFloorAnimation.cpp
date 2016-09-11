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
 * @file RotateFloorAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "RotateFloorAnimation.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
RotateFloorAnimation::RotateFloorAnimation(
    aliases::ConstContextSharedPtrRef context,
    const short& movementDirection
) :
    direction(movementDirection)
{
    /* plays the floor movement animation */
    context->getSoundsManager().getFloorMovementAnimationSound().play();
}

/**
 *
 */
void RotateFloorAnimation::playNextAnimationStep(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* if the animation step is the first one, we create a sf::Transform object
       pointed by the level transform unique pointer */
    if (animationSteps == 0)
    {
        /* dynamically create the SFML transform object of the Level object */
        level->createTransform();
    }

    /* apply a rotation */
    level->rotateAllCells(5 * direction);
}

/**
 *
 */
void RotateFloorAnimation::renderAnimation(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    level->display(
        context,
        floor,
        &entities::Cell::display
    );

    if (context->getClockMillisecondsTime() - lastAnimationUpdateTime < 50)
    {
        return;
    }

    playNextAnimationStep(
        context,
        level,
        floor
    );

    if (animationSteps == 18)
    {
        /* dynamically delete the SFML transform of the level object, we
           do not need it anymore at the end of the animation */
        level->deleteTransform();

        finished = true;

        rotateCells(
            context,
            level,
            floor
        );
    }

    incrementAnimationStep(context);
}

/**
 *
 */
void RotateFloorAnimation::rotateCells(
    const std::shared_ptr<utils::Context>& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor
)
{
    /* every line of the floor is stored into a dedicated container; each
       container is stored into a parent container */
    std::vector<std::vector<entities::Cell>> horizontalLines;

    /* these local variables are used to transfer the cells from one location
       to another one during the rotation */
    unsigned short playerColumn = 0,
                   playerIndex = 0,
                   destination = floor * 256 + 240;

    /* we browse every line of the floor one by one and store them inside
       the container of containers */
    for (
        unsigned short lines = 0;
        lines < 16;
        lines++
    )
    {
        /* container for every cell of the line */
        std::vector<entities::Cell> line;

        /* browse each cell of the line one by one */
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

            /* save the location of the player cell if found */
            if (lines * 16 + index == level->getPlayerCellIndex())
            {
                playerColumn = lines;
                playerIndex = index;
            }
        }

        horizontalLines.push_back(line);
    }

    /* copies every lines at columns in order to make the rotation */

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

}
}
