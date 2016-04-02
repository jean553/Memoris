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
 * @file Widget.hpp
 * @brief widget parent class
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_WIDGET
#define DEF_WIDGET

#include <SFML/Graphics.hpp>

#include "Context.hpp"

namespace widgets
{
class Widget
{

public:

    /**
     * @brief position setter
     *
     * @param hPosition widget horizontal position
     * @param vPosition widget vertical position
     */
    virtual void setPosition(
        float hPosition,
        float vPosition
    );

protected:

    Widget();

    /**
     * Virtual destructor, better to declare as
     * the class is an abstract class, fix security
     * problems that could be caused by polymorphism,
     * whatever happens, we are sure to call both
     * of the child and parent destructor
     */
    virtual ~Widget();

    /**
     * @brief common method to display the widget
     *
     * @param pContext    current context pointer
     */
    virtual void display(utils::Context* pContext) = 0;

    float horizontalPosition;
    float verticalPosition;
};
}

#endif
