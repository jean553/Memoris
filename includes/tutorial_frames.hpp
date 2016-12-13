/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file tutorial_frames.hpp
 * @brief insert frames into tutorial widget
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TUTORIAL_FRAMES_H_
#define MEMORIS_TUTORIAL_FRAMES_H_

#include "aliases.hpp"

namespace memoris
{
namespace utils
{

class Context;

/**
 * @brief insert a set of defined frames unique pointers into the given queue
 *
 * @param context current context reference
 * @param frames container of frames unique pointers
 * @param levelId the id of the current level, used to select the set of
 * frames to insert into the container
 */
void attachFramesToTutorial(
    const utils::Context& context,
    aliases::UniquePtrTutorialFramesContainerRef frames,
    const unsigned short& levelId
);

}
}

#endif
