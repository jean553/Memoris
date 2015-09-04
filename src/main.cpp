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

#include "defines/Dimensions.hpp"

/**
 * @return EXIT_SUCCESS when the program correctly finish
 */
int main()
{
    unsigned char currentControllerId =
        factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
    unsigned char nextControllerId = 0;

    std::string currentMusicPath =
        factories::MusicFactory::getMusicPathById(
            currentControllerId
        );
    std::string nextMusicPath = "";

    controllers::Controller *currentController =
        factories::ScreenFactory::getScreenById(
            currentControllerId
        );

    sf::RenderWindow window(
        sf::VideoMode(
            constants::Dimensions::SCREEN_WIDTH,
            constants::Dimensions::SCREEN_HEIGHT,
            32
        ),
        "Memoris",
        sf::Style::Fullscreen
    );
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);

    utils::Context context;
    context.setWindow(&window);
    context.changeMusic(currentMusicPath);

    while(window.isOpen()) {

        window.clear();
        nextControllerId = currentController->render(&context);
        window.display();

        if(nextControllerId) {

            nextMusicPath = factories::MusicFactory::getMusicPathById(
                                nextControllerId
                            );

            if(currentMusicPath != nextMusicPath) {
                context.changeMusic(nextMusicPath);
            }

            delete currentController;
            currentController = factories::ScreenFactory::getScreenById(
                                    nextControllerId
                                );

            currentControllerId = nextControllerId;
        }
    }

    return EXIT_SUCCESS;
}
