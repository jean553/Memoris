/*
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
 * @file GameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

#include "controllers.hpp"
#include "SoundsManager.hpp"
#include "PlayingSerieManager.hpp"

namespace memoris
{
namespace controllers
{

/**
 *
 */
GameController::GameController() :
/* TODO: #560 the playing serie manager should not be accessible from
   everywhere; we send the parameter here to force the execution of the
   Level constructor that loads from level file */
    level(series::PlayingSerieManager::get().getNextLevelName())
{
    /* save the exact time the level starts to be displayed; this is used to
       calculate the duration of the watching period before the beginning
       of the playing period */
    displayLevelTime = utils::Context::get().getClockMillisecondsTime();
}

/**
 *
 */
unsigned short GameController::render()
{
    /* displays the game dashboard */
    dashboard.display();

    /* display the level and all the cells */
    /* TODO: #546 only displays the first floor for now, so 0; should be
       modified according to the current user floor */
    level.display(0);

    /* displays all the cells of the level during the time of the watching
       period */
    /* TODO: #547 5000 ms is a default value, should be the actual bonus
       watching time of the player */
    if (
        watchingPeriod &&
        (
            utils::Context::get().getClockMillisecondsTime() -
            displayLevelTime > 5000
        )
    )
    {
        /* hide all the cells of the level */
        level.hideAllCells();

        /* plays the hide level sound */
        sounds::SoundsManager::get().getHideLevelSound().play();

        /* the watching mode is now terminated */
        watchingPeriod = false;

        /* at this moment, we do not save the moment the animation ends; in
           fact, this is not a repeated action, there is no need to save
           the current time here */
    }

    /* used for the screen switch transition animation */
    nextControllerId = animateScreenTransition();

    /* the events loop of the game controller */
    while(utils::Context::get().getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        /* a key is pressed on the keyboard */
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            /* the escape key is pressed down */
            case sf::Keyboard::Escape:
            {
                /* the game is terminated and the called controller is the
                   main menu controller */

                /* NOTE: the game does not ask for confirmation to the player
                   when he pressed the espace key; in fact, this feature does
                   not exist in Memoris: this would give to the player some
                   'relax' time and more time to thinks about how to finish
                   the level, even if the cells are not displayed during the
                   pause time */
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {
                /* useless, added here to respect syntax */
                break;
            }
            }
        }
        default:
        {
            /* useless, added here to respect syntax */
            break;
        }
        }
    }

    return nextControllerId;
}

}
}
