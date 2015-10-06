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

#include "../defines/Dimensions.hpp"

using namespace controllers;

const std::string EditorSerieController::STRING_EDITOR_SERIE_TITLE = "Serie editor";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_NEW_TEXT = "New";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_OPEN_TEXT = "Open";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_SAVE_TEXT = "Save";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_ADD_TEXT = "Add";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_EXIT_TEXT = "Exit";
const std::string EditorSerieController::STRING_OK = "OK";
const std::string EditorSerieController::STRING_CANCEL = "Cancel";
const char* EditorSerieController::SERIES_DIRECTORY = "data/series";

/**
 *
 */
EditorSerieController::EditorSerieController() : Controller()
{
    status = MAIN_MENU;

    titleBar.setDisplayedText(
        STRING_EDITOR_SERIE_TITLE
    );

    buttonNew.setLabel(EDITOR_SERIE_BUTTON_NEW_TEXT);
    buttonOpen.setLabel(EDITOR_SERIE_BUTTON_OPEN_TEXT);
    buttonSave.setLabel(EDITOR_SERIE_BUTTON_SAVE_TEXT);
    buttonAdd.setLabel(EDITOR_SERIE_BUTTON_ADD_TEXT);
    buttonExit.setLabel(EDITOR_SERIE_BUTTON_EXIT_TEXT);
    buttonNewOk.setLabel(STRING_OK);
    buttonNewCancel.setLabel(STRING_CANCEL);

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

    buttonNewOk.setLayout(
        EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_X,
        EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_Y,
        EDITOR_SERIE_BUTTONS_WIDTH
    );

    buttonNewCancel.setLayout(
        EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_X,
        EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_Y,
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

    inputTextNew.setLayout(
        POSITION_NEW_SERIE_INPUT_TEXT_X,
        POSITION_NEW_SERIE_INPUT_TEXT_Y,
        SIZE_NEW_SERIE_TEXT
    );

    serieNameLabelColor.r = constants::Colors::COLOR_WHITE_RED;
    serieNameLabelColor.g = constants::Colors::COLOR_WHITE_GREEN;
    serieNameLabelColor.b = constants::Colors::COLOR_WHITE_BLUE;
    serieNameLabelColor.a = constants::Colors::COLOR_ALPHA_FULL;

    serieNameLabelFont.loadFromFile(constants::Fonts::getTextFontPath());

    serieNameLabel.setFont(serieNameLabelFont);
    serieNameLabel.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    serieNameLabel.setColor(serieNameLabelColor);

    initializeMainMenuButtons();
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
    levelsList.display(context);

    // displays form when user creates a new serie or a new level
    if (status == NEW_SERIE || status == NEW_LEVEL) {
        buttonNewOk.display(context);
        buttonNewCancel.display(context);
        inputTextNew.display(context);
    }

    // displays the serie name if a serie is loaded
    if (status != MAIN_MENU) {
        context->getWindow()->draw(serieNameLabel);
    }

    cursor.display(context);

    while(context->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Escape: {
                        nextControllerId = factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
                        break;
                    }
                    default: {

                        // edit the new serie/level input text content if a new serie/level is creating
                        if(status == NEW_SERIE || status == NEW_LEVEL) {
                            inputTextNew.update(&event);
                        }
                    }
                }
            }
            case sf::Event::MouseButtonPressed: {
                switch(event.mouseButton.button) {
                    case sf::Mouse::Left: {
                        if(buttonExit.isMouseHover()) {
                            nextControllerId = factories::ScreenFactory::MAIN_MENU_CONTROLLER_ID;
                        }
                        // check buttons click according to current status
                        switch(status) {
                            case MAIN_MENU:
                                if(buttonNew.isMouseHover()) {

                                    switchMainMenuButtons(false);

                                    status = NEW_SERIE;
                                }
                                break;
                            case NEW_SERIE:
                                if(buttonNewOk.isMouseHover()) {

                                    switchMainMenuButtons(true);

                                    serieNameLabel.setString(inputTextNew.getText());
                                    serieNameLabel.setPosition(
                                        constants::Dimensions::SCREEN_WIDTH -
                                        serieNameLabel.getLocalBounds().width,
                                        POSITION_SERIE_NAME_LABEL_Y
                                    );

                                    status = EDIT_SERIE;
                                }
                                if(buttonNewCancel.isMouseHover()) {

                                    buttonNew.setEnable(true);
                                    buttonOpen.setEnable(true);

                                    status = MAIN_MENU;

                                    inputTextNew.clear();
                                }
                                break;
                            case EDIT_SERIE:
                                if(buttonAdd.isMouseHover()) {

                                    switchMainMenuButtons(false);

                                    status = NEW_LEVEL;

                                    inputTextNew.clear();
                                }
                            case NEW_LEVEL:
                                if(buttonNewCancel.isMouseHover()) {

                                    switchMainMenuButtons(true);

                                    status = EDIT_SERIE;

                                    inputTextNew.clear();
                                }
                                if(buttonNewOk.isMouseHover()) {

                                    switchMainMenuButtons(true);

                                    status = EDIT_SERIE;

                                    levelsList.addTextItem(inputTextNew.getText());

                                    inputTextNew.clear();
                                }

                        }
                        break;
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
void EditorSerieController::switchMainMenuButtons(bool areEnabled)
{
    buttonNew.setEnable(areEnabled);
    buttonOpen.setEnable(areEnabled);
    buttonSave.setEnable(areEnabled);
    buttonAdd.setEnable(areEnabled);
}

/**
 *
 */
void EditorSerieController::initializeMainMenuButtons()
{
    buttonNew.setEnable(true);
    buttonOpen.setEnable(true);
    buttonSave.setEnable(false);
    buttonAdd.setEnable(false);
}
