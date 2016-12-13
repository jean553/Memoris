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
 * @file WatchingTimeTutorialFrame.hpp
 * @brief tutorial frame with the explanation about the watching time
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WATCHINGTIMETUTORIALFRAME_H_
#define MEMORIS_WATCHINGTIMETUTORIALFRAME_H_

#include "TutorialFrame.hpp"

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class WatchingTimeTutorialFrame : public TutorialFrame
{

public:

    /**
     * @brief constructor, initializes the parent with dimensions
     *
     * @param context current context reference
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    WatchingTimeTutorialFrame(const utils::Context& context);
};

}
}

#endif
