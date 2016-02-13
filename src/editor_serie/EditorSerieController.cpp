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
#include "../defines/Window.hpp"
#include "../defines/Positions.hpp"
#include "../defines/Directories.hpp"
#include "../defines/Extensions.hpp"
#include "../defines/Fonts.hpp"
#include "../defines/Colors.hpp"

#include "../utils/DirReader.hpp"
#include "../utils/StringsListsUtils.hpp"
#include "../utils/FileWriter.hpp"

#include "../utils/ControllerFactory.hpp"

using namespace controllers;

const std::string EditorSerieController::STRING_EDITOR_SERIE_TITLE = "Serie editor";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_NEW_TEXT = "New";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_OPEN_TEXT = "Open";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_SAVE_TEXT = "Save";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_ADD_TEXT = "Add";
const std::string EditorSerieController::EDITOR_SERIE_BUTTON_EXIT_TEXT = "Exit";
const std::string EditorSerieController::STRING_OK = "OK";
const std::string EditorSerieController::STRING_CANCEL = "Cancel";
const std::string EditorSerieController::STRING_NEW_SERIE_ERROR = "Cannot create the new serie...";
const std::string EditorSerieController::STRING_NEW_LEVEL_ERROR = "The level already exists !";

const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_EXIT_POSITION_X = 1390;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_NEW_POSITION_X = 10;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_OPEN_POSITION_X = 240;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_SAVE_POSITION_X = 470;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_ADD_POSITION_X = 700;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_X = 380;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_Y = 175;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_X = 590;
const unsigned short EditorSerieController::EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_Y = 175;
const unsigned short EditorSerieController::LEVELS_LIST_POSITION_X = 10;
const unsigned short EditorSerieController::LEVELS_LIST_POSITION_Y = 250;
const unsigned short EditorSerieController::LEVELS_LIST_WIDTH = 1580;
const unsigned short EditorSerieController::LEVELS_LIST_LEVELS_NUMBER = 15;
const unsigned short EditorSerieController::POSITION_NEW_SERIE_INPUT_TEXT_X = 10;
const unsigned short EditorSerieController::POSITION_NEW_SERIE_INPUT_TEXT_Y = 175;
const unsigned short EditorSerieController::SIZE_NEW_SERIE_TEXT = 350;
const unsigned short EditorSerieController::ERROR_MESSAGE_POSITION_X = 800;
const unsigned short EditorSerieController::ERROR_MESSAGE_POSITION_Y = 200;

/**
 *
 */
EditorSerieController::EditorSerieController() : Controller()
{
    errorNewSerie = false;
    errorNewLevel = false;

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
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonOpen.setLayout(
        EDITOR_SERIE_BUTTON_OPEN_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonSave.setLayout(
        EDITOR_SERIE_BUTTON_SAVE_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonAdd.setLayout(
        EDITOR_SERIE_BUTTON_ADD_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonExit.setLayout(
        EDITOR_SERIE_BUTTON_EXIT_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonNewOk.setLayout(
        EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_X,
        EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonNewCancel.setLayout(
        EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_X,
        EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    levelsList.setLayout(
        LEVELS_LIST_POSITION_X,
        LEVELS_LIST_POSITION_Y,
        LEVELS_LIST_WIDTH,
        LEVELS_LIST_LEVELS_NUMBER
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

    serieNameLabelUnsavedColor.r = constants::Colors::COLOR_GREY_RED;
    serieNameLabelUnsavedColor.g = constants::Colors::COLOR_GREY_GREEN;
    serieNameLabelUnsavedColor.b = constants::Colors::COLOR_GREY_BLUE;
    serieNameLabelUnsavedColor.a = constants::Colors::COLOR_ALPHA_FULL;

    errorLabelColor.r = constants::Colors::COLOR_RED_RED;
    errorLabelColor.g = constants::Colors::COLOR_RED_GREEN;
    errorLabelColor.b = constants::Colors::COLOR_RED_BLUE;
    errorLabelColor.a = constants::Colors::COLOR_ALPHA_FULL;

    serieNameLabelFont.loadFromFile(constants::Fonts::getTextFontPath());

    serieNameLabel.setFont(serieNameLabelFont);
    serieNameLabel.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    serieNameLabel.setColor(serieNameLabelUnsavedColor);

    errorLabel.setFont(serieNameLabelFont);
    errorLabel.setCharacterSize(constants::Fonts::SIZE_MESSAGE_FONT);
    errorLabel.setColor(errorLabelColor);
    errorLabel.setString(STRING_NEW_SERIE_ERROR);
    errorLabel.setPosition(
        ERROR_MESSAGE_POSITION_X,
        ERROR_MESSAGE_POSITION_Y
    );

    levelErrorLabel.setFont(serieNameLabelFont);
    levelErrorLabel.setCharacterSize(constants::Fonts::SIZE_MESSAGE_FONT);
    levelErrorLabel.setColor(errorLabelColor);
    levelErrorLabel.setString(STRING_NEW_LEVEL_ERROR);
    levelErrorLabel.setPosition(
        ERROR_MESSAGE_POSITION_X,
        ERROR_MESSAGE_POSITION_Y
    );

    initializeMainMenuButtons();
}

/**
 *
 */
unsigned short EditorSerieController::render(utils::Context* pContext)
{
    titleBar.display(pContext);
    buttonNew.display(pContext);
    buttonOpen.display(pContext);
    buttonSave.display(pContext);
    buttonAdd.display(pContext);
    buttonExit.display(pContext);
    levelsList.display(pContext);

    // displays form when user creates a new serie or a new level
    if (status == NEW_SERIE || status == NEW_LEVEL) {
        buttonNewOk.display(pContext);
        buttonNewCancel.display(pContext);
        inputTextNew.display(pContext);
    }

    // displays the serie name if a serie is loaded
    if (status != MAIN_MENU) {
        pContext->getWindow()->draw(serieNameLabel);
    }

    // displays the error message if an error just occured
    if (errorNewSerie) {
        pContext->getWindow()->draw(errorLabel);
    } else if (errorNewLevel) {
        pContext->getWindow()->draw(levelErrorLabel);
    }

    cursor.display(pContext);

    while(pContext->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Escape: {
                        nextControllerId = factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
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
                            nextControllerId = factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
                        }
                        // check buttons click according to current status
                        switch(status) {
                            case MAIN_MENU:
                                if(buttonNew.isMouseHover()) {

                                    switchMainMenuButtons(false);

                                    status = NEW_SERIE;
                                }
                                if(buttonOpen.isMouseHover()) {
                                    nextControllerId =
                                        factories::ControllerFactory::OPEN_SERIE_CONTROLLER_ID;
                                }
                                break;
                            case NEW_SERIE:
                                if(buttonNewOk.isMouseHover()) {

                                    if (serieExists(inputTextNew.getText())) {
                                        errorNewSerie = true;
                                        continue;
                                    }

                                    serie.setName(inputTextNew.getText());

                                    errorNewSerie = false;

                                    serieNameLabel.setString(inputTextNew.getText());
                                    serieNameLabel.setPosition(
                                        constants::Window::WIDTH -
                                        serieNameLabel.getLocalBounds().width,
                                        constants::Dimensions::POSITION_NAME_LABEL_Y
                                    );

                                    switchMainMenuButtonsToEditSerieStatus();

                                    status = EDIT_SERIE;
                                }
                                if(buttonNewCancel.isMouseHover()) {

                                    buttonNew.setEnable(true);
                                    buttonOpen.setEnable(true);

                                    errorNewSerie = false;

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
                                if(buttonSave.isMouseHover()) {

                                    if (!serieExists(serie.getName())) {
                                        utils::FileWriter::createFile(
                                            constants::Directories::getSeriesDirectoryPath() +
                                            serie.getName() +
                                            constants::Extensions::getSeriesExtension()
                                        );
                                    }

                                    //TODO: rewrite serie file content

                                    displaySavedSerieName(true);
                                }
                            case NEW_LEVEL:
                                if(buttonNewCancel.isMouseHover()) {

                                    errorNewLevel = false;

                                    status = EDIT_SERIE;

                                    switchMainMenuButtonsToEditSerieStatus();

                                    inputTextNew.clear();

                                    buttonAdd.setEnable(true);
                                    buttonSave.setEnable(false);
                                }
                                if(buttonNewOk.isMouseHover()) {

                                    // do not add the level if already in the loaded serie
                                    if (utils::StringsListsUtils::stringsListContainsString(
                                                levelsList.getStringsList(),
                                                inputTextNew.getText()
                                            )) {
                                        errorNewLevel = true;
                                        continue;
                                    }

                                    errorNewLevel = false;

                                    status = EDIT_SERIE;

                                    switchMainMenuButtonsToEditSerieStatus();

                                    levelsList.addTextItem(inputTextNew.getText());

                                    inputTextNew.clear();

                                    displaySavedSerieName(false);
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
void EditorSerieController::switchMainMenuButtonsToEditSerieStatus()
{
    buttonNew.setEnable(false);
    buttonOpen.setEnable(false);
    buttonSave.setEnable(true);
    buttonAdd.setEnable(true);
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

/**
 *
 */
void EditorSerieController::displaySavedSerieName(bool saved)
{
    if (saved) {
        serieNameLabel.setColor(serieNameLabelColor);
    } else {
        serieNameLabel.setColor(serieNameLabelUnsavedColor);
    }

    buttonSave.setEnable(!saved);
}

/**
 *
 */
bool EditorSerieController::serieExists(std::string serieName)
{
    std::string seriesDirectory(constants::Directories::getSeriesDirectoryPath());
    std::string seriesExtension(constants::Extensions::getSeriesExtension());

    std::vector<std::string> seriesNames = utils::DirReader::getAllFiles(
            seriesDirectory.c_str(),
            seriesExtension.c_str()
                                           );

    return utils::StringsListsUtils::stringsListContainsString(seriesNames, serieName);
}
