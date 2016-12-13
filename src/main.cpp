/**
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
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Controller.hpp"
#include "Context.hpp"
#include "controllers.hpp"
#include "musics.hpp"
#include "SoundsManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

using namespace memoris;

/**
 *
 */
int main()
{
    unsigned short currentControllerId {controllers::MAIN_MENU_CONTROLLER_ID},
             nextControllerId {0};

    std::string currentMusicPath =
        musics::getMusicPathById(currentControllerId),
        nextMusicPath;

    utils::Context context;
    context.loadMusicFile(currentMusicPath);

    do
    {
        auto pCurrentController =
            controllers::getControllerById(
                context,
                currentControllerId
            ); // auto -> std::unique_ptr<controllers::Controller>

        do
        {
            /* NOTE: this instruction generates memory leaks; this error comes
               from OpenGL libraries; we do not handle this error; the leak is
               deleted if we delete this line */
            context.getSfmlWindow().clear();

            nextControllerId = pCurrentController->render(context);

            context.getSfmlWindow().display();
        }
        while (!nextControllerId);

        if (currentControllerId == controllers::EXIT)
        {
            continue;
        }

        nextMusicPath =
            musics::getMusicPathById(nextControllerId);

        /* does not reload a different music when go from one game controller
           to another one */
        if(
            currentMusicPath != nextMusicPath and
            currentControllerId != nextControllerId
        )
        {
            context.loadMusicFile(nextMusicPath);
            currentMusicPath = nextMusicPath;
        }

        currentControllerId = nextControllerId;

        context.getSoundsManager().playScreenTransitionSound();

        context.restartClock();
    }
    while (currentControllerId != controllers::EXIT);

    context.stopMusic();

    context.getSfmlWindow().close();

    return EXIT_SUCCESS;
}
