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
    lifeCell.setStringRepresentation(constants::CellsFileRepresentations::LIFE_CELL);
    malusCell.setStringRepresentation(constants::CellsFileRepresentations::DAMAGE_CELL);
    moreTimeCell.setStringRepresentation(constants::CellsFileRepresentations::MORE_TIME_CELL);
    lessTimeCell.setStringRepresentation(constants::CellsFileRepresentations::LESS_TIME_CELL);
    wallCell.setStringRepresentation(constants::CellsFileRepresentations::WALL_CELL);
    lightCell.setStringRepresentation(constants::CellsFileRepresentations::LIGHT_CELL);
    floorUpCell.setStringRepresentation(constants::CellsFileRepresentations::FLOOR_UP_CELL);
    floorDownCell.setStringRepresentation(constants::CellsFileRepresentations::FLOOR_DOWN_CELL);
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

    lifeCell.setPosition(
        hPosition,
        vPosition + cellsDimensions
    );

    malusCell.setPosition(
        hPosition + cellsDimensions,
        vPosition + cellsDimensions
    );

    moreTimeCell.setPosition(
        hPosition + cellsDimensions * 2,
        vPosition + cellsDimensions
    );

    lessTimeCell.setPosition(
        hPosition + cellsDimensions * 3,
        vPosition + cellsDimensions
    );

    wallCell.setPosition(
        hPosition,
        vPosition + cellsDimensions * 2
    );

    lightCell.setPosition(
        hPosition + cellsDimensions,
        vPosition + cellsDimensions * 2
    );

    floorUpCell.setPosition(
        hPosition + cellsDimensions * 2,
        vPosition + cellsDimensions * 2
    );

    floorDownCell.setPosition(
        hPosition + cellsDimensions * 3,
        vPosition + cellsDimensions * 2
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
    malusCell.display(pContext);
    moreTimeCell.display(pContext);
    lessTimeCell.display(pContext);
    wallCell.display(pContext);
    lightCell.display(pContext);
    floorUpCell.display(pContext);
    floorDownCell.display(pContext);
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
    else if (lifeCell.isMouseHover())
    {
        lifeCell.setSelected(true);
    }
    else if (malusCell.isMouseHover())
    {
        malusCell.setSelected(true);
    }
    else if (moreTimeCell.isMouseHover())
    {
        moreTimeCell.setSelected(true);
    }
    else if (lessTimeCell.isMouseHover())
    {
        lessTimeCell.setSelected(true);
    }
    else if (wallCell.isMouseHover())
    {
        wallCell.setSelected(true);
    }
    else if (lightCell.isMouseHover())
    {
        lightCell.setSelected(true);
    }
    else if (floorUpCell.isMouseHover())
    {
        floorUpCell.setSelected(true);
    }
    else if (floorDownCell.isMouseHover())
    {
        floorDownCell.setSelected(true);
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
    lifeCell.setSelected(false);
    malusCell.setSelected(false);
    moreTimeCell.setSelected(false);
    lessTimeCell.setSelected(false);
    wallCell.setSelected(false);
    lightCell.setSelected(false);
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
    else if (lifeCell.getIsSelected())
    {
        return &lifeCell;
    }
    else if (malusCell.getIsSelected())
    {
        return &malusCell;
    }
    else if (moreTimeCell.getIsSelected())
    {
        return &moreTimeCell;
    }
    else if (lessTimeCell.getIsSelected())
    {
        return &lessTimeCell;
    }
    else if (wallCell.getIsSelected())
    {
        return &wallCell;
    }
    else if (lightCell.getIsSelected())
    {
        return &lightCell;
    }
    else if (floorUpCell.getIsSelected())
    {
        return &floorUpCell;
    }
    else if (floorDownCell.getIsSelected())
    {
        return getFloorDownCell();
    }
    else
    {
        return &emptyCell;
    }
}

/**
 *
 */
entities::Cell* CellSelectorWidget::getFloorDownCell()
{
    return &floorDownCell;
}

/**
 *
 */
entities::Cell* CellSelectorWidget::getFloorUpCell()
{
    return &floorUpCell;
}

/**
 *
 */
entities::Cell* CellSelectorWidget::getEmptyCell()
{
    return &emptyCell;
}
