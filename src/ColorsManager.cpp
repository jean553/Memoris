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

    colorGrey.r = COLOR_GREY_RED;
    colorGrey.g = COLOR_GREY_GREEN;
    colorGrey.b = COLOR_GREY_BLUE;
    colorGrey.a = COLOR_FULL_ALPHA;

    colorPartialGrey.r = COLOR_GREY_RED;
    colorPartialGrey.g = COLOR_GREY_GREEN;
    colorPartialGrey.b = COLOR_GREY_BLUE;
    colorPartialGrey.a = COLOR_PARTIAL_ALPHA;

    colorPartialWhite.r = COLOR_WHITE_RED;
    colorPartialWhite.g = COLOR_WHITE_GREEN;
    colorPartialWhite.b = COLOR_WHITE_BLUE;
    colorPartialWhite.a = COLOR_PARTIAL_ALPHA;

    colorDarkGrey.r = COLOR_DARK_GREY_RED;
    colorDarkGrey.g = COLOR_DARK_GREY_GREEN;
    colorDarkGrey.b = COLOR_DARK_GREY_BLUE;
    colorDarkGrey.a = COLOR_FULL_ALPHA;

    colorOrange.r = COLOR_ORANGE_RED;
    colorOrange.g = COLOR_ORANGE_GREEN;
    colorOrange.b = COLOR_ORANGE_BLUE;
    colorOrange.a = COLOR_FULL_ALPHA;
}

/**
 *
 */
sf::Color& ColorsManager::getColorWhite()
{
    return colorWhite;
}

/**
 *
 */
sf::Color& ColorsManager::getColorLightBlue()
{
    return colorLightBlue;
}

/**
 *
 */
sf::Color& ColorsManager::getColorRed()
{
    return colorRed;
}

/**
 *
 */
sf::Color& ColorsManager::getColorGrey()
{
    return colorGrey;
}

/**
 *
 */
sf::Color& ColorsManager::getColorPartialWhite()
{
    return colorPartialWhite;
}

/**
 *
 */
sf::Color& ColorsManager::getColorPartialGrey()
{
    return colorPartialGrey;
}

/**
 *
 */
sf::Color& ColorsManager::getColorDarkGrey()
{
    return colorDarkGrey;
}

/**
 *
 */
sf::Color& ColorsManager::getColorOrange()
{
    return colorOrange;
}

/**
 *
 */
sf::Color& ColorsManager::getColorBlack()
{
    return colorBlack;
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
