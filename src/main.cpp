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
    /* the current controller id variable contains the id of the currently
       rendered controller; when the program starts, the first controller
       to display is the main menu controller. */
    unsigned short currentControllerId =
        factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

    /* the current music path string contains the file system path of the
       music currently played by the current controller; when the program
       starts, the played music is the menu music */
    std::string currentMusicPath =
        factories::MusicFactory::getMusicPathById(currentControllerId);

    /* the context is an unique object that is transfered from one controller
       to another during controllers switch; it contains data to exchange
       between controller, it also contains the SFML window */
    utils::Context context;

    /* load and play the main menu music when the program starts */
    context.loadMusicFile(currentMusicPath);

    /* FIXME: #406 do not use a controller pointer anymore */
    controllers::Controller* pCurrentController =
        factories::ControllerFactory::getControllerById(
            currentControllerId,
            &context
        );

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
       music will be loaded using the nxtMusicPath */
    std::string nextMusicPath;

    /* main program loop: loads, renders and modifies controllers;
       the loop stops when the SFML window is closed */
    do
    {
        /* continually clear the whole SFML window content */
        context.getSfmlWindow().clear();

        /* continually render the current controller scene */
        /* FIXME: #407 do not use context pointers
           at all, only use reference */
        nextControllerId = pCurrentController->render(&context);

        /* continually display the loaded content */
        context.getSfmlWindow().display();

        /* if the next controller id is not equal to 0, that means a new
           controller has to be generated, or the program has ot be
           terminated */
        if(nextControllerId)
        {
            /* FIXME: #407 */
            delete pCurrentController;

            pCurrentController =
                factories::ControllerFactory::getControllerById(
                    nextControllerId,
                    &context
                );

            /* get the path of the new music to load according to the next
               controller to load; sometimes, the music path is the same as
               the current controller music path */
            nextMusicPath =
                factories::MusicFactory::getMusicPathById(nextControllerId);

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

            /* check if the called id is the one supposed to terminate the
               program; the EXIT id is not pointing to any controller */
            if (currentControllerId == factories::ControllerFactory::EXIT)
            {
                context.stopMusic();

                /* close the SFML window */
                context.getSfmlWindow().close();
            }
            else
            {
                /* if the program is not supposed to be terminated, the screen
                   content is updated: a common sound is played during the
                   visual switch */
                context.playScreenTransitionSound();
            }
        }
    }
    while (context.getSfmlWindow().isOpen());

    return EXIT_SUCCESS;
}
