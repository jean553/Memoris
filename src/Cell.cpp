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
 * @file Cell.cpp
 * @brief cell entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Cell.hpp"

#include "window.hpp"
#include "cells.hpp"
#include "ColorsManager.hpp"
#include "CellsTexturesManager.hpp"
#include "Context.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

namespace memoris
{
namespace entities
{

class Cell::Impl
{

public:

    Impl(
        const char cellType,
        const float& hPosition,
        const float& vPosition
    ) :
        type(cellType),
        originalHorizontalPosition(hPosition),
        originalVerticalPosition(vPosition)
    {
    }

    char type;

    float originalHorizontalPosition;
    float originalVerticalPosition;
    float horizontalPosition {0.f};
    float verticalPosition {0.f};

    bool highlight {false};
    bool visible {false};

    sf::Sprite sprite;
};

/**
 *
 */
Cell::Cell(
    const utils::Context& context,
    const float& hPosition,
    const float& vPosition,
    const char& cellType
) :
    impl(
        std::make_unique<Impl>(
            cellType,
            hPosition,
            vPosition
        )
    )
{
    setPosition(
        hPosition,
        vPosition
    );

    show(context);
}

/**
 *
 */
Cell::Cell(const Cell& cell) : impl(std::make_unique<Impl>(*cell.impl))
{
    setType(cell.getType());
    setIsVisible(cell.isVisible());
}

/**
 *
 */
Cell::~Cell() = default;

/**
 *
 */
void Cell::moveHorizontally() const &
{
    auto& horizontalPosition = impl->horizontalPosition;

    horizontalPosition += 1;

    if (horizontalPosition > memoris::window::WIDTH)
    {
        constexpr float ANIMATED_CELL_HORIZONTAL_POSITION {-50.f};
        horizontalPosition = ANIMATED_CELL_HORIZONTAL_POSITION;
    }

    setPosition(
        horizontalPosition,
        impl->verticalPosition
    );
}

/**
 *
 */
void Cell::moveInDirection(const MovementDirection& direction) const &
{
    auto& horizontalPosition = impl->horizontalPosition;
    auto& verticalPosition = impl->verticalPosition;

    constexpr float POSITION_UPDATE_STEP {10.f};
    switch(direction)
    {
    case MovementDirection::UP:
    {
        verticalPosition -= POSITION_UPDATE_STEP;

        break;
    }
    case MovementDirection::DOWN:
    {
        verticalPosition += POSITION_UPDATE_STEP;

        break;
    }
    case MovementDirection::LEFT:
    {
        horizontalPosition -= POSITION_UPDATE_STEP;

        break;
    }
    case MovementDirection::RIGHT:
    {
        horizontalPosition += POSITION_UPDATE_STEP;

        break;
    }
    }

    setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void Cell::setPosition(
    const float& hPosition,
    const float& vPosition
) const &
{
    auto& horizontalPosition = impl->horizontalPosition;
    auto& verticalPosition = impl->verticalPosition;

    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    impl->sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
const float& Cell::getHorizontalPosition() const & noexcept
{
    return impl->horizontalPosition;
}

/**
 *
 */
const float& Cell::getVerticalPosition() const & noexcept
{
    return impl->verticalPosition;
}

/**
 *
 */
void Cell::display(
    const utils::Context& context,
    const std::unique_ptr<sf::Transform>& transform
) const &
{
    /* display the cell with a transform SFML object if an object is pointed
       by the given unique pointer reference */
    if (transform != nullptr)
    {
        context.getSfmlWindow().draw(impl->sprite, *transform);
    }
    else
    {
        context.getSfmlWindow().draw(impl->sprite);
    }
}

/**
 *
 */
void Cell::displayWithMouseHover(
    const utils::Context& context,
    const std::unique_ptr<sf::Transform>& transform
) const &
{
    if (isMouseHover() && !impl->highlight)
    {
        impl->highlight = true;

        impl->sprite.setColor(context.getColorsManager().getColorDarkGrey());
    }
    else if(!isMouseHover() && impl->highlight)
    {
        impl->highlight = false;

        impl->sprite.setColor(context.getColorsManager().getColorWhite());
    }

    context.getSfmlWindow().draw(impl->sprite);
}

/**
 *
 */
void Cell::hide(const utils::Context& context) const &
{
    impl->sprite.setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::HIDDEN_CELL
        )
    );

    /* the cell is hidden, so the boolean of visibility is updated to false */
    impl->visible = false;
}

/**
 *
 */
void Cell::show(const utils::Context& context) const &
{
    /* get the texture from the cells textures manager according to the type
       of cell; set this reference as a texture for the current cell object */
    impl->sprite.setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            impl->type
        )
    );

    /* the cell is shown, so the boolean of visibility is updated to true */
    impl->visible = true;

    setCellColorTransparency(
        context,
        255
    );
}

/**
 *
 */
const char& Cell::getType() const & noexcept
{
    return impl->type;
}

/**
 *
 */
void Cell::setType(const char& typeChar) const & noexcept
{
    impl->type = typeChar;
}

/**
 *
 */
void Cell::setCellColorTransparency(
    const utils::Context& context,
    const sf::Uint8& alpha
) const &
{
    sf::Color cellColor = context.getColorsManager().getColorWhiteCopy();

    cellColor.a = alpha;

    impl->sprite.setColor(cellColor);
}

/**
 *
 */
void Cell::setCellColor(const sf::Color& color)
{
    impl->sprite.setColor(color);
}

/**
 *
 */
void Cell::empty() const &
{
    /* set the cell as empty by changing the type to empty cell */
    impl->type = cells::EMPTY_CELL;
}

/**
 *
 */
const bool& Cell::isVisible() const & noexcept
{
    return impl->visible;
}

/**
 *
 */
void Cell::setIsVisible(const bool& visibility) const & noexcept
{
    impl->visible = visibility;
}

/**
 *
 */
const bool Cell::isMouseHover() const
{
    /* get the position of the cursor */
    sf::Vector2<int> cursorPosition = sf::Mouse::getPosition();

    constexpr float CELL_DIMENSION {49.f};
    if (
        cursorPosition.x > impl->horizontalPosition &&
        cursorPosition.x < impl->horizontalPosition + CELL_DIMENSION &&
        cursorPosition.y > impl->verticalPosition &&
        cursorPosition.y < impl->verticalPosition + CELL_DIMENSION
    )
    {
        return true;
    }

    return false;
}

/**
 *
 */
void Cell::resetPosition() &
{
    setPosition(
        impl->originalHorizontalPosition,
        impl->originalVerticalPosition
    );
}

}
}
