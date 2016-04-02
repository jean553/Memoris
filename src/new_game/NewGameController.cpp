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

#include "ControllerFactory.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"

using namespace controllers;

const std::string NewGameController::STRING_NEW_GAME_TITLE = "New game";
const std::string NewGameController::STRING_NEW_GAME_EXPLANATION = "Your name :";
const std::string NewGameController::STRING_NAME_DEFAULT = "";

const unsigned short NewGameController::SIZE_NAME_INPUT_TEXT = 600;

const unsigned short NewGameController::POSITION_NEW_GAME_TITLE_X = 620;
const unsigned short NewGameController::POSITION_NEW_GAME_TITLE_Y = 200;

const unsigned short NewGameController::POSITION_NEW_GAME_EXPLANATION_X = 645;
const unsigned short NewGameController::POSITION_NEW_GAME_EXPLANATION_Y = 380;

const unsigned short NewGameController::POSITION_NAME_INPUT_TEXT_X = 500;
const unsigned short NewGameController::POSITION_NAME_INPUT_TEXT_Y = 450;

const unsigned short NewGameController::MAX_NAME_LENGTH = 15;

/**
 *
 */
NewGameController::NewGameController() : Controller()
{
    fontTitle.loadFromFile(constants::Fonts::getTitleFontPath());
    fontExplanation.loadFromFile(constants::Fonts::getTextFontPath());

    colorTitle.r = constants::Colors::COLOR_LIGHT_BLUE_RED;
    colorTitle.g = constants::Colors::COLOR_LIGHT_BLUE_GREEN;
    colorTitle.b = constants::Colors::COLOR_LIGHT_BLUE_BLUE;
    colorTitle.a = constants::Colors::COLOR_ALPHA_FULL;

    colorExplanation.r = constants::Colors::COLOR_WHITE_RED;
    colorExplanation.g = constants::Colors::COLOR_WHITE_GREEN;
    colorExplanation.b = constants::Colors::COLOR_WHITE_BLUE;
    colorExplanation.a = constants::Colors::COLOR_ALPHA_FULL;

    title.setFont(fontTitle);
    title.setString(STRING_NEW_GAME_TITLE);
    title.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    title.setColor(colorTitle);
    title.setPosition(
        POSITION_NEW_GAME_TITLE_X,
        POSITION_NEW_GAME_TITLE_Y
    );

    explanation.setFont(fontExplanation);
    explanation.setString(STRING_NEW_GAME_EXPLANATION);
    explanation.setCharacterSize(constants::Fonts::SIZE_TEXT_FONT);
    explanation.setColor(colorExplanation);
    explanation.setPosition(
        POSITION_NEW_GAME_EXPLANATION_X,
        POSITION_NEW_GAME_EXPLANATION_Y
    );

    inputTextGameName.setLayout(
        POSITION_NAME_INPUT_TEXT_X,
        POSITION_NAME_INPUT_TEXT_Y,
        SIZE_NAME_INPUT_TEXT
    );

    inputTextGameName.setMaximumCharacters(
        MAX_NAME_LENGTH
    );

    inputTextGameName.setDisplayedText(
        STRING_NAME_DEFAULT
    );
}


/**
 *
 */
unsigned short NewGameController::render(utils::Context* pContext)
{
    pContext->getWindow()->draw(title);
    pContext->getWindow()->draw(explanation);

    inputTextGameName.display(pContext);

    while(pContext->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {

                nextControllerId =
                    factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {

                inputTextGameName.update(&event);

                break;
            }
            }
        }
        }
    }

    return nextControllerId;
}
