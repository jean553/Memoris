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
     * @brief constructor
     *
     * @param context the context to use
     */
    CellsSelector(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~CellsSelector();

    /**
     * @brief displays the cells selector
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void display() const &;

    /**
     * @brief select the cell where the mouse is currently pointing
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void selectMouseHoverCell() const &;

    /**
     * @brief getter of the selected cell type
     *
     * @return const char&
     */
    const char& getSelectedCellType() const & noexcept;

    /**
     * @brief getter of the mouse hover cell type
     *
     * @return const char
     */
    const char getMouseHoverCellType() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
