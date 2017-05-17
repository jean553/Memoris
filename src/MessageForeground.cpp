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
 * @file MessageForeground.cpp
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MessageForeground.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts_sizes.hpp"
#include "window.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace foregrounds
{

class MessageForeground::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::string&& message
    )
    {
        explanation.setFont(context.getFontsManager().getTextFont());
        explanation.setString(message);
        explanation.setCharacterSize(memoris::sizes::TEXT_SIZE);
        explanation.setFillColor(context.getColorsManager().getColorWhite());

        constexpr float EXPLANATION_VERTICAL_POSITION {380.f};
        explanation.setPosition(
            window::getCenteredTextHorizontalPosition(explanation),
            EXPLANATION_VERTICAL_POSITION
        );
    }

    sf::Text explanation;
};

/**
 *
 */
MessageForeground::MessageForeground(
    const utils::Context& context,
    const std::string&& message
) :
    AbstractForeground(context.getSfmlWindow()),
    impl(
        std::make_unique<Impl>(
            context,
            std::move(message)
        )
    )
{
}

/**
 *
 */
MessageForeground::~MessageForeground() = default;

/**
 *
 */
void MessageForeground::render() const &
{
    getWindow().draw(impl->explanation);
}

}
}
