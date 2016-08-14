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
 * @file MenuGradient.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MenuGradient.hpp"

#include "window.hpp"

namespace memoris
{
namespace others
{

/**
 *
 */
MenuGradient::MenuGradient(const std::shared_ptr<utils::Context>& context)
{
    /* the width of the menuBackground surface is fixed and the height is equal
       to the window height */
    menuBackground.setSize(
        sf::Vector2f(
            620.f,
            window::HEIGHT
        )
    );

    /* the menuBackground surface is graphically displayed at the horizontal
       center of the screen */
    menuBackground.setPosition(480.f, 0);

    /* the menuBackground surface is full black */
    menuBackground.setFillColor(context->getColorsManager().getColorBlack());

    /* initialize all the rectangles that are necessary to make the gradient
       visual effect */
    initializeGradientRectangles(context);
}

/**
 *
 */
void MenuGradient::display(const std::shared_ptr<utils::Context>& context)
{
    /* display first the menu background */
    context->getSfmlWindow().draw(menuBackground);

    /* iterate the whole sides lines container and displays them one by one */
    for (const sf::RectangleShape& rectangle : sidesLines)
    {
        context->getSfmlWindow().draw(rectangle);
    }
}

/**
 *
 */
void MenuGradient::initializeGradientRectangles(
    const std::shared_ptr<utils::Context>& context
)
{
    /* NOTE: the creation of the rectangles can be done directly inside the
      constructor of the class; in fact, there are many local variables
      to use to create these surfaces; in order to improve the code
      organization and clarity, we create these surfaces into a dedicated
      function. */

    /* horizontal position of the current created line; this cursor is edited,
       incremented and decremented continually during the gradient lines
       creation */
    float horizontalPosition = 479.f;

    /* this color is continually updated for each created line; the alpha
       value is continually modified to make the gradient effect; this color
       is copied first because we continually modify it and because we copy
       it to each created surface */
    sf::Color effectColor = context->getColorsManager().getColorBlackCopy();

    /* iterate the loop 1020 times: this is the required amount of surfaces to
       make the gradient effect on both sides of the menu background */
    for (unsigned long index = 1020; index > 0; index--)
    {
        /* create a temporary object that exists only during the loop
           iteration; set all the values of the SFML rectangle in order to
           add it into the rectangles container */
        sf::RectangleShape rectangle;

        /* the position of the current created rectangle is always vertically
           null and horizontally equals to the current horizontal position
           cursor value */
        rectangle.setPosition(horizontalPosition, 0);

        /* the gradient lines all have the same surface size; the width is one
           pixel and the height is equal to the window height */
        rectangle.setSize(
            sf::Vector2f(1, window::HEIGHT)
        );

        /* set the current calculated color to the surface */
        rectangle.setFillColor(effectColor);

        /* we increment or decrement the current horizontal position cursor
           according to the current iteration index; in fact, we have to check
           if we are creating the left side or the right side of the menu */
        if(index >= 510)
        {
            horizontalPosition--;
        }
        else
        {
            horizontalPosition++;
        }

        /* when we are in the middle of the iteration, update the horizontal
           position and reset the alpha value; we switch from the left side
           to the right side */
        if (index == 510)
        {
            horizontalPosition = 1099.f; // 480 + 620 - 1
            effectColor.a = 255;
        }

        /* the alpha value of the color is decremented each time we create two
           lines of the gradient surface */
        if (index % 2 == 0)
        {
            /* update the alpha value */
            effectColor.a--;
        }

        /* append the new created rectangle inside the container used for the
           the gradient effect creation */
        sidesLines.push_back(rectangle);
    }
}

}
}
