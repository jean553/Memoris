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
 * @file VerticalMirrorAnimation.hpp
 * @brief plays the vertical mirror animation
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractMirrorAnimation.hpp"

namespace memoris
{
namespace animations
{

class VerticalMirrorAnimation : public AbstractMirrorAnimation
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the floor index of the level
     */
    VerticalMirrorAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @brief renders the animation
     */
    void renderAnimation() & override;

private:

    /**
     * @brief replace the left side cells by the right side cells
     */
    void invertSides() &;

    /**
     * @brief changes the transparency of the left side of the level
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void updateLeftSideTransparency() const &;

    /**
     * @brief changes the transparency of the right side of the level
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void updateRightSideTransparency() const &;

    /**
     * @brief displays the level and the vertical separator surface
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void displayLevelAndVerticalSeparator() const &;

    /**
     * @brief returns the inverted index of the vertical mirror animation
     *
     * @param line constant reference to the current line
     * @param index constant reference to the current index
     *
     * @return const unsigned short
     *
     * does not return a constant reference because the method directly returns
     * the calculated value and not an object attribute
     */
    const unsigned short findInvertedIndex(
        const unsigned short& line,
        const unsigned short& index
    ) const & noexcept;
};

}
}
