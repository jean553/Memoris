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
#include "window.hpp"

namespace memoris
{
namespace utils
{

/**
 * The constructor initializes the SFML window object: the dimensions,
 * the resolution, the title and the mode ( fullscreen ) are set
 */
Context::Context() : sfmlWindow(
        sf::VideoMode(
            window::WIDTH,
            window::HEIGHT,
            window::RESOLUTION
        ),
        window::TITLE,
        sf::Style::Fullscreen
    )
{
    /* when the window is opened, the default SFML cursor is not displayed */
    sfmlWindow.setMouseCursorVisible(false);

    /* prevent the user to keep a key pressed down: the events are only
       triggered one time during the first press down and not continually */
    sfmlWindow.setKeyRepeatEnabled(false);
}

/**
 *
 */
sf::RenderWindow& Context::getSfmlWindow()
{
    return sfmlWindow;
}

/**
 *
 */
void Context::loadMusicFile(const std::string& path)
{
    /* ends the function immediately if the path is empty */
    if(path.empty())
    {
        return;
    }

    /* stop the playing music before loading the new one */
    stopMusic();

    /* open the new music from the given file */
    if(music.openFromFile(path))
    {
        /* the music is played only if the file can be opened, if no, the
           program continues but the music is not played; this is not a problem
           as the context check if the music is playing before stopping it */
        music.play();
    }
}

/**
 *
 */
void Context::stopMusic()
{
    /* check if the music object is playing a music */
    if(music.getStatus() == sf::Sound::Playing)
    {
        /* stop the SFML music */
        music.stop();
    }
}

/**
 *
 */
sf::Int32 Context::getClockMillisecondsTime() const
{
    return clock.getElapsedTime().asMilliseconds();
}

/**
 *
 */
void Context::restartClock()
{
    clock.restart();
}

}
}
