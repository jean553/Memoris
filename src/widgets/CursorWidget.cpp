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
CursorWidget::~CursorWidget()
{
}

/**
 *
 */
void CursorWidget::display(utils::Context* context)
{
    // update the position of the cursor
    // according to the system position
    sprite.setPosition(
        sf::Mouse::getPosition().x,
        sf::Mouse::getPosition().y
    );

    context->getWindow()->draw(sprite);
}
