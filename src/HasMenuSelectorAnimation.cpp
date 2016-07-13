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
 * @file HasMenuSelectorAnimation.cpp
 * @brief policy for menu selector animation
 * @package policies
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "HasMenuSelectorAnimation.hpp"
#include "MainMenuController.hpp"
#include "EditorMenuController.hpp"
#include "SerieMainMenuController.hpp"

using namespace memoris;
using namespace policies;

const sf::Uint8 HasMenuSelectorAnimation::MAXIMUM_RED_COLOR_AMOUNT = 255;
const sf::Uint8 HasMenuSelectorAnimation::MINIMUM_RED_COLOR_AMOUNT = 0;
const sf::Uint8 HasMenuSelectorAnimation::SELECTOR_COLOR_INCREMENTATION_STEP = 15;
const sf::Int32 HasMenuSelectorAnimation::INTERVAL_ANIMATION = 10;

sf::Clock HasMenuSelectorAnimation::clock;

template<typename T>
void HasMenuSelectorAnimation::animateMenuSelector(T* pMenuController)
{
    if(clock.getElapsedTime().asMilliseconds() <= INTERVAL_ANIMATION)
    {
        return;
    }

    /* TODO: operation between a short and an Uint8 type,
       should have an adapted cast somewhere I guess... */
    pMenuController->colorSelector.g +=
        SELECTOR_COLOR_INCREMENTATION_STEP * pMenuController->selectorDirection;
    pMenuController->colorSelector.b +=
        SELECTOR_COLOR_INCREMENTATION_STEP * pMenuController->selectorDirection;

    if (
        pMenuController->colorSelector.g == MINIMUM_RED_COLOR_AMOUNT ||
        pMenuController->colorSelector.g == MAXIMUM_RED_COLOR_AMOUNT
    )
    {
        pMenuController->selectorDirection *= -1;
    }

    clock.restart();
}

template void HasMenuSelectorAnimation::animateMenuSelector<controllers::EditorMenuController>(controllers::EditorMenuController* pMenuController);
