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

#include "EmptyCell.hpp"
#include "DepartureCell.hpp"
#include "ArrivalCell.hpp"
#include "StarCell.hpp"
#include "LifeCell.hpp"
#include "DamageCell.hpp"
#include "MoreTimeCell.hpp"
#include "LessTimeCell.hpp"

namespace widgets {
class CellSelectorWidget : public Widget {

public:

    static const short COLUMNS_AMOUNT;
    static const short ROWS_AMOUNT;

    CellSelectorWidget();

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
     * @return pointer to the new created cell
     */
    entities::Cell* getSelectedNewCellPointer();

private:

    /**
     * @brief unselect all the cells of the selector
     */
    void unselectAllCells();

    entities::EmptyCell emptyCell;
    entities::DepartureCell departureCell;
    entities::ArrivalCell arrivalCell;
    entities::StarCell starCell;
    entities::LifeCell lifeCell;
    entities::DamageCell damageCell;
    entities::MoreTimeCell moreTimeCell;
    entities::LessTimeCell lessTimeCell;

    sf::SoundBuffer soundCellSelectionBuffer;

    sf::Sound soundCellSelection;
};
}

#endif
