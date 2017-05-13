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
 * @file DiagonalAnimation.hpp
 * @brief animation that inverts corners
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DIAGONALANIMATION_H_
#define MEMORIS_DIAGONALANIMATION_H_

#include "LevelAnimation.hpp"

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

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the floor index of the level
     */
    DiagonalAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @brief default destructor
     */
    ~DiagonalAnimation();

    /**
     * @brief renders the animation
     */
    void renderAnimation() & override;

private:

    /**
     * @brief switch to the next step of the animation
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void playNextAnimationStep() const &;

    /**
     * @brief display the given floor of the level and the two separators
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void displayLevelAndSeparator() const &;

    /**
     * @brief applies the purple flashing on each side
     *
     * @param color the SFML color object to apply on the cells
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void applyPurpleColorOnCellsQuarters(const sf::Color& color) const &;

    /**
     * @bried invert top left cells with bottom right cells
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void invertTopLeftWithBottomRight() const &;

    /**
     * @brief invert bottom left cells with top right cells
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void invertBottomLeftWithTopRight() const &;

    /**
     * @brief invert top right cells with bottom left cells
     *
     * @param destination the delta to apply on the source cell
     * in order to get the destination cell
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void invertCells(
        const unsigned short& source,
        const short& difference
    ) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
