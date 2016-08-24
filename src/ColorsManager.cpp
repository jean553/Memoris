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
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ColorsManager.hpp"

namespace memoris
{
namespace colors
{

/**
 *
 */
ColorsManager::ColorsManager()
{
    colorWhite.r = COLOR_WHITE_RED;
    colorWhite.g = COLOR_WHITE_GREEN;
    colorWhite.b = COLOR_WHITE_BLUE;
    colorWhite.a = COLOR_FULL_ALPHA;

    colorBlue.r = COLOR_BLUE_RED;
    colorBlue.g = COLOR_BLUE_GREEN;
    colorBlue.b = COLOR_BLUE_BLUE;
    colorBlue.a = COLOR_FULL_ALPHA;

    colorRed.r = COLOR_RED_RED;
    colorRed.g = COLOR_RED_GREEN;
    colorRed.b = COLOR_RED_BLUE;
    colorRed.a = COLOR_FULL_ALPHA;

    colorLightBlue.r = COLOR_LIGHT_BLUE_RED;
    colorLightBlue.g = COLOR_LIGHT_BLUE_GREEN;
    colorLightBlue.b = COLOR_LIGHT_BLUE_BLUE;
    colorLightBlue.a = COLOR_FULL_ALPHA;

    colorPartialDarkGrey.r = COLOR_DARK_GREY_RED;
    colorPartialDarkGrey.g = COLOR_DARK_GREY_GREEN;
    colorPartialDarkGrey.b = COLOR_DARK_GREY_BLUE;
    colorPartialDarkGrey.a = COLOR_PARTIAL_ALPHA;

    colorBlack.r = COLOR_BLACK_RED;
    colorBlack.g = COLOR_BLACK_GREEN;
    colorBlack.b = COLOR_BLACK_BLUE;
    colorBlack.a = COLOR_FULL_ALPHA;

    colorGreen.r = COLOR_GREEN_RED;
    colorGreen.g = COLOR_GREEN_GREEN;
    colorGreen.b = COLOR_GREEN_BLUE;
    colorGreen.a = COLOR_FULL_ALPHA;

    colorDarkGreen.r = COLOR_DARK_GREEN_RED;
    colorDarkGreen.g = COLOR_DARK_GREEN_GREEN;
    colorDarkGreen.b = COLOR_DARK_GREEN_BLUE;
    colorDarkGreen.a = COLOR_FULL_ALPHA;

    colorPurpleLowAlpha.r = COLOR_PURPLE_RED;
    colorPurpleLowAlpha.g = COLOR_PURPLE_GREEN;
    colorPurpleLowAlpha.b = COLOR_PURPLE_BLUE;
    colorPurpleLowAlpha.a = COLOR_PARTIAL_ALPHA;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorWhite() const
{
    return colorWhite;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorLightBlue() const
{
    return colorLightBlue;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorRed() const
{
    return colorRed;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorBlack() const
{
    return colorBlack;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorPartialDarkGrey() const
{
    return colorPartialDarkGrey;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorGreen() const
{
    return colorGreen;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorDarkGreen() const
{
    return colorDarkGreen;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorPurpleLowAlpha() const
{
    return colorPurpleLowAlpha;
}

/**
 *
 */
sf::Color ColorsManager::getColorBlueCopy() const
{
    return colorBlue;
}

/**
 *
 */
sf::Color ColorsManager::getColorRedCopy() const
{
    return colorRed;
}

/**
 *
 */
sf::Color ColorsManager::getColorWhiteCopy() const
{
    return colorWhite;
}

/**
 *
 */
sf::Color ColorsManager::getColorBlackCopy() const
{
    return colorBlack;
}

}
}
