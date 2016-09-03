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
 * @file Cursor.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Cursor.hpp"

namespace memoris
{
namespace widgets
{

/**
 *
 */
Cursor::Cursor(const std::shared_ptr<utils::Context>& context)
{
    /* get the cursor texture from the textures manager */
    sprite.setTexture(context->getTexturesManager().getCursorTexture());
}

/**
 *
 */
void Cursor::render(const std::shared_ptr<utils::Context>& context)
{
    /* display the cursor */
    context->getSfmlWindow().draw(sprite);

    /* only move the cursor if more than 50 milliseconds elapsed */
    if (
        context->getClockMillisecondsTime() - 
        lastCursorPositionUpdateTime < 50
    )
    {
        return;
    }

    /* the cursor position is now the mouse position */
    sprite.setPosition(
        sf::Mouse::getPosition().x,
        sf::Mouse::getPosition().y
    );
}

}
}
