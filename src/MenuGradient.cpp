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
 * @brief menu gradient behing the selectors
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MenuGradient.hpp"

#include "window.hpp"

using namespace utils;
using namespace memoris;

const float MenuGradient::MAIN_SURFACE_WIDTH = 620.f;
const float MenuGradient::MAIN_SURFACE_HRTL_PSTN = 480.f;

const uint16_t MenuGradient::SIDE_RECTANGLES_AMNT = 510;

/**
 *
 */
MenuGradient::MenuGradient(utils::Context& context)
{
    /* the height is the screen height,
     * the width is less than the window width */
    main.setSize(
        sf::Vector2f(
            MAIN_SURFACE_WIDTH,
            window::HEIGHT
        )
    );

    main.setPosition(MAIN_SURFACE_HRTL_PSTN, 0);

    main.setFillColor(context.getColorsManager().getColorBlack());

    initializeGradientRectangles(context);
}

/**
 *
 */
void MenuGradient::display(utils::Context& context)
{
    context.getSfmlWindow().draw(main);

    /* display the left gradient */
    for (
        std::vector<sf::RectangleShape>::iterator rtgl = leftRtgls.begin();
        rtgl != leftRtgls.end();
        ++rtgl
    )
    {
        context.getSfmlWindow().draw(*rtgl);
    }

    /* display the right gradient */
    for (
        std::vector<sf::RectangleShape>::iterator rtgl = rightRtgls.begin();
        rtgl != rightRtgls.end();
        ++rtgl
    )
    {
        context.getSfmlWindow().draw(*rtgl);
    }
}

/**
 *
 */
void MenuGradient::initializeGradientRectangles(utils::Context& context)
{
    float hrtlPstn = MAIN_SURFACE_HRTL_PSTN - 1.f;

    sf::Color effectColor = context.getColorsManager().getColorBlackCopy();
    sf::Uint8 alpha = 255;

    /* initialize the left rectangles */
    for (uint16_t i = SIDE_RECTANGLES_AMNT; i > 0; i--)
    {
        sf::RectangleShape rtgl;

        rtgl.setPosition(
            hrtlPstn,
            0
        );

        rtgl.setSize(
            sf::Vector2f(
                1,
                window::HEIGHT
            )
        );

        rtgl.setFillColor(effectColor);

        hrtlPstn--;
        if (i % 2 == 0)
        {
            alpha--;
        }
        effectColor.a = alpha;

        leftRtgls.push_back(rtgl);
    }

    /* the origin is on the right side of the main rectangle */
    hrtlPstn = MAIN_SURFACE_HRTL_PSTN + MAIN_SURFACE_WIDTH - 1.f;
    alpha = 255;

    /* initialize the right rectangles */
    /* TODO: can be refactored with the previous one... */
    for (uint16_t i = SIDE_RECTANGLES_AMNT; i > 0; i--)
    {
        sf::RectangleShape rtgl;

        rtgl.setPosition(
            hrtlPstn,
            0
        );

        rtgl.setSize(
            sf::Vector2f(
                1,
                window::HEIGHT
            )
        );

        rtgl.setFillColor(effectColor);

        hrtlPstn++;
        if (i % 2 == 0)
        {
            alpha--;
        }
        effectColor.a = alpha;

        rightRtgls.push_back(rtgl);
    }
}
