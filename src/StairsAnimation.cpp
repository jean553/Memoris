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
 * @file StairsAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "StairsAnimation.hpp"

#include "SoundsManager.hpp"
#include "Cell.hpp"
#include "Level.hpp"

namespace memoris
{
namespace animations
{

constexpr float TRANSPARENCY_UPDATE_AMOUNT {17.f};

class StairsAnimation::Impl
{

public:

    Impl(const FloorMoveDirection& moveDirection)
    {
        if (moveDirection == FloorMoveDirection::Up)
        {
            direction = 1;
        }
        else
        {
            direction = -1;
        }
    }

    short direction;

    short transformation {0};

    float cellsTransparency {255.f};
};

/**
 *
 */
StairsAnimation::StairsAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& floor,
    const FloorMoveDirection& direction
) :
    LevelAnimation(
        context,
        level,
        floor
    ),
    impl(std::make_unique<Impl>(direction))
{
    /* this animation is a simple waiting period; in order to wait the
       appropriated time, we just save the current time once before the
       waiting period; if the animation just started, the last animation
       update time is equal to 0 */
    setAnimationLastUpdateTime(context.getClockMillisecondsTime());
}

/**
 *
 */
StairsAnimation::~StairsAnimation() = default;

/**
 *
 */
void StairsAnimation::renderAnimation() &
{
    const auto& context = getContext();
    const auto& level = getLevel();
    const auto& floor = getFloor();

    level->display(floor + impl->transformation);

    auto& lastUpdateTime = getAnimationLastUpdateTime();

    const auto& currentTime = context.getClockMillisecondsTime();

    constexpr sf::Uint32 ANIMATION_INTERVAL {50};
    if (currentTime - lastUpdateTime < ANIMATION_INTERVAL)
    {
        return;
    }

    playNextAnimationStep();

    setAnimationLastUpdateTime(currentTime);
}

/**
 *
 */
void StairsAnimation::playNextAnimationStep() const &
{
    const auto& animationSteps = getAnimationSteps();
    const auto& context = getContext();
    const auto& level = getLevel();
    const auto& floor = getFloor();

    const auto& direction = impl->direction;

    auto& transformation = impl->transformation;
    auto& cellsTransparency = impl->cellsTransparency;

    if (animationSteps == 0)
    {
        context.getSoundsManager().playCollisionSound();
    }

    if (animationSteps == 10)
    {
        context.getSoundsManager().playFloorSwitchSound();
    }

    if (animationSteps >= 10 && animationSteps < 25)
    {
        cellsTransparency -= TRANSPARENCY_UPDATE_AMOUNT;

        level->setCellsTransparency(
            cellsTransparency,
            floor
        );
    }
    else if (animationSteps == 25)
    {
        level->setCellsTransparency(
            0.f,
            floor + direction
        );

        transformation = direction;
    }
    else if (animationSteps >= 26 && animationSteps < 41)
    {
        cellsTransparency += TRANSPARENCY_UPDATE_AMOUNT;

        level->setCellsTransparency(
            cellsTransparency,
            floor + direction
        );
    }
    else if (animationSteps == 41)
    {
        level->setCellsTransparency(
            255.f,
            floor
        );

        endsAnimation();
    }

    incrementAnimationStep();
}

}
}
