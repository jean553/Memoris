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

#include "Context.hpp"

#include "Cell.hpp"
#include "aliases.hpp"

namespace memoris
{
namespace utils
{

class CellsSelector
{

public:

    /**
     * @brief constructor, loads the textures from the textures manager to
     * create the sprites
     *
     * @param context reference to the current context to use
     */
    CellsSelector(utils::Context& context);

    /**
     * @brief displays the cells selector
     *
     * @param context reference to the current context to use
     */
    void display(utils::Context& context);

    /**
     * @brief check if the mouse is hover a cell and set the current selected
     * type with this cell type; optimized because the research stops when the
     * concerned cell is found; this method should be called by the level
     * editor
     *
     * @param context reference to the current context to use
     */
    void selectCell(utils::Context& context);

    const char& getSelectedCellType() const;

private:

    /* the cells container of the selector */
    std::vector<entities::Cell> cells;

    /* the type of the current selected cell */
    char selectedCellType {'e'};

    /* separated sprite used to display the current selected cell picture */
    sf::Sprite selectedCellImage;
};

}
}

#endif
