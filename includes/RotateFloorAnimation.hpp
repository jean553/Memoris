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
 * @file RotateFloorAnimation.hpp
 * @brief rotates the floor on the left or on the right
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ROTATEFLOORANIMATION_H_
#define MEMORIS_ROTATEFLOORANIMATION_H_

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class RotateFloorAnimation : public LevelAnimation
{

public:

    /**
     * @brief RotateFloorAnimation::MovementDirection
     * @brief the rotate floor animation can rotate to the left or to the right
     */
    enum class MovementDirection {
        Left, /** < move to the left */
        Right /** < move to the right */
    };

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the floor index of the level
     * @param moveDirection indicates if the movement is clockwise or not
     *
     * NOTE: we use a signed integer for the direction and not an enumeration;
     * it's more convenient as we directly use the integer value
     * in order to update the transparency effect values
     */
    RotateFloorAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor,
        const MovementDirection& moveDirection
    );

    /**
     * @brief default destructor
     */
    ~RotateFloorAnimation();

    /**
     * @brief renders the animation
     */
    void renderAnimation() & override;

private:

    /**
     * @brief executes action by jumping to the next animation step
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void playNextAnimationStep() const &;

    /**
     * @brief rotate the cells of the floor on the left
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void rotateCells() const &;

    /**
     * @brief converts the given index into orthogonal coordinates
     *
     * @param index the index to convert
     *
     * @return std::pair<short, short>
     */
    std::pair<short, short>
    getCoordinatesFromIndex(const unsigned short& index) const & noexcept;

    /**
     * @brief converts the given coordinates into index
     *
     * @param x the horizontal coordinate
     * @param y the vertical coordinate
     *
     * @return unsigned short
     * 
     * parameters are passed by copy, we directly modifies the coordinates
     * for index calculation without creating new variables within the function
     */
    unsigned short getIndexFromCoordinates(
        short x,
        short y
    ) const & noexcept;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
