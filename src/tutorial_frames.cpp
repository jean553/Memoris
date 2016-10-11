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
 * @file tutorial_frames.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "tutorial_frames.hpp"

#include "WelcomeTutorialFrame.hpp"
#include "GoalTutorialFrame.hpp"
#include "DepartureArrivalTutorialFrame.hpp"
#include "WatchingTimeTutorialFrame.hpp"

#include <memory>

namespace memoris
{
namespace utils
{


/**
 *
 */
void attachFramesToTutorial(
    utils::Context& context,
    aliases::UniquePtrTutorialFramesContainerRef frames,
    const unsigned short& levelId
)
{
    switch(levelId)
    {
    default:
    {
        frames.push(std::make_unique<widgets::WelcomeTutorialFrame>(context));
        frames.push(std::make_unique<widgets::GoalTutorialFrame>(context));
        frames.push(
            std::make_unique<widgets::DepartureArrivalTutorialFrame>(context)
        );
        frames.push(
            std::make_unique<widgets::WatchingTimeTutorialFrame>(context)
        );
    }
    }
}

}
}
