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
 */

#include "Controller.hpp"
#include "Context.hpp"
#include "controllers.hpp"
#include "musics.hpp"

using namespace memoris;

/**
 *
 */
int main()
{
    /* the current controller id variable contains the id of the currently
       rendered controller; when the program starts, the first controller
       to display is the main menu controller. */
    unsigned short currentControllerId =
        controllers::MAIN_MENU_CONTROLLER_ID;

    /* the current music path string contains the file system path of the
       music currently played by the current controller; when the program
       starts, the played music is the menu music */
    std::string currentMusicPath =
        musics::getMusicPathById(currentControllerId);

    /* the context is an unique object that is transfered from one controller
       to another during controllers switch; it contains data to exchange
       between controller, it also contains the SFML window; the context
       constructor also loads the fonts manager, that loads fonts from file;
       an exception is thrown here if at least one font file couldn't be
       opened, the error message is displayed in the console */
    utils::Context context;

    /* load and play the main menu music when the program starts */
    context.loadMusicFile(currentMusicPath);

    /* the next controller id contains the id of the new controller to
       initialize. After generation of a controller, the current controller id
       is equal to the next controller id, the next controller id is equal
       to 0. When a controller calls a new controller, the next controller id
       variable is updated. If the next controller id and the current
       controller id are different, the controller with the nextControllerId
       value is generated.*/
    unsigned short nextControllerId = 0;

    /* the next music path string contains the path of the next music to
       load and play during the next controller generation. Sometimes, from
       one controller to another, the currentMusicPath and the nxtMusicPath are
       the sames, there is no interupt and modification of the playing music;
       if they are different during the generation of a new controller, a new
       music will be loaded using the nextMusicPath */
    std::string nextMusicPath;

    /* first loop, calls the render loop and create each controller
       when necessary */
    do
    {
        /* create a pointer to the current controller, pointing to the
           controller to render; we use a pointer as there are different
           children classes of controllers, all children of the Controller
           class. */
        controllers::Controller* pCurrentController =
            controllers::getControllerById(
                currentControllerId,
                context
            );

        /* main program loop: loads, renders and modifies controllers;
           the loop stops when the SFML window is closed */
        do
        {
            /* continually clear the whole SFML window content */
            context.getSfmlWindow().clear();

            /* continually render the current controller scene */
            nextControllerId = pCurrentController->render(context);

            /* continually display the loaded content */
            context.getSfmlWindow().display();
        }
        while (!nextControllerId);

        /* delete the controller pointed by the current controller pointer */
        delete pCurrentController;

        /* check if the program is supposed to be terminated */
        if (currentControllerId != controllers::EXIT)
        {
            /* get the path of the new music to load according to the next
               controller to load; sometimes, the music path is the same as
               the current controller music path */
            nextMusicPath =
                musics::getMusicPathById(nextControllerId);

            /* check if the current music path and the next music path are
               different; if they are different, a new music has to be
               loaded */
            if(currentMusicPath != nextMusicPath)
            {
                /* if the current music path and the next music path are
                   different, load and play the new music according to the
                   next music path */
                context.loadMusicFile(nextMusicPath);
                currentMusicPath = nextMusicPath;
            }

            currentControllerId = nextControllerId;

            /* if the program is not supposed to be terminated, the screen
               content is updated: a common sound is played during the
               visual switch */
            context.getSoundsManager().getScreenTransitionSound().play();

            /* restart the clock */
            context.restartClock();
        }
    }
    while (currentControllerId != controllers::EXIT);

    context.stopMusic();

    /* close the SFML window */
    context.getSfmlWindow().close();

    return EXIT_SUCCESS;
}
