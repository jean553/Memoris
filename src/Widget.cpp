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
 * @file Widget.cpp
 * @brief widget parent class
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Widget.hpp"

namespace memoris
{
namespace widgets
{

/**
 *
 */
Widget::Widget(
    std::shared_ptr<utils::Context> contextPtr,
    const float& hPosition,
    const float& vPosition
) :
    context(contextPtr),
    horizontalPosition(hPosition),
    verticalPosition(vPosition)
{
    /* does nothing, only assigned the given parameters into the attributes */
}

/**
 *
 */
Widget::~Widget()
{
    /* virtual destructor that we have to declare in order to ensure that
       the children widgets destructors are called correctly when a child
       object is pointed by a parent pointer and the pointed object is
       deleted */
}

/**
 *
 */
void Widget::setPosition(
    float hPosition,
    float vPosition
)
{
    /* update the widget position according to the given horizontal and
       vertical position */
    horizontalPosition = hPosition;
    verticalPosition = vPosition;
}

}
}
