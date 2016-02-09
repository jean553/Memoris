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

#include "../defines/Dimensions.hpp"
#include "../defines/Colors.hpp"

using namespace entities;

/**
 *
 */
Cell::Cell()
{
    horizontalPosition = 0;
    verticalPosition = 0;

    transparentWhiteColor.r = constants::Colors::COLOR_WHITE_RED;
    transparentWhiteColor.g = constants::Colors::COLOR_WHITE_GREEN;
    transparentWhiteColor.b = constants::Colors::COLOR_WHITE_BLUE;
    transparentWhiteColor.a = constants::Colors::COLOR_ALPHA_PARTIAL;

    whiteColor.r = constants::Colors::COLOR_WHITE_RED;
    whiteColor.g = constants::Colors::COLOR_WHITE_GREEN;
    whiteColor.b = constants::Colors::COLOR_WHITE_BLUE;
    whiteColor.a = constants::Colors::COLOR_ALPHA_FULL;
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
void Cell::setPosition(int hPosition, int vPosition)
{
    horizontalPosition = hPosition;
    verticalPosition = vPosition;

    sprite.setPosition(
        horizontalPosition,
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
}

/**
 *
 */
void Cell::display(utils::Context* pContext)
{
    if (isMouseHover()) {
        sprite.setColor(transparentWhiteColor);
    } else {
        sprite.setColor(whiteColor);
    }

    pContext->getWindow()->draw(sprite);
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
    ) {
        return true;
    }

    return false;
}
