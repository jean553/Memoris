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
     * @brief renders the animation, this function has to be called by the
     * game controller; handles the waiting time (animation update interval)
     * and call the pure virtual function render()
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the concerned level object
     * @param floor the level floor to render
     */
    void renderAnimation(
        utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;

protected:

    /* during the animation, the transparency of the cells is modified
       progressively; the amount of transparency value update at each iteration
       is always the same and equal to 51.f, so we just refactor it in the
       code segment */
    static constexpr float TRANSPARENCY_UPDATE_AMOUNT {51.f};

    /**
     * @brief changes the transparency of a set of cells on the level
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the concerned level object
     * @param startingCellIndex the index of the first cell transparency to
     * update
     * @param difference the positive or negative transparency amount to
     * add or substract
     *
     * NOTE: the 'difference' parameter is passed by copy. This is mandatory
     * to use the variadic parameters (va_list does not work if the previous
     * parameter is a reference)
     */
    virtual void setLevelSideCellsTransparency(
        utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& startingCellIndex,
        const float difference
    ) = 0;

    /**
     * @brief declaration of the function to execute the mirror movement
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    virtual void executeMirrorMovement(
        utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) = 0;

    /**
     * @brief declaration of the function to execute the reverse mirror
     * movement
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    virtual void executeReverseMirrorMovement(
        utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) = 0;

    /**
     * @brief method used for code refactoring; render the level and displays
     * the separator
     *
     * @param context reference to the current context to use
     * @param level shared pointer to the concerned level object
     * @param floor the floor to render
     */
    void displayLevelAndSeparator(
        utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /* the transparency of the animated side during the animation; the default
       value is 255 as the side is totally visible */
    float animatedSideTransparency {255.f};

    /* the SFML surface that represent the red color separator between the
       two mirrored areas; this surface is initialized inside the constructor
       (horizontal or vertical according to the constructor) */
    sf::RectangleShape separator;

    /* a container for the saved cells; during the animation, the cells of one
       side are replaced by the cells of another side; that means we have to
       save a copy of the cells of the first side before we overwritte it */
    std::queue<entities::Cell> savedCells;
};

}
}

#endif
