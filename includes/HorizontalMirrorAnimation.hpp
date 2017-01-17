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
 * @file HorizontalMirrorAnimation.hpp
 * @brief plays the horizontal mirror animation
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTLEVELANIMATIONS_H_
#define MEMORIS_ABSTRACTLEVELANIMATIONS_H_

#include "AbstractMirrorAnimation.hpp"

namespace memoris
{
namespace animations
{

class HorizontalMirrorAnimation : public AbstractMirrorAnimation
{

public:

    /**
     * @brief renders the animation
     *
     * @param context constant reference to the current context to use
     * @param level constant reference on shared pointer to the concerned level
     * @param floor constant unsigned integer to the level floor to render
     */
    void renderAnimation(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) & override;

private:

    static constexpr unsigned short TOP_SIDE_FIRST_CELL_INDEX {0};
    static constexpr unsigned short INVERTED_CELL_INDEX_OFFSET {240};
    static constexpr unsigned short LINE_CELLS_FACTOR {32};

    /**
     * @brief invert the top side cells with the bottom side cells
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to shared pointer on the level to use
     * @param floor the current floor to display in the animation
     */
    void invertSides(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief changes the transparency of the top side of the level
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     * @param floor constant reference indicating which floor to animate
     *
     * not 'noexcept' because it calls SFML methods
     */
    void updateTopSideTransparency(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) const &;

    /**
     * @brief changes the transparency of the bottom side of the level
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     * @param floor constant reference indicating which floor to animate
     *
     * not 'noexcept' because it calls SFML methods
     */
    void updateBottomSideTransparency(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) const &;

    /**
     * @brief displays the level and the horizontal separator; method created
     * only for refactor purposes as it is called two times at two different
     * moments in the script
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     * @param floor constant reference indicating which floor to animate
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void displayLevelAndHorizontalSeparator(
        const utils::Context& context,
        const Level& level,
        const unsigned short& floor
    ) const &;

    /**
     * @brief calculates the interved index of the horizontal mirror for the
     * given index
     *
     * @param line constant reference to the current line of the cell (0...15)
     * @param index constant reference to the current index of the cell
     * (0...255) (considere the current floor factor)
     *
     * @return const unsigned short
     *
     * does not return a reference because it directly returns the result of
     * the calculation without storing it
     */
    const unsigned short findInvertedIndex(
        const unsigned short& line,
        const unsigned short& index
    ) const & noexcept;
};

}
}

#endif
