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
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ColorsManager.hpp"

#include <SFML/Graphics/Color.hpp>

namespace memoris
{
namespace managers
{

class ColorsManager::Impl
{

public:

    const sf::Color colorWhite
    {
        255,
        255,
        255,
        255
    };

    const sf::Color colorBlue
    {
        0,
        0,
        255,
        255
    };

    const sf::Color colorRed
    {
        255,
        0,
        0,
        255
    };

    const sf::Color colorLightBlue
    {
        105,
        125,
        255,
        255
    };

    const sf::Color colorBlack
    {
        0,
        0,
        0,
        255
    };

    const sf::Color colorPartialDarkGrey
    {
        50,
        50,
        50,
        225
    };

    const sf::Color colorGreen
    {
        0,
        192,
        0,
        255
    };

    const sf::Color colorDarkGreen
    {
        0,
        100,
        0,
        255
    };

    const sf::Color colorPurpleLowAlpha
    {
        255,
        0,
        255,
        75
    };

    const sf::Color colorDarkGrey
    {
        50,
        50,
        50,
        255
    };

    const sf::Color colorBlueLowAlpha
    {
        0,
        17,
        97,
        200
    };
};

/**
 *
 */
ColorsManager::ColorsManager() noexcept :
impl(std::make_unique<Impl>())
{
}

/**
 *
 */
ColorsManager::~ColorsManager() noexcept = default;

/**
 *
 */
const sf::Color& ColorsManager::getColorWhite() const & noexcept
{
    return impl->colorWhite;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorLightBlue() const & noexcept
{
    return impl->colorLightBlue;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorBlue() const & noexcept
{
    return impl->colorBlue;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorRed() const & noexcept
{
    return impl->colorRed;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorBlack() const & noexcept
{
    return impl->colorBlack;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorPartialDarkGrey() const & noexcept
{
    return impl->colorPartialDarkGrey;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorGreen() const & noexcept
{
    return impl->colorGreen;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorDarkGreen() const & noexcept
{
    return impl->colorDarkGreen;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorPurpleLowAlpha() const & noexcept
{
    return impl->colorPurpleLowAlpha;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorDarkGrey() const & noexcept
{
    return impl->colorDarkGrey;
}

/**
 *
 */
const sf::Color& ColorsManager::getColorBlueLowAlpha() const & noexcept
{
    return impl->colorBlueLowAlpha;
}

/**
 *
 */
sf::Color ColorsManager::getColorBlueCopy() const & noexcept
{
    return impl->colorBlue;
}

/**
 *
 */
sf::Color ColorsManager::getColorRedCopy() const & noexcept
{
    return impl->colorRed;
}

/**
 *
 */
sf::Color ColorsManager::getColorWhiteCopy() const & noexcept
{
    return impl->colorWhite;
}

/**
 *
 */
sf::Color ColorsManager::getColorBlackCopy() const & noexcept
{
    return impl->colorBlack;
}

}
}
