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
 * @file EditorNewSerieController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorNewSerieController.hpp"

using namespace controllers;

/**
 *
 */
EditorNewSerieController::EditorNewSerieController() : Controller()
{
    fontExplanation.loadFromFile(PATH_FONT_TEXT);

    colorExplanation.r = COLOR_WHITE_RED;
    colorExplanation.g = COLOR_WHITE_GREEN;
    colorExplanation.b = COLOR_WHITE_BLUE;
    colorExplanation.a = COLOR_ALPHA_FULL;

    explanation.setFont(fontExplanation);
    explanation.setString(STRING_NEW_SERIE_EXPLANATION);
    explanation.setCharacterSize(SIZE_TEXT_FONT);
    explanation.setColor(colorExplanation);
    explanation.setPosition(
        POSITION_NEW_SERIE_EXPLANATION_X,
        POSITION_NEW_SERIE_EXPLANATION_Y
    );

    inputTextSerieName = new widgets::InputTextWidget(
        POSITION_NEW_SERIE_INPUT_TEXT_X,
        POSITION_NEW_SERIE_INPUT_TEXT_Y,
        SIZE_NEW_SERIE_INPUT_TEXT,
        STRING_NEW_SERIE_DEFAULT,
        MAX_NEW_SERIE_LENGTH
    );
}

/**
 *
 */
EditorNewSerieController::~EditorNewSerieController()
{
    delete inputTextSerieName;
}

/**
 *
 */
unsigned char EditorNewSerieController::render(utils::Context* context)
{
    context->getWindow()->draw(explanation);

    inputTextSerieName->display(context);

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
                        nextControllerId = EDITOR_MAIN_MENU_CONTROLLER_ID;

                        break;
                    }
                    case sf::Keyboard::Return:
                    {
                        nextControllerId = EDITOR_SERIE_CONTROLLER_ID;

                        break;
                    }
                    default:
                    {
                        inputTextSerieName->update(&event);

                        break;
                    }
                }
            }
        }
    }

    return nextControllerId;
}
