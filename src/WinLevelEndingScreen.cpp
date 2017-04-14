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
 * @file WinLevelEndingScreen.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WinLevelEndingScreen.hpp"

#include "fonts_sizes.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "window.hpp"

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
        leftLevelsAmount.setString(
            std::to_string(
                context.getPlayingSerieManager().getRemainingLevelsAmount()
            )
        );
        leftLevelsAmount.setCharacterSize(sizes::LEVELS_COUNTDOWN_SIZE);
        leftLevelsAmount.setFont(
            context.getFontsManager().getTextFont()
        );
        leftLevelsAmount.setFillColor(
            context.getColorsManager().getColorWhite()
        );
        leftLevelsAmount.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(leftLevelsAmount),
            LEFT_LEVELS_LABEL_VERTICAL_POSITION
        );

        leftLevelsSuffix.setString("levels left");
        leftLevelsSuffix.setCharacterSize(sizes::SUB_TITLE_SIZE);
        leftLevelsSuffix.setFont(context.getFontsManager().getTextFont());
        leftLevelsSuffix.setFillColor(
            context.getColorsManager().getColorWhite()
        );
        leftLevelsSuffix.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(leftLevelsSuffix),
            LEFT_LEVELS_SUFFIX_VERTICAL_POSITION
        );
    }

    sf::Text leftLevelsSuffix;
    sf::Text leftLevelsAmount;

    sf::Uint32 lastAnimationUpdateTime {0};

    sf::Uint8 leftLevelsAmountTransparency {255};

    sf::Int8 leftLevelsAmountDirection {-17}; // (17 steps) 255 / 15 = 17
};

/**
 *
 */
WinLevelEndingScreen::WinLevelEndingScreen(const Context& context) :
    LevelEndingScreen(context),
    impl(std::make_unique<Impl>(context))
{
    text.setString("You Win !");
    text.setFillColor(context.getColorsManager().getColorGreen());

    /* the position is not set in the parent controller because we need to
       know the surface width before setting the horizontal position */

    text.setPosition(
        window::getCenteredSfmlSurfaceHorizontalPosition(text),
        LEFT_LEVELS_PREFIX_VERTICAL_POSITION
    );
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
        impl->lastAnimationUpdateTime < ANIMATION_INTERVAL
    )
    {
        return;
    }

    impl->leftLevelsAmountTransparency += impl->leftLevelsAmountDirection;

    if (
        impl->leftLevelsAmountTransparency == 0 ||
        impl->leftLevelsAmountTransparency == MAXIMUM_TRANSPARENCY
    )
    {
        impl->leftLevelsAmountDirection *= -1;
    }

    sf::Color color = context.getColorsManager().getColorWhiteCopy();

    color.a = impl->leftLevelsAmountTransparency;

    impl->leftLevelsAmount.setFillColor(color);

    impl->lastAnimationUpdateTime = context.getClockMillisecondsTime();
}

}
}
