/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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

#ifndef MEMORIS_HORIZONTALMIRRORANIMATION_H_
#define MEMORIS_HORIZONTALMIRRORANIMATION_H_

#include "AbstractMirrorAnimation.hpp"

namespace memoris
{
namespace animations
{

class HorizontalMirrorAnimation : public AbstractMirrorAnimation
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the floor index of the level
     */
    HorizontalMirrorAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @brief renders the animation
     *
     * @param floor the level floor to render
     */
    void renderAnimation(const unsigned short& floor) & override;

private:

    /**
     * @brief invert the top side cells with the bottom side cells
     *
     * @param floor the current floor where the animation is rendered
     *
     * not noexcept because it calls SFML methods
     */
    void invertSides(const unsigned short& floor) const &;

    /**
     * @brief changes the transparency of the top side of the level
     *
     * @param floor the current floor where the animation is rendered
     *
     * not noexcept because it calls SFML methods
     */
    void updateTopSideTransparency(const unsigned short& floor) const &;

    /**
     * @brief changes the transparency of the bottom side of the level
     *
     * @param floor the current floor where the animation is rendered
     *
     * not noexcept because it calls SFML methods
     */
    void updateBottomSideTransparency(const unsigned short& floor) const &;

    /**
     * @brief displays the level and the horizontal separator; method created
     * only for refactor purposes as it is called two times at two different
     * moments in the script
     *
     * @param floor constant reference indicating which floor to animate
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void displayLevelAndHorizontalSeparator(const unsigned short& floor)
        const &;

    /**
     * @brief calculates the interved index of the horizontal mirror for the
     * given index
     *
     * @param line constant reference to the current line of the cell (0...15)
     * @param index constant reference to the current index of the cell
     * (0...255) (considere the current floor factor)
     *
     * @return const unsigned short
     */
    const unsigned short findInvertedIndex(
        const unsigned short& line,
        const unsigned short& index
    ) const & noexcept;
};

}
}

#endif
