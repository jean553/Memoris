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

#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace controllers
{

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
NewGameController::NewGameController(utils::Context& context) :
    inputTextGameName(),
    Controller()
{
    title.setFont(memoris::fonts::FontsManager::get().getTitleFont());
    title.setString(STRING_NEW_GAME_TITLE);
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(memoris::colors::ColorsManager::get().getColorLightBlue());
    title.setPosition(
        POSITION_NEW_GAME_TITLE_X,
        POSITION_NEW_GAME_TITLE_Y
    );

    explanation.setFont(memoris::fonts::FontsManager::get().getTextFont());
    explanation.setString(STRING_NEW_GAME_EXPLANATION);
    explanation.setCharacterSize(memoris::fonts::TEXT_SIZE);
    explanation.setColor(memoris::colors::ColorsManager::get().getColorWhite());
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
unsigned short NewGameController::render(utils::Context& context)
{
    context.getSfmlWindow().draw(title);
    context.getSfmlWindow().draw(explanation);

    inputTextGameName.display();

    nextControllerId = animateScreenTransition();

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {

                expectedControllerId =
                    MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Return:
            {

                expectedControllerId =
                    SERIE_MAIN_MENU_CONTROLLER_ID;

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

}
}
