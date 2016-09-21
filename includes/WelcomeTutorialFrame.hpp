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
 * @file WelcomeTutorialFrame.hpp
 * @brief tutorial frame with the welcome message
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WELCOMETUTORIALFRAME_H_
#define MEMORIS_WELCOMETUTORIALFRAME_H_

#include "TutorialFrame.hpp"

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class WelcomeTutorialFrame : public TutorialFrame
{

public:

    /**
     * @brief destructor, initializes the parent with dimensions
     *
     * @param context current context reference
     */
    WelcomeTutorialFrame(utils::Context& context);

    /**
     * @brief default constructor, empty, only declared in order to use the
     * forwarding declaration
     */
    ~WelcomeTutorialFrame() noexcept;

    /**
     * @brief render the welcome tutorial frame
     *
     * @param context reference to the current context to use
     *
     * the 'context' parameter is not a constant reference because the
     * context contains the SFML window which will be modified
     *
     * not 'noexcept' because calls SFML surfaces
     */
    virtual void render(utils::Context& context) const & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
