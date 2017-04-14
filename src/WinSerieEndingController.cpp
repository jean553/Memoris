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
 * @file WinSerieEndingController.hpp
 * @brief the wining screen that is displayed when the user wins the serie
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "WinSerieEndingController.hpp"

#include "controllers_ids.hpp"
#include "Context.hpp"
#include "fonts_sizes.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "window.hpp"
#include "AnimatedBackground.hpp"
#include "HorizontalGradient.hpp"
#include "PlayingSerieManager.hpp"
#include "SerieResult.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

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
        const auto& textFont = context.getFontsManager().getTextFont();
        const auto& colorsManager = context.getColorsManager();

        title.setString("Serie finished !");
        title.setCharacterSize(sizes::TITLE_SIZE);
        title.setFont(textFont);
        title.setFillColor(colorsManager.getColorLightBlue());

        const auto& playingSerieManager = context.getPlayingSerieManager();

        time.setString(playingSerieManager.getPlayingTimeAsString());
        time.setCharacterSize(sizes::TITLE_SIZE);
        time.setFont(textFont);
        time.setFillColor(colorsManager.getColorWhite());

        constexpr float TITLE_VERTICAL_POSITION {200.f};
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        constexpr float TIME_VERTICAL_POSITION {400.f};
        time.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(time),
            TIME_VERTICAL_POSITION
        );

        const auto& results = playingSerieManager.getResults();

        for (
            auto result = results.cbegin();
            result < results.cend();
            ++result
        )
        {
            std::string resultString = (*result)->getString();

            /* replace commas by space for graphical reasons; I got some
               problem by adding the space character directly into the file */
            std::replace(
                resultString.begin(),
                resultString.end(),
                ',',
                ' '
            );

            auto resultText = std::make_unique<sf::Text>(
                resultString,
                textFont,
                sizes::TEXT_SIZE
            );

            const auto index = std::distance(
                results.cbegin(),
                result
            );

            constexpr float RESULTS_FIRST_ITEM_VERTICAL_POSITION {300.f};
            constexpr float RESULTS_INTERVAL {50.f};
            resultText->setPosition(
                window::getCenteredSfmlSurfaceHorizontalPosition(*resultText),
                RESULTS_FIRST_ITEM_VERTICAL_POSITION + RESULTS_INTERVAL * index
            );
            resultText->setFillColor(colorsManager.getColorWhiteAlphaCopy());

            resultsTexts.push_back(std::move(resultText));
        }

        colorTimeTexts = colorsManager.getColorWhiteCopy();
    }

    sf::Text title;
    sf::Text time;

    utils::AnimatedBackground background;

    others::HorizontalGradient gradient;

    /* use pointers instead of plain objects in order to accelerate the copy
       process (sf::Text has no move constructor) */
    std::vector<std::unique_ptr<sf::Text>> resultsTexts;

    bool renderTransitionAnimation {false};

    sf::Int32 lastAnimationUpdateTime {0};

    sf::Color colorTimeTexts;
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
WinSerieEndingController::~WinSerieEndingController() = default;

/**
 *
 */
const ControllerId& WinSerieEndingController::render() const &
{
    const auto& context = getContext();
    auto currentTime = context.getClockMillisecondsTime();

    auto& renderTransitionAnimation = impl->renderTransitionAnimation;
    auto& lastAnimationUpdateTime = impl->lastAnimationUpdateTime;

    auto& title = impl->title;
    auto& time = impl->time;

    impl->background.render();
    impl->gradient.render(context);

    sf::Color titleColor = title.getFillColor();
    auto& titleTransparency = titleColor.a;

    constexpr sf::Int32 SWITCH_ANIMATION_INTERVAL {30};
    if (
        renderTransitionAnimation and
        currentTime - lastAnimationUpdateTime > SWITCH_ANIMATION_INTERVAL
    )
    {
        constexpr sf::Uint8 OPACITY_UPDATE_INTERVAL {51};

        auto& colorTimeTexts = impl->colorTimeTexts;
        auto& whiteTransparency = colorTimeTexts.a;

        if (titleTransparency != 0)
        {
            titleTransparency -= OPACITY_UPDATE_INTERVAL;
            whiteTransparency -= OPACITY_UPDATE_INTERVAL;

            title.setFillColor(titleColor);
            time.setFillColor(colorTimeTexts);
        }
        else
        {
            whiteTransparency += OPACITY_UPDATE_INTERVAL;

            for (const auto& resultText : impl->resultsTexts)
            {
                (*resultText).setFillColor(colorTimeTexts);
            }

            constexpr sf::Uint8 COLOR_WHITE_MAX_OPACITY {255};
            if (whiteTransparency == COLOR_WHITE_MAX_OPACITY)
            {
                renderTransitionAnimation = false;
            }
        }

        lastAnimationUpdateTime = currentTime;
    }

    auto& window = context.getSfmlWindow();

    if (titleTransparency == 0)
    {
        for (const auto& resultText : impl->resultsTexts)
        {
            window.draw(*resultText);
        }
    }
    else
    {
        window.draw(title);
        window.draw(time);
    }

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
            {
                if (titleTransparency != 0)
                {
                    renderTransitionAnimation = true;

                    break;
                }

                setExpectedControllerId(ControllerId::MainMenu);

                break;
            }
            default:
            {
                break;
            }
            }
        }
        default:
        {
            break;
        }
        }
    }

    return getNextControllerId();
}

}
}
