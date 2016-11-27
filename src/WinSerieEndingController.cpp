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
 * @file WinSerieEndingController.hpp
 * @brief the wining screen that is displayed when the user wins the serie
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WinSerieEndingController.hpp"

#include "Context.hpp"
#include "controllers.hpp"
#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"
#include "AnimatedBackground.hpp"
#include "HorizontalGradient.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class WinSerieEndingController::Impl
{

public:

    Impl(const utils::Context& context) :
        background(context),
        gradient(context)
    {
        title.setString("Serie finished !");
        title.setCharacterSize(fonts::TITLE_SIZE);
        title.setFont(context.getFontsManager().getTextFont());
        title.setColor(context.getColorsManager().getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        time.setString("00 : 00 : 00");
        time.setCharacterSize(fonts::TITLE_SIZE);
        time.setFont(context.getFontsManager().getTextFont());
        time.setColor(context.getColorsManager().getColorWhite());
        time.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(time),
            TIME_VERTICAL_POSITION
        );
    }

    sf::Text title;
    sf::Text time;

    utils::AnimatedBackground background;

    others::HorizontalGradient gradient;
};

/**
 *
 */
WinSerieEndingController::WinSerieEndingController(
    const utils::Context& context
) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
WinSerieEndingController::~WinSerieEndingController() noexcept = default;

/**
 *
 */
const unsigned short& WinSerieEndingController::render(
    const utils::Context& context
) &
{
    impl->background.render(context);
    impl->gradient.render(context);

    context.getSfmlWindow().draw(impl->title);
    context.getSfmlWindow().draw(impl->time);

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
            }
            }
        }
        default:
        {
        }
        }
    }

    return nextControllerId;
}

}
}
