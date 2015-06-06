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
 * New game screen.
 *
 * @file NewGameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "NewGameController.hpp"

using namespace controllers;

/**
 *
 */
NewGameController::NewGameController() : Controller()
{
    fontTitle.loadFromFile(PATH_FONT_TITLE);
    fontExplanation.loadFromFile(PATH_FONT_TEXT);

    colorTitle.r = COLOR_LIGHT_BLUE_RED;
    colorTitle.g = COLOR_LIGHT_BLUE_GREEN;
    colorTitle.b = COLOR_LIGHT_BLUE_BLUE;
    colorTitle.a = COLOR_ALPHA_FULL;

    colorExplanation.r = COLOR_WHITE_RED;
    colorExplanation.g = COLOR_WHITE_GREEN;
    colorExplanation.b = COLOR_WHITE_BLUE;
    colorExplanation.a = COLOR_ALPHA_FULL;

    title.setFont(fontTitle);
    title.setString(STRING_NEW_GAME_TITLE);
    title.setCharacterSize(SIZE_SUB_TITLE_FONT);
    title.setColor(colorTitle);
    title.setPosition(
        POSITION_NEW_GAME_TITLE_X,
        POSITION_NEW_GAME_TITLE_Y
    );

    explanation.setFont(fontExplanation);
    explanation.setString(STRING_NEW_GAME_EXPLANATION);
    explanation.setCharacterSize(SIZE_TEXT_FONT);
    explanation.setColor(colorExplanation);
    explanation.setPosition(
        POSITION_NEW_GAME_EXPLANATION_X,
        POSITION_NEW_GAME_EXPLANATION_Y
    );

    soundBuffer.loadFromFile(SOUND_OPEN_SCREEN);

    soundSelectorSelect.setBuffer(soundBuffer);

    inputTextGameName = new widgets::InputTextWidget(
        POSITION_NAME_INPUT_TEXT_X,
        POSITION_NAME_INPUT_TEXT_Y,
        SIZE_NAME_INPUT_TEXT,
        STRING_NAME_DEFAULT,
        MAX_NAME_LENGTH
    );

    soundSelectorSelect.play();
}

/**
 *
 */
NewGameController::~NewGameController()
{
    delete inputTextGameName;
}

/**
 *
 */
unsigned char NewGameController::render(utils::Context* context)
{
    context->getWindow()->draw(title);
    context->getWindow()->draw(explanation);

    inputTextGameName->display(context);

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
                    default:
                    {
                        inputTextGameName->update(&event);

                        break;
                    }
                }
            }
        }
    }

    return nextControllerId;
}
