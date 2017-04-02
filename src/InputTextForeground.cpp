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
 * @file InputTextForeground.hpp
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "InputTextForeground.hpp"

#include "InputTextWidget.hpp"
#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"
#include "window.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace foregrounds
{

class InputTextForeground::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::string&& message
    ) : inputTextLevelName(context)
    {
        explanation.setFont(context.getFontsManager().getTextFont());
        explanation.setString(message);
        explanation.setCharacterSize(memoris::fonts::TEXT_SIZE);
        explanation.setFillColor(context.getColorsManager().getColorWhite());
        explanation.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(explanation),
            300.f
        );
    }

    widgets::InputTextWidget inputTextLevelName;

    sf::Text explanation;
};

/**
 *
 */
InputTextForeground::InputTextForeground(
    const utils::Context& context,
    const std::string&& message
) :
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
InputTextForeground::~InputTextForeground() noexcept = default;

/**
 *
 */
void InputTextForeground::render(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->explanation);

    impl->inputTextLevelName.display();
}

/**
 *
 */
widgets::InputTextWidget& InputTextForeground::getInputTextWidget() const &
    noexcept
{
    return impl->inputTextLevelName;
}

}
}
