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
     * @param level constant reference to shared pointer on the level to use
     * @param floor the current floor to display in the animation
     */
    void playNextAnimationStep(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & override;

private:

    static constexpr unsigned short TOP_SIDE_FIRST_CELL_INDEX {0};
    static constexpr unsigned short TOP_SIDE_LAST_CELL_INDEX {128};
    static constexpr unsigned short BOTTOM_SIDE_LAST_CELL_INDEX {255};
    static constexpr unsigned short CELLS_PER_FLOOR {256};

    /**
     * @brief replace the high cells by the low cells
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void executeReverseMirrorMovement(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & override;

    /**
     * @brief replace the low cells by the high cells
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void executeMirrorMovement(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & override;

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
        const std::shared_ptr<entities::Level>& level,
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
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) const &;
};

}
}

#endif
