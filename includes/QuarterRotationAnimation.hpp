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
 * @file QuarterRotationAnimation.hpp
 * @brief rotate the quarters
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_QUARTERROTATIONANIMATION_H_
#define MEMORIS_QUARTERROTATIONANIMATION_H_

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class QuarterRotationAnimation : public LevelAnimation
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the floor index of the animation
     */
    QuarterRotationAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @brief default destructor
     */
    ~QuarterRotationAnimation();

    /**
     * @brief renders the animation
     */
    void renderAnimation() & override;

private:

    /**
     * @brief move all the quarters at the same time in the expected direction
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void moveAllQuarters() const &;

    /**
     * @brief invert the cells after the animation; update the position of all
     * the floor cells at the same time
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void updateCells() const &;

    /**
     * @brief apply the given modification on the given cell index
     *
     * @param index the index of the cell to move
     * @param modification the movement of the selected cell
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void invertCells(
        const unsigned short& index,
        const unsigned short& modification
    ) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
