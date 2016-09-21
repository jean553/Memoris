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
 * @file TutorialFrame.hpp
 * @brief one frame (page) displayed into the controller
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TUTORIALFRAME_H_
#define MEMORIS_TUTORIALFRAME_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class TutorialFrame
{

public:

    /**
     * @brief default destructor, empty, only declared in order to use 
     * forwarding declaration
     *
     * @throw std::bad_alloc thrown by std::make_unique if an allocation
     * error occurs
     */
    ~TutorialFrame() noexcept;

    /**
     * @brief pure virtual method used to make this base class abstract; this
     * method is used to let each frame specifies the surfaces to render
     *
     * @param context reference to the current context to use
     *
     * the 'context' parameter is not a constant reference because the
     * context contains the SFML window which will be modified
     *
     * not 'noexcept' because the implementation will always call SFML methods
     * that are no noexcept
     */
    virtual void render(utils::Context& context) const & = 0;

    /**
     * @brief getter of the vertical position
     *
     * @return const float&
     */
    const float& getVerticalPosition() const & noexcept;

    /**
     * @brief getter of the width
     *
     * @return const float&
     */
    const float& getWidth() const & noexcept;

    /**
     * @brief getter of the height
     *
     * @return const float&
     */
    const float& getHeight() const & noexcept;

protected:

    /**
     * @brief constructor, set the dimensions of the frame
     *
     * @param frameVerticalPosition the vertical position of the frame
     * @param frameWidth the width of the frame
     * @param frameHeight the height of the frame
     */
    TutorialFrame(
        const float& frameVerticalPosition,
        const float& frameWidth,
        const float& frameHeight
    ) noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
