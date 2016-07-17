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

#include <SFML/Audio.hpp>

#include "Widget.hpp"
#include "Cell.hpp"

namespace widgets
{
class CellSelectorWidget : public memoris::widgets::Widget
{

public:

    static const short COLUMNS_AMOUNT;
    static const short ROWS_AMOUNT;

    /**
     * @brief constructor
     */
    CellSelectorWidget();

    /**
     * @brief displays all the cells for selection
     */
    void display();

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

    /**
     * @brief select a cell on click, should be used
     * in the controller loop after a click event
     */
    void selectCellOnClick();

    /**
     * @brief detects if the mouse is hover the widget
     *
     * @return true if the mouse is hover
     */
    bool isMouseHover() const;

    /**
     * @brief return a pointer to a new cell, the same type as the selected cell
     *
     * @return entities::Cell*
     */
    memoris::entities::Cell* getSelectedNewCellPointer();

    /**
     * @brief return a pointer to the down floor cell, used
     * to automatically add this down cell when the up one is added
     *
     * @return entities::Cell*
     */
    memoris::entities::Cell* getFloorDownCell();

    /**
     * @brief return a pointer to the up floor cell, used
     * to automatically add this up cell when the down one is added
     *
     * @return entities::Cell*
     */
    memoris::entities::Cell* getFloorUpCell();

    /**
     * @brief return a pointer to the empty cell, used
     * to automatically update the level according to
     * the current selected cell
     *
     * @return entities::Cell*
     */
    memoris::entities::Cell* getEmptyCell();

private:

    /**
     * @brief unselect all the cells of the selector
     */
    void unselectAllCells();

    memoris::entities::Cell emptyCell;
    memoris::entities::Cell departureCell;
    memoris::entities::Cell arrivalCell;
    memoris::entities::Cell starCell;
    memoris::entities::Cell lifeCell;
    memoris::entities::Cell malusCell;
    memoris::entities::Cell moreTimeCell;
    memoris::entities::Cell lessTimeCell;
    memoris::entities::Cell wallCell;
    memoris::entities::Cell lightCell;
    memoris::entities::Cell floorUpCell;
    memoris::entities::Cell floorDownCell;
};
}

#endif
