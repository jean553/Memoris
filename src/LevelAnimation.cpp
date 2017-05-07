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
 * @file LevelAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelAnimation.hpp"

#include "Context.hpp"
#include "Cell.hpp"
#include "Level.hpp"

#include <SFML/Config.hpp>

namespace memoris
{
namespace animations
{

class LevelAnimation::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level
    ) :
        context(context),
        level(level)
    {
    }

    sf::Uint32 lastAnimationUpdateTime {0};

    unsigned short animationSteps {0};

    bool finished {false};

    short updatedPlayerIndex {-1};

    const utils::Context& context;

    /* TODO: #1186 the level in game controller, controllers factory
       and level animation should not be a pointer but only a reference */
    const std::shared_ptr<entities::Level> level;
};

/**
 *
 */
LevelAnimation::LevelAnimation(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level
) : 
    impl(
        std::make_unique<Impl>(
            context,
            level
        )
    )
{
}

/**
 *
 */
LevelAnimation::~LevelAnimation() = default;

/**
 *
 */
const bool& LevelAnimation::isFinished() const & noexcept
{
    return impl->finished;
}

/**
 *
 */
const utils::Context& LevelAnimation::getContext() const & noexcept
{
    return impl->context;
}

/**
 *
 */
void LevelAnimation::showOrHideCell(
    const unsigned short& index,
    const bool& visible
) const &
{
    const auto& context = impl->context;
    const auto& level = impl->level;

    if (visible)
    {
        level->getCells()[index]->show(context);
    }
    else
    {
        level->getCells()[index]->hide(context);
    }
}

/**
 *
 */
void LevelAnimation::incrementAnimationStep() &
{
    impl->animationSteps++;

    impl->lastAnimationUpdateTime = impl->context.getClockMillisecondsTime();
}

/**
 *
 */
void LevelAnimation::movePlayer() const &
{
    const auto& level = impl->level;

    level->setPlayerCellIndex(impl->updatedPlayerIndex);
    level->getCells()[impl->updatedPlayerIndex]->show(impl->context);
}

/**
 *
 */
const sf::Uint32& LevelAnimation::getAnimationLastUpdateTime() const & noexcept
{
    return impl->lastAnimationUpdateTime;
}

/**
 *
 */
void LevelAnimation::setAnimationLastUpdateTime(const sf::Uint32& time) const
    & noexcept
{
    impl->lastAnimationUpdateTime = time;
}

/**
 *
 */
const unsigned short& LevelAnimation::getAnimationSteps() const & noexcept
{
    return impl->animationSteps;
}

/**
 *
 */
void LevelAnimation::endsAnimation() const & noexcept
{
    impl->finished = true;
}

/**
 *
 */
const short& LevelAnimation::getUpdatedPlayerIndex() const & noexcept
{
    return impl->updatedPlayerIndex;
}

/**
 *
 */
void LevelAnimation::setUpdatedPlayerIndex(const short& index) const & noexcept
{
    impl->updatedPlayerIndex = index;
}

}
}
