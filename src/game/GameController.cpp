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
 * @file GameController.hpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

using namespace controllers;

/**
 *
 */
GameController::GameController()
{
    window = new sf::RenderWindow(
        sf::VideoMode(1600, 900, 32),
        "SFML",
        sf::Style::Fullscreen
    );

    context = new utils::Context(window);

    currentControllerId = factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;

    currentController = factories::ScreenFactory::getScreenById(
                            currentControllerId
                        );

    currentMusicPath = factories::MusicFactory::getMusicPathById(
                           currentControllerId
                       );

    nextMusicPath = "";
    nextControllerId = 0;
}

/**
 *
 */
GameController::GameController(const GameController &gameController)
{
    context = new utils::Context(*gameController.context);

    window = context->getWindow();

    currentControllerId = gameController.currentControllerId;
    nextControllerId = gameController.nextControllerId;
    currentMusicPath = gameController.currentMusicPath;
    nextMusicPath = gameController.nextMusicPath;

    currentController = factories::ScreenFactory::getScreenById(
                            currentControllerId
                        );
}

/**
 *
 */
GameController::~GameController()
{
    delete currentController;
    delete context;
    delete window;
}

/**
 *
 */
void GameController::run()
{
    window->setMouseCursorVisible(false);

    // load the first music, main menu music
    context->changeMusic(currentMusicPath);

    while(window->isOpen()) {
        window->clear();

        nextControllerId = currentController->render(context);

        window->display();

        if(nextControllerId) {

            // update the current music
            nextMusicPath = factories::MusicFactory::getMusicPathById(
                                nextControllerId
                            );
            if(currentMusicPath != nextMusicPath) {
                context->changeMusic(nextMusicPath);
            }

            // update the current screen controller
            delete currentController;
            currentController = factories::ScreenFactory::getScreenById(
                                    nextControllerId
                                );

            currentControllerId = nextControllerId;
        }
    }
}
