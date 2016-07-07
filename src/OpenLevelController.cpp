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
 * @file OpenLevelController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenLevelController.hpp"

#include "DirReader.hpp"
#include "Screens.hpp"
#include "Messages.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace controllers
{

const std::string OpenLevelController::STRING_OPEN_LEVEL_TITLE = "Open level";
const std::string OpenLevelController::STRING_ALREADY_ADDED_ERROR_MESSAGE =
    "Already added !";

const unsigned short OpenLevelController::LEVELS_LIST_WIDTH = 1580;
const unsigned short OpenLevelController::LEVELS_LIST_POSITION_X = 10;
const unsigned short OpenLevelController::LEVELS_LIST_POSITION_Y = 130;
const unsigned short OpenLevelController::LEVELS_LIST_LEVELS_NUMBER = 18;

const float OpenLevelController::ERROR_MESSAGE_POSITION_X = 1300;
const float OpenLevelController::ERROR_MESSAGE_POSITION_Y = 40;

/**
 *
 */
OpenLevelController::OpenLevelController() :
    Controller()
{
    errorAlreadyAddedLevel = false;

    titleBar.setDisplayedText(
        STRING_OPEN_LEVEL_TITLE
    );

    levelsList.setLayout(
        LEVELS_LIST_POSITION_X,
        LEVELS_LIST_POSITION_Y,
        LEVELS_LIST_WIDTH,
        LEVELS_LIST_LEVELS_NUMBER
    );

    levelsList.setStringsList(
        utils::DirReader::getAllFiles(
            "data/levels",
            ".level"
        )
    );

    errorLabel.setFont(memoris::fonts::FontsManager::get().getTextFont());
    errorLabel.setCharacterSize(memoris::fonts::INFORMATION_SIZE);
    errorLabel.setColor(memoris::colors::ColorsManager::get().getColorRed());
    errorLabel.setString(STRING_ALREADY_ADDED_ERROR_MESSAGE);
    errorLabel.setPosition(
        ERROR_MESSAGE_POSITION_X,
        ERROR_MESSAGE_POSITION_Y
    );
}

/**
 *
 */
unsigned short OpenLevelController::render()
{
    titleBar.display();
    levelsList.display();
    cursor.display();

    if (errorAlreadyAddedLevel)
    {
        utils::Context::get().getSfmlWindow().draw(errorLabel);
    }

    nextControllerId = animateScreenTransition();

    while(utils::Context::get().getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                changeNextControllerId();
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                if (levelsList.isMouseHover())
                {
                    std::vector<std::string> stringsList =
                        utils::Context::get().getStringsList();

                    /* do not add the level if already in the list
                       TODO: could be refactored if addStringIntoStringsList
                       return a boolean... */
                    if (
                        std::find(
                            stringsList.begin(),
                            stringsList.end(),
                            levelsList.getSelectedItemValue()) !=
                        stringsList.end()
                    )
                    {
                        errorAlreadyAddedLevel = true;

                        continue;
                    }

                    utils::Context::get().addStringIntoStringsList(
                        levelsList.getSelectedItemValue()
                    );

                    changeNextControllerId();
                }
                levelsList.scroll();
            }
            }
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void OpenLevelController::changeNextControllerId()
{
    expectedControllerId =
        utils::Context::get().getMessageByName(
            constants::Messages::PREVIOUS_CONTROLLER_MESSAGE
        ) == constants::Screens::SERIE_EDITOR_SCREEN_NAME ?
        EDITOR_SERIE_CONTROLLER_ID :
        EDITOR_LEVEL_CONTROLLER_ID;
}

}
}
