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
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 *
 * Starting point of the program
 */

#include <SFML/Graphics.hpp>

#include "utils/ScreenFactory.hpp"
#include "utils/MusicFactory.hpp"
#include "utils/Controller.hpp"
#include "utils/Context.hpp"

#include "defines/Window.hpp"

/**
 *
 */
int main()
{
    unsigned short currentControllerId =
        factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
    unsigned short nextControllerId = 0;

    std::string currentMusicPath =
        factories::MusicFactory::getMusicPathById(
            currentControllerId
        );
    std::string nextMusicPath = "";

    controllers::Controller* pCurrentController =
        factories::ScreenFactory::getScreenById(
            currentControllerId
        );

    sf::RenderWindow window(
        sf::VideoMode(
            constants::Window::WIDTH,
            constants::Window::HEIGHT,
            constants::Window::RESOLUTION
        ),
        constants::Window::TITLE,
        sf::Style::Fullscreen
    );
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);

    utils::Context context;
    context.setWindow(&window);
    context.changeMusic(currentMusicPath);

    do {

        window.clear();
        nextControllerId = pCurrentController->render(&context);
        window.display();

        if(nextControllerId) {

            delete pCurrentController;

            pCurrentController = factories::ScreenFactory::getScreenById(
                                     nextControllerId
                                 );

            nextMusicPath = factories::MusicFactory::getMusicPathById(
                                nextControllerId
                            );

            if(currentMusicPath != nextMusicPath) {
                context.changeMusic(nextMusicPath);
            }

            currentControllerId = nextControllerId;

            if (currentControllerId == factories::ScreenFactory::EXIT) {
                context.stopMusic();
                window.close();
            }
        }
    } while (window.isOpen());

    return EXIT_SUCCESS;
}
