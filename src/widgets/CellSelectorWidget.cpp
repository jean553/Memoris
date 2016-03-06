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
 * Editor of levels.
 *
 * @file EditorLevelController.cpp
 * @brief levels editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellSelectorWidget.hpp"

#include "Dimensions.hpp"
#include "Sounds.hpp"

using namespace widgets;

const short CellSelectorWidget::COLUMNS_AMOUNT = 4;
const short CellSelectorWidget::ROWS_AMOUNT = 3;

/**
 *
 */
CellSelectorWidget::CellSelectorWidget()
{
    soundCellSelectionBuffer.loadFromFile(
        constants::Sounds::CELL_SELECTOR_SELECTION_SOUND_PATH
    );

    soundCellSelection.setBuffer(
        soundCellSelectionBuffer
    );
}

/**
 *
 */
void CellSelectorWidget::setPosition(
    float hPosition,
    float vPosition
) {

    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    emptyCell.setPosition(
        hPosition,
        vPosition
    );

    departureCell.setPosition(
        hPosition + constants::Dimensions::CELL_PIXELS_DIMENSIONS +
        constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION,
        vPosition
    );

    arrivalCell.setPosition(
        hPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ) * 2,
        vPosition
    );

    starCell.setPosition(
        hPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ) * 3,
        vPosition
    );

    lifeCell.setPosition(
        hPosition,
        vPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        )
    );

    damageCell.setPosition(
        hPosition + constants::Dimensions::CELL_PIXELS_DIMENSIONS +
        constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION,
        vPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        )
    );

    moreTimeCell.setPosition(
        hPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ) * 2,
        vPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        )
    );

    lessTimeCell.setPosition(
        hPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ) * 3,
        vPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        )
    );

    floorUpCell.setPosition(
        hPosition,
        vPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ) * 2
    );

    floorDownCell.setPosition(
        hPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ),
        vPosition +
        (
            constants::Dimensions::CELL_PIXELS_DIMENSIONS +
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION
        ) * 2
    );
}

/**
 *
 */
void CellSelectorWidget::display(utils::Context* pContext)
{
    emptyCell.display(pContext);
    departureCell.display(pContext);
    arrivalCell.display(pContext);
    starCell.display(pContext);
    lifeCell.display(pContext);
    damageCell.display(pContext);
    moreTimeCell.display(pContext);
    lessTimeCell.display(pContext);
    floorUpCell.display(pContext);
    floorDownCell.display(pContext);
}

/**
 *
 */
void CellSelectorWidget::selectCellOnClick()
{
    unselectAllCells();

    if (emptyCell.isMouseHover()) {
        emptyCell.setSelected(true);
    }
    else if (departureCell.isMouseHover()) {
        departureCell.setSelected(true);
    }
    else if (arrivalCell.isMouseHover()) {
        arrivalCell.setSelected(true);
    }
    else if (starCell.isMouseHover()) {
        starCell.setSelected(true);
    }
    else if (lifeCell.isMouseHover()) {
        lifeCell.setSelected(true);
    }
    else if (damageCell.isMouseHover()) {
        damageCell.setSelected(true);
    }
    else if (moreTimeCell.isMouseHover()) {
        moreTimeCell.setSelected(true);
    }
    else if (lessTimeCell.isMouseHover()) {
        lessTimeCell.setSelected(true);
    }
    else if (floorUpCell.isMouseHover()) {
        floorUpCell.setSelected(true);
    }
    else if (floorDownCell.isMouseHover()) {
        floorDownCell.setSelected(true);
    }

    //TODO: should not be played when no cell is selected,
    //I keep it here for now as the selector is a cells rectangle
    //and this problem is not supposed to happen in the future
    soundCellSelection.play();
}

/**
 *
 */
void CellSelectorWidget::unselectAllCells()
{
    emptyCell.setSelected(false);
    departureCell.setSelected(false);
    arrivalCell.setSelected(false);
    starCell.setSelected(false);
    lifeCell.setSelected(false);
    damageCell.setSelected(false);
    moreTimeCell.setSelected(false);
    lessTimeCell.setSelected(false);
    floorUpCell.setSelected(false);
    floorDownCell.setSelected(false);
}

/**
 *
 */
bool CellSelectorWidget::isMouseHover() const
{
    if (
        sf::Mouse::getPosition().x > horizontalPosition &&
        sf::Mouse::getPosition().x < horizontalPosition +
        (
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION +
            constants::Dimensions::CELL_PIXELS_DIMENSIONS
        ) * COLUMNS_AMOUNT &&
        sf::Mouse::getPosition().y > verticalPosition &&
        sf::Mouse::getPosition().y < verticalPosition +
        (
            constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION +
            constants::Dimensions::CELL_PIXELS_DIMENSIONS
        ) * ROWS_AMOUNT
    ) {
        return true;
    }

    return false;
}

/**
 *
 */
entities::Cell* CellSelectorWidget::getSelectedNewCellPointer()
{
    if (departureCell.getIsSelected()) {
        return new entities::DepartureCell();
    }
    else if (arrivalCell.getIsSelected()) {
        return new entities::ArrivalCell();
    }
    else if (starCell.getIsSelected()) {
        return new entities::StarCell();
    }
    else if (lifeCell.getIsSelected()) {
        return new entities::LifeCell();
    }
    else if (damageCell.getIsSelected()) {
        return new entities::DamageCell();
    }
    else if (moreTimeCell.getIsSelected()) {
        return new entities::MoreTimeCell();
    }
    else if (lessTimeCell.getIsSelected()) {
        return new entities::LessTimeCell();
    }
    else if (floorUpCell.getIsSelected()) {
        return new entities::FloorUpCell();
    }
    else if (floorDownCell.getIsSelected()) {
        return new entities::FloorDownCell();
    } else {
        return new entities::EmptyCell();
    }

    return NULL;
}
