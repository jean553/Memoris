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
 * @file PickUpEffect.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "PickUpEffect.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace memoris
{
namespace utils
{

class PickUpEffect::Impl
{

public:

    Impl(
        const sf::Texture& texture,
        const float& hPosition,
        const float& vPosition
    )
    {
        sprite.setTexture(texture);
        sprite.setPosition(
            hPosition,
            vPosition
        );
    }

    sf::Sprite sprite;

    sf::Uint32 animationLastUpdateTime {0};

    float size {1.f};
    float positionOffset {0.f};
};

/**
 *
 */
PickUpEffect::PickUpEffect(
    const sf::Texture& texture,
    const float& hPosition,
    const float& vPosition
) :
    impl(
        std::make_unique<Impl>(
            texture,
            hPosition,
            vPosition
        )
    )
{
}

}
}
