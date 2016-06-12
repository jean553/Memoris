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

#include "ControllerFactory.hpp"
#include "MusicFactory.hpp"
#include "Controller.hpp"
#include "Context.hpp"

/**
 *
 */
int main()
{
    unsigned short currentControllerId =
        factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
    unsigned short nextControllerId = 0;

    std::string currentMusicPath =
        factories::MusicFactory::getMusicPathById(
            currentControllerId
        );
    std::string nextMusicPath;

    utils::Context context;
    context.changeMusic(currentMusicPath);

    controllers::Controller* pCurrentController =
        factories::ControllerFactory::getControllerById(
            currentControllerId,
            &context
        );

    do
    {

        context.getSfmlWin().clear();
        nextControllerId = pCurrentController->render(&context);
        context.getSfmlWin().display();

        if(nextControllerId)
        {

            delete pCurrentController;

            pCurrentController =
                factories::ControllerFactory::getControllerById(
                    nextControllerId,
                    &context
                );

            nextMusicPath =
                factories::MusicFactory::getMusicPathById(
                    nextControllerId
                );

            if(currentMusicPath != nextMusicPath)
            {
                context.changeMusic(nextMusicPath);
                currentMusicPath = nextMusicPath;
            }

            currentControllerId = nextControllerId;

            if (currentControllerId == factories::ControllerFactory::EXIT)
            {
                context.stopMusic();
                context.getSfmlWin().close();
            }
            else
            {
                context.playScreenTransitionCommonSound();
            }
        }
    }
    while (context.getSfmlWin().isOpen());

    return EXIT_SUCCESS;
}
