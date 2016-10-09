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
 * @file TutorialWidget.hpp
 * @brief tutorial manager that displays the information into the tutorial
 * serie levels
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TUTORIALWIDGET_H_
#define MEMORIS_TUTORIALWIDGET_H_

#include <memory>

namespace sf
{
class Color;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class TutorialWidget
{

public:

    /**
     * @brief constructor, empty, only used to initialize the implementation
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because the method calls SFML functions that are not
     * noexcept
     */
    TutorialWidget(utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use the
     * forwarding declaration
     */
    ~TutorialWidget() noexcept;

    /**
     * @brief display the tutorial widget
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because the method calls SFML functions that are not
     * noexcept
     *
     * not 'const' because it calls the animateFlashingAnimation() method
     * which modifies the attributes
     */
    void display(utils::Context& context) &;

    /**
     * @brief displays the next frame, returns true if an item has been popped
     * or false if the container is already empty; the container is not
     * modified if the function returns false
     *
     * @return const bool
     *
     * the returned boolean is not a reference because there is no local
     * variable returned inside the function, but directly a rvalue in the
     * return; statement
     *
     * not 'const' because the method pop values from the frames queue, changes
     * the widget dimensions according to the popped frame dimension; set the
     * current frame unique pointer
     *
     * not 'noexcept' could be noexcept because we have the guarantee that
     * no one of the std::queue::front, std::queue::pop, std::queue::empty
     * will throw an exception (guarantee for non-empty containers, undefined
     * behavior for empty containers), but the method also call SFML methods
     * which are not marked as noexcept
     */
    const bool nextFrame() &;

private:

    enum class FlashingColors
    {
        BLUE, WHITE
    };

    static constexpr float HORIZONTAL_POSITION {10.f};
    static constexpr float BORDER_WIDTH {2.f};
    static constexpr float DIMENSION_UPDATE_STEP {10.f};

    /**
     * @brief render the flashing animation of the widget
     *
     * @param context reference to the current context to use
     *
     * not 'const' because it modifies some surfaces
     *
     * not 'noexcept' because it calls SFML methods that are not
     * noexcept
     */
    void animateFlashingAnimation(utils::Context& context) &;

    /**
     * @brief update the color of all the border surfaces
     *
     * @param color constant reference to the new color to apply
     *
     * not 'const' because it modifies some surfaces
     *
     * not 'noexcept' because it calls SFML methods that are not
     * noexcept
     */
    void setBorderColor(const sf::Color& color) &;

    /**
     * @brief set the widget dimensions with the dimensions of the current
     * tutorial frame
     *
     * @param width expected widget width
     * @param height expected widget height
     * @param position expected widget vertical position
     *
     * not 'const' because it updates the dimensions of the widget
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void updateWidgetDimensions(
        const float& width,
        const float& height,
        const float& position
    ) &;

    /**
     * @brief played when switching from one frame to another one; create a
     * smooth dimensions animation effect
     *
     * @param context reference to the current context to use
     *
     * not 'const' because it modifies the dimensions of the widget
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void animateDimensions(const utils::Context& context) &;

    /**
     * @brief set the current frame value with the next frame of the frames
     * queue
     *
     * not 'const' because it modifies the current frame value
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void loadFrame() &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
