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

namespace sf
{
class Text;
class Drawable;
}

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
     */
    ~TutorialFrame() noexcept;

    /**
     * @brief render all the SFML drawable objects of the items container
     *
     * @param context reference to the current context to use
     *
     * the 'context' parameter is not a constant reference because the
     * context contains the SFML window which will be modified
     *
     * not 'noexcept' because the implementation will always call SFML methods
     * that are no noexcept
     */
    void render(utils::Context& context) const &;

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

    /**
     * @brief insert one item into the items container by move sementics
     *
     * @param item unique pointer to a SFML drawable object (text or sprite)
     *
     * item cannot be const because it is modified (moved) inside the method
     *
     * not 'const' because it modifies one attribute
     *
     * not 'noexcept' because it calls std::vector::push_back() which may
     * throw an exception
     *
     * protected because only called by frames constructors
     */
    void insertItem(std::unique_ptr<sf::Drawable> item) &;

    /**
     * @brief static method that applies the same properties to all the texts
     * surfaces passed by reference (common text size, font and color)
     *
     * @param context reference to the current context to use
     * @param text constant unique pointer reference to a SFML text
     *
     * this method is static because it never changes any attribute of the
     * current instance; it applies a set of properties to a SFML text, but
     * has no relationship with any specific frame; the method is declared
     * here because those properties are only applied to SFML texts objects
     * declared into Tutorial frames
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    static void applyPropertiesToText(
        utils::Context& context,
        const std::unique_ptr<sf::Text>& text
    );

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
