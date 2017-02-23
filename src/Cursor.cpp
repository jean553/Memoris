/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

    Impl(const utils::Context& context)
    {
        sprite.setTexture(context.getTexturesManager().getCursorTexture());
    }

    sf::Sprite sprite;

    sf::Uint32 lastCursorPositionUpdateTime {0};

    sf::Vector2<float> position;
};

/**
 *
 */
Cursor::Cursor(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    /* we force the position of the cursor surface during the initialization;
       the surface is visually directly at the same position as the real
       cursor one */
    updateCursorPosition();
}

/**
 *
 */
Cursor::~Cursor() noexcept = default;

/**
 *
 */
void Cursor::render(const utils::Context& context)
{
    auto& sprite = impl->sprite;

    context.getSfmlWindow().draw(sprite);

    const auto& currentTime = context.getClockMillisecondsTime();
    auto& lastCursorPositionUpdateTime = impl->lastCursorPositionUpdateTime;

    if (currentTime - lastCursorPositionUpdateTime < 30)
    {
        return;
    }

    updateCursorPosition();

    lastCursorPositionUpdateTime = currentTime;
}

/**
 *
 */
void Cursor::updateCursorPosition() const &
{
    const auto positionIntegers = sf::Mouse::getPosition();

    auto& positionFloats = impl->position;
    positionFloats = sf::Vector2<float>(
        static_cast<float>(positionIntegers.x),
        static_cast<float>(positionIntegers.y)
    );

    impl->sprite.setPosition(positionFloats);
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
