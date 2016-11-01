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
 * @file LevelAnimation.cpp
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelAnimation.hpp"

#include "Context.hpp"
#include "Cell.hpp"
#include "Level.hpp"

namespace memoris
{
namespace animations
{

/**
 *
 */
const bool& LevelAnimation::isFinished() const & noexcept
{
    return finished;
}

/**
 *
 */
void LevelAnimation::showOrHideCell(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
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
    animationSteps++;

    lastAnimationUpdateTime = context.getClockMillisecondsTime();
}

/**
 *
 */
void LevelAnimation::movePlayer(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level
) const &
{
    level->setPlayerCellIndex(updatedPlayerIndex);
    level->getCells()[updatedPlayerIndex]->show(context);
}

}
}
