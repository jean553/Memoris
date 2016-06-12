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
 * @file MenuGradient.hpp
 * @brief menu gradient behing the selectors
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_MENU_GRADIENT
#define DEF_MENU_GRADIENT

#include <SFML/Graphics.hpp>
#include <vector>

#include "Context.hpp"

namespace utils
{
class MenuGradient
{
public:

    MenuGradient();

    /**
     * @brief display the gradient area
     *
     * @param context pointer to the current context
     */
    void display(utils::Context& context);

private:

    static const float_t MAIN_SURFACE_WIDTH;
    static const float_t MAIN_SURFACE_HRTL_PSTN;

    static const uint16_t SIDE_RECTANGLES_AMNT;

    /**
     * @brief initialize gradient rectangles
     */
    void initializeGradientRectangles();

    sf::Color gradientColor;

    sf::RectangleShape main;

    std::vector<sf::RectangleShape> leftRtgls;
    std::vector<sf::RectangleShape> rightRtgls;
};
}

#endif
