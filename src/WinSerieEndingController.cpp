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
#include "controllers.hpp"
#include "fonts.hpp"
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

#include <array>

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
        title.setCharacterSize(fonts::TITLE_SIZE);
        title.setFont(textFont);
        title.setColor(colorsManager.getColorLightBlue());
        title.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        const auto& playingSerieManager = context.getPlayingSerieManager();

        time.setString(playingSerieManager.getPlayingTimeAsString());
        time.setCharacterSize(fonts::TITLE_SIZE);
        time.setFont(textFont);
        time.setColor(colorsManager.getColorWhite());
        time.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(time),
            TIME_VERTICAL_POSITION
        );

        auto& results = playingSerieManager.getResults();

        /* TODO: we copy because every text item has a white color
         * that will change when switch from the user serie time
         * to the previous best results; this should be improved:
         * one common color should be used by every text surface */
        sf::Color colorResults = colorsManager.getColorWhiteCopy();
        colorResults.a = 0;

        unsigned short index {0};

        for (const entities::SerieResult& result : results)
        {
            std::string resultString = result.getString();

            if (resultString == ".")
            {
                continue;
            }

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
                fonts::TEXT_SIZE
            );

            resultText->setPosition(
                window::getCenteredSfmlSurfaceHorizontalPosition(*resultText),
                RESULTS_FIRST_ITEM_VERTICAL_POSITION + RESULTS_INTERVAL * index
            );

            resultText->setColor(colorResults);

            resultsTexts.push_back(std::move(resultText));

            index++;
        }

        colorWhite = context.getColorsManager().getColorWhiteCopy();
    }

    sf::Text title;
    sf::Text time;

    utils::AnimatedBackground background;

    others::HorizontalGradient gradient;

    /* use pointers instead of plain objects in order to accelerate the copy
       process (sf::Text has no move constructor) */
    std::vector<std::unique_ptr<sf::Text>> resultsTexts;

    bool displayRanking {false};
    bool switchingDisplayedContent {false};

    sf::Int32 lastAnimationUpdateTime {0};

    sf::Color colorWhite;
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

    impl->background.render();
    impl->gradient.render(context);

    sf::Int32 currentTime = context.getClockMillisecondsTime();

    constexpr sf::Int32 SWITCH_ANIMATION_INTERVAL {30};
    if (
        impl->switchingDisplayedContent and
        currentTime - impl->lastAnimationUpdateTime > SWITCH_ANIMATION_INTERVAL
    )
    {
        constexpr sf::Uint8 OPACITY_UPDATE_INTERVAL {51};

        if (!impl->displayRanking)
        {
            /* create a new object and do not use references here; the function
               sf::Color::getColor() returns a constant reference but we want
               update the opacity */
            sf::Color titleColor = impl->title.getColor();

            titleColor.a -= OPACITY_UPDATE_INTERVAL;
            impl->colorWhite.a -= OPACITY_UPDATE_INTERVAL;

            impl->title.setColor(titleColor);
            impl->time.setColor(impl->colorWhite);

            if (titleColor.a == 0)
            {
                impl->displayRanking = true;
            }
        }
        else
        {
            impl->colorWhite.a += OPACITY_UPDATE_INTERVAL;

            // const std::unique_ptr<sf::Text>&
            for (const auto& resultText : impl->resultsTexts)
            {
                (*resultText).setColor(impl->colorWhite);
            }

            constexpr sf::Uint8 COLOR_WHITE_MAX_OPACITY {255};
            if (impl->colorWhite.a == COLOR_WHITE_MAX_OPACITY)
            {
                impl->switchingDisplayedContent = false;
            }
        }

        impl->lastAnimationUpdateTime = currentTime;
    }

    if (impl->displayRanking)
    {
        // const std::unique_ptr<sf::Text>&
        for (const auto& resultText : impl->resultsTexts)
        {
            context.getSfmlWindow().draw(*resultText);
        }
    }
    else
    {
        context.getSfmlWindow().draw(impl->title);
        context.getSfmlWindow().draw(impl->time);
    }

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
            {
                if (!impl->displayRanking)
                {
                    impl->switchingDisplayedContent = true;

                    break;
                }

                setExpectedControllerId(ControllerId::MainMenu);

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

    return getNextControllerId();
}

}
}
