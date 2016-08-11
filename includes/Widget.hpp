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

#include "Context.hpp"

namespace memoris
{
namespace widgets
{

class Widget
{

protected:

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
     *
     * @param context shared pointer to the context to use
     */
    virtual void display(std::shared_ptr<utils::Context> context) = 0;
};

}
}

#endif
