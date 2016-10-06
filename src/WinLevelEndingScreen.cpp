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
 * @file WinLevelEndingScreen.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WinLevelEndingScreen.hpp"

#include "fonts.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace utils
{

class WinLevelEndingScreen::Impl
{

public:

    Impl(const Context& context)
    {
        leftLevelsAmount.setPosition(
            700.f,
            200.f
        );
        leftLevelsAmount.setString(
            std::to_string(
                context.getPlayingSerieManager().getRemainingLevelsAmount()
            )
        );
        leftLevelsAmount.setCharacterSize(fonts::LEVELS_COUNTDOWN_SIZE);
        leftLevelsAmount.setFont(
            context.getFontsManager().getTextFont()
        );
        leftLevelsAmount.setColor(
            context.getColorsManager().getColorWhite()
        );

        leftLevelsSuffix.setPosition(
            560.f,
            650.f
        );
        leftLevelsSuffix.setString("levels left");
        leftLevelsSuffix.setCharacterSize(fonts::SUB_TITLE_SIZE);
        leftLevelsSuffix.setFont(context.getFontsManager().getTextFont());
        leftLevelsSuffix.setColor(
            context.getColorsManager().getColorDarkGreen()
        );
    }

    sf::Text leftLevelsSuffix;
    sf::Text leftLevelsAmount;

    sf::Uint32 lastAnimationUpdateTime {0};

    sf::Uint8 leftLevelsAmountTransparency {255};

    /* 17 because this is the increment/decrement step of transparency to
       create the flashing animation ( 255 / 5 = 17 ) */
    sf::Int8 leftLevelsAmountDirection {-17};
};

/**
 *
 */
WinLevelEndingScreen::WinLevelEndingScreen(const Context& context) :
    LevelEndingScreen(context),
    impl(std::make_unique<Impl>(context))
{
    text.setPosition(
        480.f,
        150.f
    );
    text.setString("You Win !");
    text.setColor(context.getColorsManager().getColorGreen());
}

/**
 *
 */
WinLevelEndingScreen::~WinLevelEndingScreen() noexcept = default;

/**
 *
 */
void WinLevelEndingScreen::render(const Context& context) &
{
    /* already done in the derivated function, but we want add aditional
       actions for this class */
    context.getSfmlWindow().draw(filter);
    context.getSfmlWindow().draw(text);

    context.getSfmlWindow().draw(impl->leftLevelsSuffix);

    animateLeftLevelsAmount(context);
}

/**
 *
 */
void WinLevelEndingScreen::animateLeftLevelsAmount(const Context& context) &
{
    context.getSfmlWindow().draw(impl->leftLevelsAmount);

    if (
        context.getClockMillisecondsTime() -
        impl->lastAnimationUpdateTime < 50
    )
    {
        return;
    }

    impl->leftLevelsAmountTransparency += impl->leftLevelsAmountDirection;

    if (
        impl->leftLevelsAmountTransparency == 0 ||
        impl->leftLevelsAmountTransparency == 255
    )
    {
        impl->leftLevelsAmountDirection *= -1;
    }

    sf::Color color = context.getColorsManager().getColorWhiteCopy();

    color.a = impl->leftLevelsAmountTransparency;

    impl->leftLevelsAmount.setColor(color);

    impl->lastAnimationUpdateTime = context.getClockMillisecondsTime();
}

}
}
