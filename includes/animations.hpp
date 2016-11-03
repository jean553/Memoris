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
 * @file animations.hpp
 * @brief factory method for the animations objects
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ANIMATIONS_H_
#define MEMORIS_ANIMATIONS_H_

#include "LevelAnimation.hpp"

#include <memory>

namespace memoris
{
namespace animations
{

/**
 * @brief level animation factory; creates the animation objects, creates a
 * unique pointer to them and returns this pointer; we use unique pointer
 * because all the animations have the same parent type with the same
 * attributes and methods; we create and destroy these animations dynamlically
 * during the game; unique pointer is restrictive and adapted in our case
 *
 * @param context reference to the current context to use
 * @param cellType the animation is returned according to the cell type; some
 * cells starts animation, this function directly returns the animation
 * according to the given type
 *
 * @return std::unique_ptr<LevelAnimation>
 */
std::unique_ptr<LevelAnimation> getAnimationByCellType(
    const utils::Context& context,
    const char& cellType
);

}
}

#endif
