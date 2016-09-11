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
 * @file ColorsManager.cpp
 * @package colors
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ColorsManager.hpp"

namespace memoris
{
namespace managers
{

/**
 *
 */
const sf::Color& ColorsManager::getColorWhite() const noexcept
{
    return colorWhite;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorLightBlue() const noexcept
{
    return colorLightBlue;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorRed() const noexcept
{
    return colorRed;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorBlack() const noexcept
{
    return colorBlack;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorPartialDarkGrey() const noexcept
{
    return colorPartialDarkGrey;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorGreen() const noexcept
{
    return colorGreen;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorDarkGreen() const noexcept
{
    return colorDarkGreen;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorPurpleLowAlpha() const noexcept
{
    return colorPurpleLowAlpha;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorDarkGrey() const noexcept
{
    return colorDarkGrey;
}

/**
 *
 */
sf::Color ColorsManager::getColorBlueCopy() const noexcept
{
    return colorBlue;
}

/**
 *
 */
sf::Color ColorsManager::getColorRedCopy() const noexcept
{
    return colorRed;
}

/**
 *
 */
sf::Color ColorsManager::getColorWhiteCopy() const noexcept
{
    return colorWhite;
}

/**
 *
 */
sf::Color ColorsManager::getColorBlackCopy() const noexcept
{
    return colorBlack;
}

}
}
