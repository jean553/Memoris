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
#include "CellsFileRepresentations.hpp"
#include "CellFactory.hpp"

using namespace widgets;

const short CellSelectorWidget::COLUMNS_AMOUNT = 4;
const short CellSelectorWidget::ROWS_AMOUNT = 5;

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

    /* TODO: to refactor... */
    emptyCell.setStringRepresentation(constants::CellsFileRepresentations::EMPTY_CELL);
    departureCell.setStringRepresentation(constants::CellsFileRepresentations::DEPARTURE_CELL);
    arrivalCell.setStringRepresentation(constants::CellsFileRepresentations::ARRIVAL_CELL);
    starCell.setStringRepresentation(constants::CellsFileRepresentations::STAR_CELL);

    emptyCell.setPicturePath(factories::CellFactory::EMPTY_CELL_PICTURE_PATH);
    departureCell.setPicturePath(factories::CellFactory::DEPARTURE_CELL_PICTURE_PATH);
    arrivalCell.setPicturePath(factories::CellFactory::ARRIVAL_CELL_PICTURE_PATH);
    starCell.setPicturePath(factories::CellFactory::STAR_CELL_PICTURE_PATH);
}

/**
 *
 */
void CellSelectorWidget::setPosition(
    float hPosition,
    float vPosition
)
{
    const float cellsDimensions =
        constants::Dimensions::CELL_PIXELS_DIMENSIONS +
        constants::Dimensions::SELECTOR_CELLS_PIXELS_SEPARATION;

    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    emptyCell.setPosition(
        hPosition,
        vPosition
    );

    departureCell.setPosition(
        hPosition + cellsDimensions,
        vPosition
    );

    arrivalCell.setPosition(
        hPosition + cellsDimensions * 2,
        vPosition
    );

    starCell.setPosition(
        hPosition + cellsDimensions * 3,
        vPosition
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
}

/**
 *
 */
void CellSelectorWidget::selectCellOnClick()
{
    unselectAllCells();

    if (emptyCell.isMouseHover())
    {
        emptyCell.setSelected(true);
    }
    else if (departureCell.isMouseHover())
    {
        departureCell.setSelected(true);
    }
    else if (arrivalCell.isMouseHover())
    {
        arrivalCell.setSelected(true);
    }
    else if (starCell.isMouseHover())
    {
        starCell.setSelected(true);
    }

    /* TODO: should not be played when no cell is selected,
       I keep it here for now as the selector is a cells rectangle
       and this problem is not supposed to happen in the future */
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
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
entities::Cell* CellSelectorWidget::getSelectedNewCellPointer()
{
    if (departureCell.getIsSelected())
    {
        return &departureCell;
    }
    else if (arrivalCell.getIsSelected())
    {
        return &arrivalCell;
    }
    else if (starCell.getIsSelected())
    {
        return &starCell;
    }
    else
    {
        return &emptyCell;
    }
}
