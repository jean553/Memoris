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
 * @file CellsSelector.hpp
 * @brief the selector of cells into the level editor
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CELLSSELECTOR_H_
#define MEMORIS_CELLSSELECTOR_H_

#include <memory>

namespace memoris
{
namespace utils
{

class Context;

class CellsSelector
{

public:

    /**
     * @brief constructor, loads the textures from the textures manager to
     * create the sprites (this is done by the initialized implementation)
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    CellsSelector(const utils::Context& context);

    /**
     * @brief default destructor, empty, only used in order to use forwarding
     * declaration
     */
    ~CellsSelector() noexcept;

    /**
     * @brief displays the cells selector
     *
     * @param context constant reference to the current context to use
     *
     * not 'const' because it modifies the cells color if the mouse is hover
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void display(const utils::Context& context) &;

    /**
     * @brief check if the mouse is hover a cell and set the current selected
     * type with this cell type; optimized because the research stops when the
     * concerned cell is found; this method should be called by the level
     * editor
     *
     * @param context reference to the current context to use
     *
     * not 'const' because it modifies the selected cell type and image
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void selectCell(const utils::Context& context) &;

    /**
     * @brief getter of the selected cell type
     *
     * @return const char&
     */
    const char& getSelectedCellType() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
