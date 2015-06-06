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
 * @file EditorSerieController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorSerieController.hpp"

using namespace controllers;

/**
 *
 */
EditorSerieController::EditorSerieController() : Controller()
{
    soundBuffer.loadFromFile(SOUND_OPEN_SCREEN);

    soundOpenScreen.setBuffer(soundBuffer);

    titleBar = new widgets::TitleBarWidget(
        STRING_EDITOR_SERIE_TITLE
    );

    soundOpenScreen.play();
}

/**
 *
 */
EditorSerieController::~EditorSerieController()
{
    delete titleBar;
}

/**
 *
 */
unsigned char EditorSerieController::render(utils::Context* context)
{
    titleBar->display(context);

    while(context->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        nextControllerId = MAIN_MENU_CONTROLLER_ID;

                        break;
                    }
                }
            }
        }
    }

    return nextControllerId;
}
