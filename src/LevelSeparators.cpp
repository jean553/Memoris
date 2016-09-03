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
 * @file LevelSeparators.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "LevelSeparators.hpp"

#include "window.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
LevelSeparators::LevelSeparators(
    const std::shared_ptr<utils::Context>& context
)
{
    left.setSize(
        sf::Vector2f(
            1,
            window::HEIGHT
        )
    );
    right.setSize(
        sf::Vector2f(
            1,
            window::HEIGHT
        )
    );

    left.setPosition(
        290.f,
        0.f
    );
    right.setPosition(
        1308.f,
        0.f
    );

    left.setFillColor(context->getColorsManager().getColorWhite());
    right.setFillColor(context->getColorsManager().getColorWhite());
}

/**
 *
 */
void LevelSeparators::display(
    const std::shared_ptr<utils::Context>& context
) const
{
    context->getSfmlWindow().draw(left);
    context->getSfmlWindow().draw(right);
}

}
}
