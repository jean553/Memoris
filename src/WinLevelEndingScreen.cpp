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

#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace memoris
{
namespace utils
{

class WinLevelEndingScreen::Impl
{

public:

    Impl(const Context& context)
    {
        const auto& colorWhite = context.getColorsManager().getColorWhite();
        const auto& textFont = context.getFontsManager().getTextFont();

        /* TODO: #1164 left levels amount should not be loaded
           into the win level ending screen but directly passed
           as a parameter */
        leftLevelsAmount.setString(
            std::to_string(
                context.getPlayingSerieManager().getRemainingLevelsAmount()
            )
        );

        constexpr unsigned int LEVELS_AMOUNT_TEXT_SIZE {400};
        constexpr float LEFT_LEVELS_LABEL_VERTICAL_POSITION {200.f};

        leftLevelsAmount.setCharacterSize(LEVELS_AMOUNT_TEXT_SIZE);
        leftLevelsAmount.setFont(textFont);
        leftLevelsAmount.setFillColor(colorWhite);
        leftLevelsAmount.setPosition(
            window::getCenteredTextHorizontalPosition(leftLevelsAmount),
            LEFT_LEVELS_LABEL_VERTICAL_POSITION
        );

        constexpr unsigned int TEXT_SIZE {70};
        constexpr float LEFT_LEVELS_SUFFIX_VERTICAL_POSITION {650.f};

        leftLevelsSuffix.setString("levels left");
        leftLevelsSuffix.setCharacterSize(TEXT_SIZE);
        leftLevelsSuffix.setFont(textFont);
        leftLevelsSuffix.setFillColor(colorWhite);
        leftLevelsSuffix.setPosition(
            window::getCenteredTextHorizontalPosition(leftLevelsSuffix),
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
    AbstractLevelEndingScreen(context),
    impl(std::make_unique<Impl>(context))
{
    auto& text = getText();
    constexpr float LEFT_LEVELS_PREFIX_VERTICAL_POSITION {150.f};

    text.setString("You Win !");
    text.setFillColor(context.getColorsManager().getColorGreen());
    text.setPosition(
        window::getCenteredTextHorizontalPosition(text),
        LEFT_LEVELS_PREFIX_VERTICAL_POSITION
    );
}

/**
 *
 */
WinLevelEndingScreen::~WinLevelEndingScreen() = default;

/**
 *
 */
void WinLevelEndingScreen::render() &
{
    const auto& context = getContext();
    auto& window = context.getSfmlWindow();

    window.draw(getFilter());
    window.draw(getText());
    window.draw(impl->leftLevelsSuffix);
    window.draw(impl->leftLevelsAmount);

    constexpr sf::Uint32 ANIMATION_INTERVAL {50};
    auto& lastAnimationUpdateTime = impl->lastAnimationUpdateTime;
    const auto& currentTime = context.getClockMillisecondsTime();

    if (currentTime - lastAnimationUpdateTime < ANIMATION_INTERVAL)
    {
        return;
    }

    auto& leftLevelsAmountTransparency = impl->leftLevelsAmountTransparency;
    auto& leftLevelsAmountDirection = impl->leftLevelsAmountDirection;

    leftLevelsAmountTransparency += leftLevelsAmountDirection;

    constexpr sf::Uint8 MAXIMUM_TRANSPARENCY {255};
    if (
        leftLevelsAmountTransparency == 0 or
        leftLevelsAmountTransparency == MAXIMUM_TRANSPARENCY
    )
    {
        leftLevelsAmountDirection *= -1;
    }

    auto color = context.getColorsManager().getColorWhiteCopy();
    color.a = leftLevelsAmountTransparency;
    impl->leftLevelsAmount.setFillColor(color);

    lastAnimationUpdateTime = currentTime;
}

}
}
