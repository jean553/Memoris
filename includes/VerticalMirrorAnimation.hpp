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
     * @brief renders the animation
     *
     * @param context constant reference to the current context to use
     * @param level constant reference on shared pointer to the concerned level
     * @param floor constant unsigned integer to the level floor to render
     */
    void renderAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & override;

private:

    static constexpr unsigned short CELLS_PER_LINE_PER_SIDE {8};

    /**
     * @brief replace the left side cells by the right side cells
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void executeMirrorMovement(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief replace the right side cells by the left side cells
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void executeReverseMirrorMovement(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) &;

    /**
     * @brief changes the transparency of the left side of the level
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     * @param floor constant reference indicating which floor to animate
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void updateLeftSideTransparency(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) const &;

    /**
     * @brief changes the transparency of the right side of the level
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     * @param floor constant reference indicating which floor to animate
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void updateRightSideTransparency(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) const &;

    /**
     * @brief displays the level and the vertical separator surface
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     * @param floor constant reference indicating which floor to animate
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void displayLevelAndVerticalSeparator(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) const &;

    /* use to know when the end of the line of the current
       animated side has been reached; this is used to know
       when the animation is switched to the next line without
       animating the other side; check the code of
       setLevelSideCellsTransparency for more details */
    unsigned short sideMax {8};
};

}
}
