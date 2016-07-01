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
 * @file Cell.cpp
 * @brief cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Cell.hpp"

#include "Dimensions.hpp"
#include "ColorsManager.hpp"

using namespace entities;

const uint8_t Cell::INTERVAL_ANIMATION = 10;
const uint8_t Cell::SELECTOR_COLOR_INCREMENTATION_STEP = 15;
const uint16_t Cell::MAXIMUM_RED_COLOR_AMOUNT = 255;
const uint16_t Cell::MINIMUM_RED_COLOR_AMOUNT = 0;

/**
 *
 */
Cell::Cell(utils::Context& context)
{
    /* TODO: this is not used inside the copy constructor,
      because we are mandatory to pass the context as
      a parameter of the copy constructor. If we do that,
      this is not a copy constructor anymore... Need to
      find a solution for this... */
    /* the selector color is continually updated, that's
       why we copy it from the red color first */
    selectorColor = memoris::colors::ColorsManager::get().getColorRed();
    initializeCommonAttributes();
}

/**
 *
 */
Cell::Cell(const Cell& cell)
{
    initializeCommonAttributes();

    setPicturePath(cell.getPicturePath());

    setPosition(
        cell.getHorizontalPosition(),
        cell.getVerticalPosition()
    );

    setLevelAddresses(cell.getAddress());

    setStringRepresentation(cell.getStringRepresentation());
}

/**
 *
 */
Cell::Cell(
    utils::Context& context,
    std::string fileValue) :
    stringRepresentation(fileValue)
{
    selectorColor = memoris::colors::ColorsManager::get().getColorRed();
    initializeCommonAttributes();
}

/**
 *
 */
Cell::~Cell()
{
}

/**
 *
 */
void Cell::performAction()
{
}

/**
 *
 */
void Cell::setPosition(
    float hPosition,
    float vPosition
)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );

    hiddenCellPtr.setSpritePosition(
        horizontalPosition,
        verticalPosition
    );

    topSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition
    );

    bottomSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition +
        constants::Dimensions::CELL_PIXELS_DIMENSIONS -
        constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH
    );

    leftSelectionBar.setPosition(
        horizontalPosition,
        verticalPosition
    );

    rightSelectionBar.setPosition(
        horizontalPosition +
        constants::Dimensions::CELL_PIXELS_DIMENSIONS -
        constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH,
        verticalPosition
    );
}

/**
 *
 */
void Cell::setPicturePath(std::string path)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture, true);

    picturePath = path;
}

/**
 *
 */
std::string Cell::getPicturePath() const
{
    return picturePath;
}

/**
 *
 */
void Cell::display(utils::Context& context)
{
    sf::Sprite sprToDspl;

    if (getIsHidden())
    {
        sprToDspl = hiddenCellPtr.getSprite();
    }
    else
    {
        sprToDspl = sprite;
    }

    if (isMouseHover() && isCursorSensitive)
    {
        sprToDspl.setColor(memoris::colors::ColorsManager::get().getColorPartialWhite());
    }
    else
    {
        sprToDspl.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    }

    context.getSfmlWindow().draw(sprToDspl);

    if (isSelected)
    {
        if (isAnimated)
        {
            animateCell();
        }

        context.getSfmlWindow().draw(topSelectionBar);
        context.getSfmlWindow().draw(bottomSelectionBar);
        context.getSfmlWindow().draw(leftSelectionBar);
        context.getSfmlWindow().draw(rightSelectionBar);
    }
}

/**
 *
 */
bool Cell::isMouseHover() const
{
    if (
        sf::Mouse::getPosition().x > horizontalPosition &&
        sf::Mouse::getPosition().x < horizontalPosition + constants::Dimensions::CELL_PIXELS_DIMENSIONS &&
        sf::Mouse::getPosition().y > verticalPosition &&
        sf::Mouse::getPosition().y < verticalPosition + constants::Dimensions::CELL_PIXELS_DIMENSIONS
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void Cell::setSelected(bool selected)
{
    isSelected = selected;
}

/**
 *
 */
float Cell::getHorizontalPosition() const
{
    return horizontalPosition;
}

/**
 *
 */
float Cell::getVerticalPosition() const
{
    return verticalPosition;
}

/**
 *
 */
void Cell::setLevelAddresses(const uint16_t& cellAddress)
{
    address = cellAddress;
}

/**
 *
 */
uint16_t Cell::getAddress() const
{
    return address;
}

/**
 *
 */
bool Cell::getIsSelected() const
{
    return isSelected;
}

/**
 *
 */
void Cell::setHidden(const bool& hidden)
{
    isHidden = hidden;
}

/**
 *
 */
bool Cell::getIsHidden() const
{
    return isHidden;
}

/**
 *
 */
void Cell::setCursorSensitivity(const bool& sensitivity)
{
    isCursorSensitive = sensitivity;
}

/**
 *
 */
void Cell::initializeCommonAttributes()
{
    isSelected = false;
    isHidden = false;
    isCursorSensitive = true;
    isAnimated = false;

    horizontalPosition = 0;
    verticalPosition = 0;
    address = 0;
    selectorDirection = -1;


    topSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::CELL_PIXELS_DIMENSIONS,
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH
        )
    );

    bottomSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::CELL_PIXELS_DIMENSIONS,
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH
        )
    );

    leftSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH,
            constants::Dimensions::CELL_PIXELS_DIMENSIONS
        )
    );

    rightSelectionBar.setSize(
        sf::Vector2f(
            constants::Dimensions::SELECTED_CELLS_BORDER_WIDTH,
            constants::Dimensions::CELL_PIXELS_DIMENSIONS
        )
    );

    topSelectionBar.setFillColor(selectorColor);
    bottomSelectionBar.setFillColor(selectorColor);
    leftSelectionBar.setFillColor(selectorColor);
    rightSelectionBar.setFillColor(selectorColor);
}

/**
 *
 */
void Cell::setStringRepresentation(const std::string& representation)
{
    stringRepresentation = representation;

    /* force the update of the picture path */
    setPicturePath("res/cells/" + representation + ".png");
}

/**
 *
 */
std::string Cell::getStringRepresentation() const
{
    return stringRepresentation;
}

/**
 *
 */
void Cell::setIsAnimated(const bool& animate)
{
    isAnimated = animate;
}

/**
 *
 */
void Cell::animateCell()
{
    if(clock.getElapsedTime().asMilliseconds() <= INTERVAL_ANIMATION)
    {
        return;
    }

    selectorColor.g +=
        SELECTOR_COLOR_INCREMENTATION_STEP * selectorDirection;
    selectorColor.b +=
        SELECTOR_COLOR_INCREMENTATION_STEP * selectorDirection;

    topSelectionBar.setFillColor(selectorColor);
    bottomSelectionBar.setFillColor(selectorColor);
    leftSelectionBar.setFillColor(selectorColor);
    rightSelectionBar.setFillColor(selectorColor);

    if (
        selectorColor.g == MINIMUM_RED_COLOR_AMOUNT ||
        selectorColor.g == MAXIMUM_RED_COLOR_AMOUNT
    )
    {
        selectorDirection *= -1;
    }

    clock.restart();
}
