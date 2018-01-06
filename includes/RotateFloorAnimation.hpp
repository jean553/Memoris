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

#include <vector>

namespace memoris
{

namespace entities
{
class Cell;
}

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
     * @brief rotates one specific given cell at the given index
     *
     * @param index the index of the cell to rotate
     * @param floor the current index floor
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void rotateCell(
        const unsigned short& index,
        const unsigned short& floor
    ) const &;

    /**
     * @brief rotates one specific given cell from a specific quarter array
     *
     * @param index the index of the cell to rotate (quarter array index)
     * @param convertedIndex the index of the cell to rotate (level index)
     * @param floor the current index floor
     * @param cellsCopy array used to store temporarily the quarter of cells
     *
     * TODO: check if an array of cells is enough
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void rotateCellFromQuarter(
        const unsigned short& index,
        const unsigned short& convertedIndex,
        const unsigned short& floor,
        const std::vector<std::unique_ptr<entities::Cell>>& cellsCopy
    ) const &;

    /**
     * @brief converts the given index into orthogonal coordinates
     *
     * @param index the index to convert
     * @param floor the current index floor
     *
     * @return std::pair<short, short>
     */
    std::pair<short, short>
    getCoordinatesFromIndex(
        const unsigned short& index,
        const unsigned short& floor
    ) const & noexcept;

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

    /**
     * @brief updates the destination cell visibility
     * according to the source cell visibility
     *
     * @param source the source cell
     * @param destination the destination cell
     *
     * not noexcept as some functions call the SFML methods
     */
    void updateDestinationCellVisibility(
        const entities::Cell& source,
        const entities::Cell& destination
    ) const &;

    /**
     * @brief generates a copy of a given cell in order to be stored
     * into a container that stores a quarter of cell (for rotation);
     * it only copies the type and the visibility, the only two elements
     * that are necessary to be known in order to copy the cell
     * for rotation purposes; positions are set to 0 as they are useless;
     *
     * @param cell the source cell to copy
     *
     * @return std::unique_ptr<entities::Cell>
     *
     * not noexcept as the function calls some SFML functions
     *
     * the returned unique_ptr is not constant as it has to be moved by client
     */
    std::unique_ptr<entities::Cell> getCellCopy(
        const entities::Cell& source
    ) const &;

    /**
     * @brief updates the horizontal or vertical coordinates
     * according to the rotation direction
     *
     * @param x the orthogonal x coordinate
     * @param y the orthogonal y coordinate
     *
     * the passed references are supposed to modify
     * their values within the function
     */
    void updateCoordinates(
        short& x,
        short& y
    ) const & noexcept;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
