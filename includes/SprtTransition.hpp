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
 * @file SprtTransition.hpp
 * @brief horizontal translation of a sprite
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SPRT_TRANSLATION
#define DEF_SPRT_TRANSLATION

#include <SFML/Graphics.hpp>

#include "Context.hpp"

namespace utils
{
class SprtTransition
{
public:

    SprtTransition(
        const float& hrtlPstnRef,
        const float& vrtlPstnRef,
        const float& hrtlSizeRef
    );

    /**
     * @brief displays the sprite translation
     *
     * @param context context pointer
     * @param sprt sprite to display
     */
    void display(
        utils::Context& context,
        sf::Sprite& sprt,
        const bool& animate
    );

private:

    static const uint8_t INTERVAL;
    static const float HRTL_INTERVAL;

    sf::Clock clk;

    float hrtlPstn;
    float vrtlPstn;
    float hrtlSize;

    const float oriHrtlPstn;

    int8_t drct;
};
}

#endif
