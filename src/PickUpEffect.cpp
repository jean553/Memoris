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
 * @file PickUpEffect.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PickUpEffect.hpp"

#include "Context.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace utils
{

class PickUpEffect::Impl
{

public:

    Impl(
        const sf::Texture& texture,
        const float& horizontalPosition,
        const float& verticalPosition
    )
    {
        sprite.setTexture(texture);
        sprite.setPosition(
            horizontalPosition,
            verticalPosition
        );
    }

    sf::Sprite sprite;

    sf::Uint32 animationLastUpdateTime {0};

    sf::Uint8 alpha {255};
};

/**
 *
 */
PickUpEffect::PickUpEffect(
    const sf::Texture& texture,
    const float& horizontalPosition,
    const float& verticalPosition
) :
    impl(
        std::make_unique<Impl>(
            texture,
            horizontalPosition,
            verticalPosition
        )
    )
{
}

/**
 *
 */
PickUpEffect::~PickUpEffect() = default;

/**
 *
 */
void PickUpEffect::render(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->sprite);

    constexpr sf::Uint32 ANIMATION_INTERVAL {50};
    if (
        context.getClockMillisecondsTime() -
        impl->animationLastUpdateTime < ANIMATION_INTERVAL
    )
    {
        return;
    }

    constexpr float MOVEMENT_STEP {-1.f};
    impl->sprite.move(
        MOVEMENT_STEP,
        MOVEMENT_STEP
    );

    constexpr float SCALE_STEP {1.05f};
    impl->sprite.scale(
        SCALE_STEP,
        SCALE_STEP
    );

    impl->sprite.setColor(
        sf::Color(
            255,
            255,
            255,
            impl->alpha
        )
    );

    constexpr sf::Uint8 ALPHA_STEP {17};
    impl->alpha -= ALPHA_STEP;

    impl->animationLastUpdateTime = context.getClockMillisecondsTime();
}

/**
 *
 */
const bool PickUpEffect::isFinished() const & noexcept
{
    return !impl->alpha;
}

}
}
