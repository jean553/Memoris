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
 * @file SprtTransition.cpp
 * @brief horizontal translation of a sprite
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SprtTransition.hpp"
#include "Colors.hpp"

using namespace utils;

const uint8_t SprtTransition::INTERVAL = 10;

const float_t SprtTransition::HRTL_INTERVAL = 10.f;

/**
 *
 */
SprtTransition::SprtTransition(
    const float_t& hrtlPstnRef,
    const float_t& vrtlPstnRef,
    const float_t& hrtlSizeRef
) : oriHrtlPstn(hrtlPstnRef)
{

    hrtlPstn = hrtlPstnRef;
    vrtlPstn = vrtlPstnRef;
    hrtlSize = hrtlSizeRef;

    drct = 1;
}

/**
 *
 */
void SprtTransition::display(
    utils::Context& context,
    sf::Sprite& sprt,
    const bool& animate
)
{
    context.getSfmlWindow().draw(sprt);

    if (!animate)
    {
        sprt.setPosition(
            oriHrtlPstn,
            vrtlPstn
        );

        sprt.setColor(
            sf::Color(
                constants::Colors::COLOR_WHITE_RED,
                constants::Colors::COLOR_WHITE_GREEN,
                constants::Colors::COLOR_WHITE_BLUE,
                constants::Colors::COLOR_ALPHA_PARTIAL
            )
        );
    }

    if (
        clk.getElapsedTime().asMilliseconds() < INTERVAL ||
        !animate
    )
    {
        return;
    }

    sprt.setColor(
        sf::Color(
            constants::Colors::COLOR_WHITE_RED,
            constants::Colors::COLOR_WHITE_GREEN,
            constants::Colors::COLOR_WHITE_BLUE,
            constants::Colors::COLOR_ALPHA_FULL
        )
    );

    hrtlPstn += HRTL_INTERVAL * drct;

    sprt.setPosition(
        hrtlPstn,
        vrtlPstn
    );

    if (
        hrtlPstn > oriHrtlPstn + hrtlSize ||
        hrtlPstn < oriHrtlPstn - hrtlSize
    )
    {
        drct *= -1;
    }

    clk.restart();
}
