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
 * @file DiagonalAnimation.hpp
 * @brief this animation inverts the top left corner cells with the
 * bottom right corner cells, and the bottom left corner cells with the top
 * right corner cells
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DIAGONALANIMATION_H_
#define MEMORIS_DIAGONALANIMATION_H_

#include "LevelAnimation.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
class Color;
}

namespace memoris
{
namespace animations
{

class DiagonalAnimation : public LevelAnimation
{
    using Level = std::unique_ptr<entities::Level>;

public:

    /**
     * @brief renders the animation, overrided from the parent class
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void renderAnimation(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) & override;

private:

    /**
     * @brief switch to the next step of the animation, overrided from the
     * parent class
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void playNextAnimationStep(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief display the given floor of the level and the two separators
     * (both horizontal and vertical separators)
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void displayLevelAndSeparator(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief applies the purple flashing on each side that will be inversed
     * by the animation
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     * @param color the SFML color object to apply on the cells
     */
    void applyPurpleColorOnCellsQuarters(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor,
        const sf::Color& color
    ) &;

    /**
     * @bried invert the cells of the top left corner with the cells of the
     * bottom right corner
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void invertTopLeftWithBottomRight(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief invert the cells of the top right corner with the cells of the
     * bottom left corner
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param floor the current floor to display in the animation
     */
    void invertBottomLeftWithTopRight(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief invert the cells of the top right corner with the cells of the
     * bottom left corner
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to animate
     * @param source the source cell index
     * @param destination the difference to apply on the source cell to get
     * the destination cell
     */
    void invertCells(
        const utils::Context& context,
        const Level& level,
        const unsigned short& source,
        const short& difference
    ) &;

    /* the vertical and horizontal separators */
    sf::RectangleShape verticalSeparator;
    sf::RectangleShape horizontalSeparator;
};

}
}

#endif
