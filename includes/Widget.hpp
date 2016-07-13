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
     * @brief widget position setter
     *
     * @param hPosition widget horizontal position
     * @param vPosition widget vertical position
     *
     * TODO: #503 this method should be deleted; set the widget position is
     * only done through the constructor
     */
    void setPosition(
        float hPosition,
        float vPosition
    );

protected:

    /**
     * @brief constructor, initialize the widget positions values; this
     * constructor is protected because only called by children classes as the
     * Widget class is abstract (we never directly create a Widget instance)
     *
     * @param hPosition widget horizontal position
     * @param vPosition widget vertical position
     *
     * TODO: #503 this feature is not developed yet, so some widgets are not
     * using the Widget constructor by sending directly the positions values to
     * it; the default value of these positions should be deleted when all the
     * widgets directly set the positions when the widget constructor is
     * called
     */
    Widget(
        const float& hPosition = 0,
        const float& vPosition = 0
    );

    /**
     * @brief destructor, virtual and empty; virtual because we create
     * children of this Widget class, we have to ensure that the child
     * object destructor is called
     */
    virtual ~Widget();

    /**
     * @brief pure virtual function to render the widget; according to the
     * child widget, this method has to be written in every widget class;
     * makes the Widget abstract
     */
    virtual void display() = 0;

    /* NOTE: we use float for the widget position because it is the type
       used by the SFML library to set surfaces positions */

    /* NOTE: we do not initialize these non-static members here, in fact, they
       are directly initialized with the values given by the child object
       by the constructor */

    /* the horizontal position of the widget */
    float horizontalPosition;

    /* the vertical position of the widget */
    float verticalPosition;
};

}
}

#endif
