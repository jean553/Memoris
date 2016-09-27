/**
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
 * @file Context.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Context.hpp"

#include "TexturesManager.hpp"
#include "SoundsManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "CellsTexturesManager.hpp"
#include "PlayingSerieManager.hpp"
#include "EditingLevelManager.hpp"
#include "Game.hpp"
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

namespace memoris
{
namespace utils
{

class Context::Impl
{

public:

    managers::TexturesManager texturesManager;
    managers::SoundsManager soundsManager;
    managers::ColorsManager colorsManager;
    managers::FontsManager fontsManager;
    managers::CellsTexturesManager cellsTexturesManager;
    managers::PlayingSerieManager playingSerieManager;
    managers::EditingLevelManager editingLevelManager;

    sf::RenderWindow sfmlWindow =
    {
        sf::VideoMode(
            window::WIDTH,
            window::HEIGHT,
            window::RESOLUTION
        ),
        window::TITLE,
        sf::Style::Fullscreen
    };

    sf::Music music;

    /* unique SFML clock for time management in every controller
     *
     * NOTE: we use an unique clock for all the animation and time
     * management of the game; the clock is restarted everytime the
     * controller is modified; the maximum time returned in milliseconds
     * is equal to 49 days... so this is a safe method */
    sf::Clock clock;

    /* unique pointer to the current loaded game; this pointed object is
       initialized when a new game is created or when an existing game is
       loaded; if there is no need to have a game loaded at the moment,
       the pointer is just null; when the context is created, the main menu
       is rendered, at this moment, the game has no reason to be loaded;
       initialized in the implementation to use forwarding declaration */
    std::unique_ptr<entities::Game> game {nullptr};
};

/**
 *
 */
Context::Context() : impl(std::make_unique<Impl>())
{
    /* when the window is opened, the default SFML cursor is not displayed */
    impl->sfmlWindow.setMouseCursorVisible(false);

    /* prevent the user to keep a key pressed down: the events are only
       triggered one time during the first press down and not continually */
    impl->sfmlWindow.setKeyRepeatEnabled(false);
}

/**
 *
 */
Context::~Context() noexcept = default;

/**
 *
 */
const managers::TexturesManager& Context::getTexturesManager() const & noexcept
{
    return impl->texturesManager;
}

/**
 *
 */
const managers::SoundsManager& Context::getSoundsManager() const & noexcept
{
    return impl->soundsManager;
}

/**
 *
 */
const managers::ColorsManager& Context::getColorsManager() const & noexcept
{
    return impl->colorsManager;
}

/**
 *
 */
const managers::FontsManager& Context::getFontsManager() const & noexcept
{
    return impl->fontsManager;
}

/**
 *
 */
const managers::CellsTexturesManager& Context::getCellsTexturesManager() const
& noexcept
{
    return impl->cellsTexturesManager;
}

/**
 *
 */
managers::PlayingSerieManager& Context::getPlayingSerieManager() const &
noexcept
{
    return impl->playingSerieManager;
}

/**
 *
 */
managers::EditingLevelManager& Context::getEditingLevelManager() const &
noexcept
{
    return impl->editingLevelManager;
}

/**
 *
 */
sf::RenderWindow& Context::getSfmlWindow() const & noexcept
{
    return impl->sfmlWindow;
}

/**
 *
 */
const sf::Int32 Context::getClockMillisecondsTime() const &
{
    return impl->clock.getElapsedTime().asMilliseconds();
}

/**
 *
 */
void Context::loadMusicFile(const std::string& path) &
{
    if(path.empty())
    {
        return;
    }

    stopMusic();

    if(impl->music.openFromFile(path))
    {
        impl->music.play();
    }
}

/**
 *
 */
void Context::stopMusic() &
{
    if(impl->music.getStatus() == sf::Sound::Playing)
    {
        impl->music.stop();
    }
}

/**
 *
 */
void Context::restartClock() &
{
    impl->clock.restart();
}

/**
 *
 */
void Context::createGame(const std::string& name) &
{
    if (impl->game != nullptr)
    {
        impl->game.reset();
    }

    impl->game = std::make_unique<entities::Game>(name);
}

}
}
