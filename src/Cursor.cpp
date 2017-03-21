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
 * @file Cursor.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Cursor.hpp"

#include "TexturesManager.hpp"
#include "Context.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace widgets
{

class Cursor::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
    {
        sprite.setTexture(context.getTexturesManager().getCursorTexture());
    }

    sf::Sprite sprite;

    sf::Uint32 lastUpdateTime {0};

    sf::Vector2<float> position;

    const utils::Context& context;
};

/**
 *
 */
Cursor::Cursor(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
Cursor::~Cursor() = default;

/**
 *
 */
void Cursor::render() const &
{
    const auto& context = impl->context;

    context.getSfmlWindow().draw(impl->sprite);

    const auto& currentTime = context.getClockMillisecondsTime();
    auto& lastUpdateTime = impl->lastUpdateTime;

    constexpr sf::Uint32 CURSOR_UPDATE_POSITION_INTERVAL {30};
    if (currentTime - lastUpdateTime < CURSOR_UPDATE_POSITION_INTERVAL)
    {
        return;
    }

    const auto positionIntegers = sf::Mouse::getPosition();
    auto& positionFloats = impl->position;

    /* we get integers and store floats because all surfaces and texts
       positions manipulations are done with floats */
    positionFloats = sf::Vector2<float>(
        static_cast<float>(positionIntegers.x),
        static_cast<float>(positionIntegers.y)
    );

    impl->sprite.setPosition(positionFloats);

    lastUpdateTime = currentTime;
}

/**
 *
 */
const sf::Vector2<float>& Cursor::getPosition() const & noexcept
{
    return impl->position;
}

}
}
