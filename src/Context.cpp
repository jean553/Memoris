/**
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
#include "ShapesManager.hpp"
#include "PlayingSerieManager.hpp"
#include "EditingLevelManager.hpp"
#include "window.hpp"
#include "Game.hpp"
#include "controllers_ids.hpp"

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
    managers::ShapesManager shapesManager;
    managers::PlayingSerieManager playingSerieManager;
    managers::EditingLevelManager editingLevelManager;

    sf::RenderWindow sfmlWindow =
    {
        /* the float width is only converted once
           when creating the window and no conversion
           is necessary when calculating the horizontal
           position of centered text */
        sf::VideoMode(
            static_cast<unsigned int>(window::WIDTH),
            window::HEIGHT
        ),
        "Memoris",
        sf::Style::Fullscreen
    };

    sf::Music music;

    sf::Clock clock;

    /* TODO: to delete */
    entities::Game game;

    std::string gameName;
};

/**
 *
 */
Context::Context() : impl(std::make_unique<Impl>())
{
    auto& window = impl->sfmlWindow;
    window.setMouseCursorVisible(false);

    /* prevent the user to keep a key pressed down: the events are only
       triggered one time during the first press down and not continuously */
    window.setKeyRepeatEnabled(false);
}

/**
 *
 */
Context::~Context() = default;

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
const managers::ShapesManager& Context::getShapesManager() const & noexcept
{
    return impl->shapesManager;
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
const Context::MusicId Context::getMusicId(const controllers::ControllerId& id)
    const & noexcept
{
    if (id != controllers::ControllerId::Game)
    {
        return Context::MusicId::MenuMusic;
    }

    constexpr unsigned int MAXIMUM_RANDOM_GAME_MUSIC {2};
    unsigned int randomNumber = rand() % MAXIMUM_RANDOM_GAME_MUSIC;

    if (randomNumber == 0)
    {
        return Context::MusicId::FirstGameMusic;
    }

    return Context::MusicId::SecondGameMusic;
}

/**
 *
 */
void Context::loadMusicFile(const MusicId& id) const &
{
    std::string path;

    switch(id)
    {
    case Context::MusicId::FirstGameMusic:
    {
        path = "Zeropage_-_Ambiose";

        break;
    }
    case Context::MusicId::SecondGameMusic:
    {
        path = "Zeropage_-_Void_Sensor";

        break;
    }
    default:
    {
        path = "Zeropage_-_Ambient_Dance";
    }
    }

    stopMusic();

    auto& music = impl->music;

    constexpr char MUSICS_PATH[] {"res/musics/"};
    constexpr char MUSICS_EXTENSION[] {".ogg"};
    if(music.openFromFile(MUSICS_PATH + path + MUSICS_EXTENSION))
    {
        music.play();
        music.setLoop(true);
    }
}

/**
 *
 */
void Context::stopMusic() const &
{
    auto& music = impl->music;
    if(music.getStatus() == sf::Sound::Playing)
    {
        music.stop();
    }
}

/**
 *
 */
void Context::restartClock() const &
{
    impl->clock.restart();
}

/**
 *
 */
const entities::Game& Context::getGame() const & noexcept
{
    return impl->game;
}

/**
 *
 */
void Context::setGameName(const std::string& gameName) const & noexcept
{
    impl->gameName = gameName;
}

}
}
