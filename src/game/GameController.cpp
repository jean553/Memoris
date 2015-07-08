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
    screenFactory = new factories::ScreenFactory();
    musicFactory = new factories::MusicFactory();

    context = new utils::Context();

    currentController = screenFactory->getScreenById(
                            MAIN_MENU_CONTROLLER_ID
                        );

    currentMusicPath = musicFactory->getMusicPathById(
                           MAIN_MENU_CONTROLLER_ID
                       );

    nextMusicPath = "";

    currentControllerId = MAIN_MENU_CONTROLLER_ID;
    nextControllerId = 0;
}

/**
 *
 */
GameController::~GameController()
{
    delete screenFactory;
    delete musicFactory;

    delete currentController;

    delete context;
}

/**
 *
 */
void GameController::run(sf::RenderWindow* window)
{
    context->setWindow(window);
    window->setMouseCursorVisible(false);

    // load the first music, main menu music
    context->changeMusic(currentMusicPath);

    while(window->isOpen()) {
        window->clear();

        nextControllerId = currentController->render(context);

        window->display();

        if(nextControllerId) {

            // update the current music
            nextMusicPath = musicFactory->getMusicPathById(
                                nextControllerId
                            );
            if(currentMusicPath != nextMusicPath) {
                context->changeMusic(nextMusicPath);
            }

            // update the current screen controller
            delete currentController;
            currentController = screenFactory->getScreenById(
                                    nextControllerId
                                );

            currentControllerId = nextControllerId;
        }
    }
}
