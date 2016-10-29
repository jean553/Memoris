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
 * @file AbstractMirrorAnimation.hpp
 * @brief abstract class that manages the level mirror animations
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTMIRRORANIMATION
#define MEMORIS_ABSTRACTMIRRORANIMATION

#include "LevelAnimation.hpp"

#include "Cell.hpp"

#include <queue>

namespace memoris
{
namespace animations
{

class AbstractMirrorAnimation : public LevelAnimation
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

protected:

    /**
     * @brief changes the transparency of a set of cells on the level
     *
     * @param context constant reference to the current context to use
     * @param level constant shared pointer to the concerned level object
     * @param startingCellIndex the index of the first cell transparency to
     */
    virtual void setLevelSideCellsTransparency(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& startIndex
    ) & = 0;

    /**
     * @brief declaration of the function to execute the mirror movement
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    virtual void executeMirrorMovement(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & = 0;

    /**
     * @brief declaration of the function to execute the reverse mirror
     * movement
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    virtual void executeReverseMirrorMovement(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & = 0;

    /**
     * @brief increases the transparency
     *
     * not 'const' because it modifies the animated side transparency
     */
    void increaseTransparency() & noexcept;

    /**
     * @brief increases the transparency
     *
     * not 'const' because it modifies the animated side transparency
     */
    void decreaseTransparency() & noexcept;

    /**
     * @brief applies the current animated side transparency on the given cell
     *
     * @param context constant reference to the current context to use
     * @param level constant reference to a shared pointer on the level
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void applyTransparencyOnOneCell(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& index
    ) const &;

    /* these attributes are not inside an
       implementation as they are protected */

    /* TODO: check if can be deleted */
    std::queue<entities::Cell> savedCells;

    /* TODO: move it in private attributes */
    float animatedSideTransparency {255.f};

private:

    static constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};
    static constexpr float TRANSPARENCY_INTERVAL {51.f};
};

}
}

#endif
