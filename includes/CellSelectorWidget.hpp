/**
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
 * Cells selector widget
 *
 * @file CellSelectorWidget.hpp
 * @brief button widget
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CELL_SELECTOR_WIDGET
#define DEF_CELL_SELECTOR_WIDGET

#include "Widget.hpp"

#include "EmptyCell.hpp"

namespace widgets {
class CellSelectorWidget : public Widget {

public:

    /**
     * @brief displays all the cells for selection
     *
     * @param pContext current context pointer
     */
    void display(utils::Context* pContext);

    /**
     * @brief redefinition of the position setter,
     * as it is necessary to set all the cells position
     *
     * @param hPosition widget horizontal position
     * @param vPosition widget vertical position
     */
    void setPosition(
        float hPosition,
        float vPosition
    );

private:

    entities::EmptyCell emptyCell;
};
}

#endif
