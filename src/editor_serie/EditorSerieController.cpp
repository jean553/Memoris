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

const std::string EditorSerieController::STRING_EDITOR_SERIE_TITLE = "Serie editor";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_NEW_TEXT = "New";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_OPEN_TEXT = "Open";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_SAVE_TEXT = "Save";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_ADD_TEXT = "Add";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_EXIT_TEXT = "Exit";
const char* EditorSerieController::SERIES_DIRECTORY = "data/series";

/**
 *
 */
EditorSerieController::EditorSerieController() : Controller()
{
    titleBar.setDisplayedText(
        STRING_EDITOR_SERIE_TITLE
    );

    buttonNew.setLabel(EDITOR_SERIE_BUTTON_NEW_TEXT);
    buttonOpen.setLabel(EDITOR_SERIE_BUTTON_OPEN_TEXT);
    buttonSave.setLabel(EDITOR_SERIE_BUTTON_SAVE_TEXT);
    buttonAdd.setLabel(EDITOR_SERIE_BUTTON_ADD_TEXT);
    buttonExit.setLabel(EDITOR_SERIE_BUTTON_EXIT_TEXT);

    buttonNew.setLayout(
        EDITOR_SERIE_BUTTON_NEW_POSITION_X,
        EDITOR_SERIE_BUTTONS_POSITION_Y,
        EDITOR_SERIE_BUTTONS_WIDTH
    );

    buttonOpen.setLayout(
        EDITOR_SERIE_BUTTON_OPEN_POSITION_X,
        EDITOR_SERIE_BUTTONS_POSITION_Y,
        EDITOR_SERIE_BUTTONS_WIDTH
    );

    buttonSave.setLayout(
        EDITOR_SERIE_BUTTON_SAVE_POSITION_X,
        EDITOR_SERIE_BUTTONS_POSITION_Y,
        EDITOR_SERIE_BUTTONS_WIDTH
    );

    buttonAdd.setLayout(
        EDITOR_SERIE_BUTTON_ADD_POSITION_X,
        EDITOR_SERIE_BUTTONS_POSITION_Y,
        EDITOR_SERIE_BUTTONS_WIDTH
    );

    buttonExit.setLayout(
        EDITOR_SERIE_BUTTON_EXIT_POSITION_X,
        EDITOR_SERIE_BUTTONS_POSITION_Y,
        EDITOR_SERIE_BUTTONS_WIDTH
    );

    levelsList.setLayout(
        LEVELS_LIST_POSITION_X,
        LEVELS_LIST_POSITION_Y,
        LEVELS_LIST_WIDTH,
        LEVELS_LIST_LEVELS_NUMBER
    );

    levelsList.setStringsList(
        utils::DirReader::getAllFiles(SERIES_DIRECTORY)
    );
}

/**
 *
 */
unsigned char EditorSerieController::render(utils::Context* context)
{
    titleBar.display(context);
    buttonNew.display(context);
    buttonOpen.display(context);
    buttonSave.display(context);
    buttonAdd.display(context);
    buttonExit.display(context);
    cursor.display(context);
    levelsList.display(context);

    while(context->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Escape: {
                        nextControllerId = factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
                        break;
                    }
                }
            }
            case sf::Event::MouseButtonPressed: {
                switch(event.mouseButton.button) {
                    case sf::Mouse::Left: {
                        if(buttonExit.isMouseHover()) {
                            nextControllerId = factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
                        }
                        break;
                    }
                }
            }
        }
    }

    return nextControllerId;
}
