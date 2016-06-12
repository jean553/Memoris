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
 * @file CursorWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CursorWidget.hpp"

using namespace widgets;

const std::string CursorWidget::PATH_IMAGE_CURSOR = "res/images/cursor.png";

/**
 *
 */
CursorWidget::CursorWidget()
{
    picture.loadFromFile(PATH_IMAGE_CURSOR);
    sprite.setTexture(picture);
}

/**
 *
 */
void CursorWidget::display(utils::Context* pContext)
{
    /* NOTE: this is useless, as the CursorWidget attributes are never get,
       instead, we directly get the sf::Cursor position. Despite this, we
       still manually update the widget position to guarantee logic. */
    setPosition(
        sf::Mouse::getPosition().x,
        sf::Mouse::getPosition().y
    );

    sprite.setPosition(
        horizontalPosition,
        verticalPosition
    );

    pContext->getSfmlWindow().draw(sprite);
}
