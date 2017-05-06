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

    sf::Uint32 lastAnimationUpdateTime {0};

    unsigned short animationSteps {0};

    bool finished {false};

    short updatedPlayerIndex {-1};
};

/**
 *
 */
LevelAnimation::LevelAnimation() : impl(std::make_unique<Impl>())
{
}

/**
 *
 */
LevelAnimation::~LevelAnimation() noexcept = default;

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
void LevelAnimation::showOrHideCell(
    const utils::Context& context,
    const Level& level,
    const unsigned short& index,
    const bool& visible
) const &
{
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
void LevelAnimation::incrementAnimationStep(const utils::Context& context) &
{
    impl->animationSteps++;

    impl->lastAnimationUpdateTime = context.getClockMillisecondsTime();
}

/**
 *
 */
void LevelAnimation::movePlayer(
    const utils::Context& context,
    const Level& level
) const &
{
    level->setPlayerCellIndex(impl->updatedPlayerIndex);
    level->getCells()[impl->updatedPlayerIndex]->show(context);
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
