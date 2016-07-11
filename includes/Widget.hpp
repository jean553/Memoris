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
 * @brief widget parent class; contains the common properties of every widget;
 * contains the vertical and the horizontal position of the widget; this class
 * is abstract
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WIDGET_H_ 
#define MEMORIS_WIDGET_H_ 

/* TODO: never used into the Widget class, should be in the children classes */
#include <SFML/Graphics.hpp>

namespace memoris
{
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
     */
    virtual void display() = 0;

    float horizontalPosition;
    float verticalPosition;
};

}
}

#endif
