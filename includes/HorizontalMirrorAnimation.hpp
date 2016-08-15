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

#include "LevelAnimation.hpp"

namespace memoris
{
namespace animations
{

class HorizontalMirrorAnimation : public LevelAnimation
{

public:

    /**
     * @brief constructor, initializes the separator
     *
     * @param context shared pointer to the context to use
     */
    HorizontalMirrorAnimation(
        const std::shared_ptr<utils::Context>& context
    );

    /**
     * @brief renders the animation
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void render(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) override;

private:

    /**
     * @brief horizontally invert all the cells
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void replaceHighCellsByLowCells(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @brief invert all the low cells (cells that are in the bottom area of
     * the level)
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     */
    void replaceLowCellsByHighCells(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    /**
     * @brief used for the animation of the grid; this function updates the
     * transparency value of 160 cells starting at the given index; the
     * modification to apply is specified by the 'difference' parameter
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param floor the current floor to display in the animation
     * @param difference the color transparency update to apply on the
     * transparency value of the cells textures
     */
    void setLevelSideCellsTransparency(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& startingCellIndex,
        const float& difference
    );

    /**
     * @brief function created for refactoring purposals; takes one cell index
     * and specifies if this cell is visible or not
     *
     * @param context shared pointer to the current context to use
     * @param level shared pointer to the level to use
     * @param index concerned cell index
     * @param visible true if the cell is visible, false if the cell is hidden
     */
    void showOrHideCell(
        const std::shared_ptr<utils::Context>& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& index,
        const bool& visible
    );

    /* the horizontal separator; this serparator is a horizontal red line
       displayed during the whole mirror animation in the middle of the
       level */
    sf::RectangleShape separator;

    /* contains all the types of the cells of the bottom side; this is used
       to save the types of these cells when they are replaced by the top
       side cells */
    std::vector<char> lowCells;

    /* contains the visible parameter of the cells of the bottom side; this is
       used to save the visibility parameter of these cells when they are
       replaced by the top side cells */
    std::vector<bool> visible;

    /* this boolean is set to true if the next player cell has been calculated
       ; we use it to avoid to calculate it again according on which level
       cells side we are working on */
    bool gotDestinationCell {false};

    /* the index of the next player cell after the animation; by default, the
       value is 0 */
    unsigned short destinationCell {0};

    float gradient {255.f};
};

}
}

#endif
