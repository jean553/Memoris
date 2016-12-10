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
 * @file RankingController.hpp
 * @brief displays ranking for one serie
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "RankingController.hpp"

#include "Context.hpp"
#include "controllers.hpp"
#include "PlayingSerieManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"
#include "window.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <array>
#include <string>
#include <memory>

namespace memoris
{
namespace controllers
{

class RankingController::Impl
{

public:

    Impl(const utils::Context& context)
    {
        // const std::array<std::string, N>&
        auto& results = context.getPlayingSerieManager().getResults();

        // const sf::Font&
        const auto& font = context.getFontsManager().getTextFont();

        for (
            managers::PlayingSerieManager::Results::const_iterator it =
                results.begin();
            it != results.end();
            ++it
        )
        {
            /* skip undefined result */
            if (*it == ".")
            {
                continue;
            }

            // std::unique_ptr<sf::Text>
            auto resultText = std::make_unique<sf::Text>(
                *it,
                font,
                fonts::TEXT_SIZE
            );

            resultText->setPosition(
                window::getCenteredSfmlSurfaceHorizontalPosition(*resultText),
                RESULTS_FIRST_ITEM_VERTICAL_POSITION +
                    RESULTS_INTERVAL * std::distance(results.begin(), it)
            );

            resultsTexts.push_back(std::move(resultText));
        }
    }

    /* use pointers instead of plain objects in order to accelerate the copy
       process (sf::Text has no move constructor) */
    std::vector<std::unique_ptr<sf::Text>> resultsTexts;
};

/**
 *
 */
RankingController::RankingController(
    const utils::Context& context
) :
    Controller(context),
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
RankingController::~RankingController() noexcept = default;

/**
 *
 */
const unsigned short& RankingController::render(
    const utils::Context& context
) &
{
    // const std::unique_ptr<sf::Text>&
    for (const auto& resultText : impl->resultsTexts)
    {
        context.getSfmlWindow().draw(*resultText);
    }

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
