/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @file AbstractMirrorAnimation.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "AbstractMirrorAnimation.hpp"

#include "Level.hpp"
#include "Cell.hpp"

#include <SFML/Config.hpp>

namespace memoris
{
namespace animations
{

constexpr sf::Uint32 ANIMATION_STEPS_INTERVAL {50};

class AbstractMirrorAnimation::Impl
{

public:

    sf::Uint8 animatedSideTransparency {255};
};

/**
 *
 */
AbstractMirrorAnimation::AbstractMirrorAnimation() :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
AbstractMirrorAnimation::~AbstractMirrorAnimation() noexcept = default;

/**
 *
 */
void AbstractMirrorAnimation::increaseTransparency() & noexcept
{
    impl->animatedSideTransparency += TRANSPARENCY_INTERVAL;
}

/**
 *
 */
void AbstractMirrorAnimation::decreaseTransparency() & noexcept
{
    impl->animatedSideTransparency -= TRANSPARENCY_INTERVAL;
}

/**
 *
 */
void AbstractMirrorAnimation::setFullTransparent() & noexcept
{
    impl->animatedSideTransparency = 0.f;
}

/**
 *
 */
void AbstractMirrorAnimation::setNoTransparent() & noexcept
{
    impl->animatedSideTransparency = MAXIMUM_TRANSPARENCY;
}

/**
 *
 */
void AbstractMirrorAnimation::applyTransparencyOnOneCell(
    const utils::Context& context,
    const Level& level,
    const unsigned short& index
) const &
{
    level->getCells()[index]->setCellColorTransparency(
        context,
        impl->animatedSideTransparency
    );
}

}
}
