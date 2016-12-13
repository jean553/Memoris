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
 * @file GoalTutorialFrame.hpp
 * @brief tutorial frame that displays the main explanation about the Memoris
 * level main goal
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GOALTUTORIALFRAME_H_
#define MEMORIS_GOALTUTORIALFRAME_H_

#include "TutorialFrame.hpp"

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class GoalTutorialFrame : public TutorialFrame
{

public:

    /**
     * @brief constructor, initializes the item of the frame
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    GoalTutorialFrame(const utils::Context& context);
};

}
}

#endif
