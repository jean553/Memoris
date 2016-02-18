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
 * Policy for menu selector animation
 *
 * @file HasMenuSelectorAnimation.hpp
 * @brief policy for menu selector animation
 * @package policies
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_HAS_MENU_SELECTOR_ANIMATION
#define DEF_HAS_MENU_SELECTOR_ANIMATION

#include <SFML/Graphics.hpp>

namespace policies {
class HasMenuSelectorAnimation {

public:

    static const sf::Uint8 MAXIMUM_RED_COLOR_AMOUNT;
    static const sf::Uint8 MINIMUM_RED_COLOR_AMOUNT;
    static const sf::Uint8 SELECTOR_COLOR_INCREMENTATION_STEP;
    static const sf::Int32 INTERVAL_ANIMATION;

    static sf::Clock clock;

    /**
     * @brief animate the selector of the given menu
     */
    template<typename T>
    static void animateMenuSelector(T* pMenuController);
};
}

#endif
