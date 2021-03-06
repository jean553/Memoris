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
#include "Context.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace animations
{

/**
 *
 */
HorizontalMirrorAnimation::HorizontalMirrorAnimation(
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
void HorizontalMirrorAnimation::renderAnimation() &
{
    const auto& context = getContext();

    constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};
    if (
        context.getClockMillisecondsTime() -
        getAnimationLastUpdateTime() < ANIMATION_STEPS_INTERVAL
    )
    {
        displayLevelAndHorizontalSeparator();

        return;
    }

    const auto animationSteps = getAnimationSteps();

    if (animationSteps == 0)
    {
        context.getSoundsManager().playMirrorAnimationSound();
    }
    else if (
        animationSteps >= 10 and
        animationSteps < 15
    )
    {
        decreaseTransparency();

        updateBottomSideTransparency();
    }
    else if (animationSteps == 15)
    {
        setNoTransparent();
    }
    else if (
        animationSteps >= 16 and
        animationSteps < 21
    )
    {
        decreaseTransparency();

        updateTopSideTransparency();
    }
    else if (animationSteps == 21)
    {
        invertSides();

        setFullTransparent();
    }
    else if (
        animationSteps >= 22 and
        animationSteps < 27
    )
    {
        increaseTransparency();

        updateTopSideTransparency();
    }
    else if (animationSteps == 27)
    {
        setFullTransparent();
    }
    else if (
        animationSteps >= 28 and
        animationSteps < 33
    )
    {
        increaseTransparency();

        updateBottomSideTransparency();
    }
    else if (animationSteps == 33)
    {
        movePlayer();

        endsAnimation();
    }

    displayLevelAndHorizontalSeparator();

    incrementAnimationStep();
}

/**
 *
 */
void HorizontalMirrorAnimation::invertSides() const &
{
    const auto& level = getLevel();

    const unsigned short previousPlayerCell = level->getPlayerCellIndex();

    unsigned short line {0};
    unsigned short floor {0};

    for (
        unsigned short index {0};
        index < dimensions::CELLS_PER_LEVEL;
        index += 1
    )
    {
        using namespace dimensions;

        if (
            index >= TOP_SIDE_LAST_CELL_INDEX + (CELLS_PER_FLOOR * floor) and
            index < CELLS_PER_FLOOR * (floor + 1)
        )
        {
            if ((index + 1) % CELLS_PER_FLOOR == 0)
            {
                floor += 1;
                line = 0;
            }

            continue;
        }

        const char type = level->getCells()[index]->getType();
        const bool visible = level->getCells()[index]->isVisible();
        const unsigned short invertedIndex =
            findInvertedIndex(
                floor,
                line,
                index
            );

        level->getCells()[index]->setType(
            level->getCells()[invertedIndex]->getType()
        );

        constexpr sf::Uint8 NOT_DISPLAYED_TRANSPARENCY {0};

        showOrHideCell(
            index,
            level->getCells()[invertedIndex]->isVisible(),
            NOT_DISPLAYED_TRANSPARENCY
        );

        level->getCells()[invertedIndex]->setType(type);

        showOrHideCell(
            invertedIndex,
            visible,
            NOT_DISPLAYED_TRANSPARENCY
        );

        if (previousPlayerCell == index)
        {
            setUpdatedPlayerIndex(
                findInvertedIndex(
                    floor,
                    line,
                    index
                )
            );
        } else if (
            previousPlayerCell ==
                findInvertedIndex(
                    floor,
                    line,
                    index
                )
        )
        {
            setUpdatedPlayerIndex(index);
        }

        if (
            index != 0 and
            (index + 1) % CELLS_PER_LINE == 0
        )
        {
            line += 1;
        }
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateTopSideTransparency() const &
{
    const unsigned short floorFirstCellIndex =
        getFloor() * dimensions::CELLS_PER_FLOOR;
    const unsigned short floorLastCellIndex =
        floorFirstCellIndex + dimensions::TOP_SIDE_LAST_CELL_INDEX;

    for (
        unsigned short index = floorFirstCellIndex;
        index < floorLastCellIndex;
        index += 1
    )
    {
        applyTransparencyOnOneCell(index);
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::updateBottomSideTransparency() const &
{
    const auto& floor = getFloor();

    const unsigned short floorSideFirstCellIndex =
        floor * dimensions::CELLS_PER_FLOOR +
            dimensions::TOP_SIDE_LAST_CELL_INDEX;
    const unsigned short floorSideLastCellIndex =
        (floor + 1) * dimensions::CELLS_PER_FLOOR;

    for (
        unsigned short index = floorSideFirstCellIndex;
        index < floorSideLastCellIndex;
        index += 1
    )
    {
        applyTransparencyOnOneCell(index);
    }
}

/**
 *
 */
void HorizontalMirrorAnimation::displayLevelAndHorizontalSeparator() const &
{
    const auto& context = getContext();

    getLevel()->display(getFloor());

    context.getSfmlWindow().draw(
        context.getShapesManager().getHorizontalSeparator()
    );
}

/**
 *
 */
const unsigned short HorizontalMirrorAnimation::findInvertedIndex(
    const unsigned short& floor,
    const unsigned short& line,
    const unsigned short& index
) const & noexcept
{
    using namespace dimensions;
    const unsigned short offset = 240 + (CELLS_PER_FLOOR * floor);
    constexpr unsigned short LINE_CELLS_FACTOR {32};

    /* this calculation can work with negative value, but at the end,
       the result should always be more than 0 to prevent seg fault */
    return offset - LINE_CELLS_FACTOR * line + (
        index - CELLS_PER_FLOOR * floor
    );
}

}
}
