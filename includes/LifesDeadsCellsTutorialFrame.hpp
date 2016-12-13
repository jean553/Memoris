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
 * @file LifesDeadsCellsTutorialFrame.hpp
 * @brief shows the life and dead cells
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LIFESDEADSCELLSTUTORIALFRAME_H_
#define MEMORIS_LIFESDEADSCELLSTUTORIALFRAME_H_

#include "TutorialFrame.hpp"

namespace memoris
{
namespace widgets
{

class LifesDeadsCellsTutorialFrame : public TutorialFrame
{

public:

    /**
     * @brief constructor, initializes the items of the frame
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    LifesDeadsCellsTutorialFrame(const utils::Context& context);
};

}
}

#endif
