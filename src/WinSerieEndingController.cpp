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

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <fstream>

namespace memoris
{
namespace controllers
{

constexpr char GAMES_FILES_DIRECTORY[] {"data/games/"};
constexpr char GAMES_FILES_EXTENSION[] {".game"};

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
        title.setFont(textFont);
        title.setFillColor(colorsManager.getColorLightBlue());

        const auto& playingSerieManager = context.getPlayingSerieManager();

        time.setString(playingSerieManager.getPlayingTimeAsString());
        time.setFont(textFont);
        time.setFillColor(colorsManager.getColorWhite());

        constexpr unsigned int TEXTS_SIZE {140};
        title.setCharacterSize(TEXTS_SIZE);
        time.setCharacterSize(TEXTS_SIZE);

        constexpr float TITLE_VERTICAL_POSITION {200.f};
        title.setPosition(
            window::getCenteredTextHorizontalPosition(title),
            TITLE_VERTICAL_POSITION
        );

        constexpr float TIME_VERTICAL_POSITION {400.f};
        time.setPosition(
            window::getCenteredTextHorizontalPosition(time),
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
    unlockNextSerieFromGameFile();
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

    auto& title = impl->title;
    auto& time = impl->time;

    impl->background.render();
    impl->gradient.render();

    auto& window = context.getSfmlWindow();
    window.draw(title);
    window.draw(time);

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

/**
 *
 */
inline void WinSerieEndingController::unlockNextSerieFromGameFile() const &
{
    /* we cannot read, clear, write a file, the only solution
       is to first open it for reading and then open it again
       for clear its content and write into it */

    const std::string fileName = GAMES_FILES_DIRECTORY +
        getContext().getGameName() +
        GAMES_FILES_EXTENSION;

    std::fstream file;
    file.open(
        fileName,
        std::ios::in
    );

    char serieCharacter;
    file.get(serieCharacter);
    file.close();

    unsigned short lastUnlockedSerie = serieCharacter - '0';
    lastUnlockedSerie += 1;

    file.open(
        fileName,
        std::ios::trunc | std::ios::out
    );
    file << lastUnlockedSerie;
}

}
}
