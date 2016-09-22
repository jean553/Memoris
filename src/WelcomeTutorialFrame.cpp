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
 * @file WelcomeTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WelcomeTutorialFrame.hpp"

#include "fonts.hpp"
#include "Context.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace widgets
{

class WelcomeTutorialFrame::Impl
{

public:

    Impl(utils::Context& context)
    {
        title.setString("Welcome in Memoris !");
        title.setCharacterSize(fonts::INFORMATION_SIZE);
        title.setFont(context.getFontsManager().getTextFont());
        title.setColor(context.getColorsManager().getColorWhite());
        title.setPosition(
            20.f,
            110.f
        );
    }

    sf::Text title;
};

/**
 *
 */
WelcomeTutorialFrame::WelcomeTutorialFrame(utils::Context& context) :
    TutorialFrame(
        100.f,
        400.f,
        200.f
    ),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
WelcomeTutorialFrame::~WelcomeTutorialFrame() noexcept = default;

/**
 *
 */
void WelcomeTutorialFrame::render(utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->title);
}

}
}
