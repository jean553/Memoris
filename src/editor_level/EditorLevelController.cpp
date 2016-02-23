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
 * Editor of levels.
 *
 * @file EditorLevelController.cpp
 * @brief levels editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorLevelController.hpp"

#include "Positions.hpp"
#include "Dimensions.hpp"
#include "Window.hpp"
#include "Colors.hpp"
#include "Fonts.hpp"
#include "Directories.hpp"
#include "Extensions.hpp"
#include "DirReader.hpp"
#include "StringsListsUtils.hpp"
#include "FileWriter.hpp"
#include "ControllerFactory.hpp"

using namespace controllers;

const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_EXIT_TEXT = "Exit";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_NEW_TEXT = "New";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_OPEN_TEXT = "Open";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_SAVE_TEXT = "Save";

const std::string EditorLevelController::STRING_EDITOR_LEVEL_TITLE = "Level editor";

const std::string EditorLevelController::STRING_NEW_LEVEL_ERROR = "The level already exists !";

const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTONS_POSITION_X = 1390;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_NEW_POSITION_Y = 170;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y = 240;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y = 310;

const unsigned short EditorLevelController::LEVEL_POSITION_X = 5;
const unsigned short EditorLevelController::LEVEL_POSITION_Y = 90;

const unsigned short EditorLevelController::CELL_SELECTOR_POSITION_X = 1050;
const unsigned short EditorLevelController::CELL_SELECTOR_POSITION_Y = 90;

const unsigned short EditorLevelController::ERROR_MESSAGE_POSITION_X = 780;
const unsigned short EditorLevelController::ERROR_MESSAGE_POSITION_Y = 30;

const unsigned short EditorLevelController::POSITION_NEW_LEVEL_INPUT_TEXT_X = 1230;
const unsigned short EditorLevelController::POSITION_NEW_LEVEL_INPUT_TEXT_Y = 10;

const unsigned short EditorLevelController::SIZE_NEW_LEVEL_TEXT = 350;

/**
 *
 */
EditorLevelController::EditorLevelController() : Controller(), level(LEVEL_POSITION_X, LEVEL_POSITION_Y)
{
    titleBar.setDisplayedText(
        STRING_EDITOR_LEVEL_TITLE
    );

    buttonExit.setLabel(EDITOR_LEVEL_BUTTON_EXIT_TEXT);
    buttonNew.setLabel(EDITOR_LEVEL_BUTTON_NEW_TEXT);
    buttonOpen.setLabel(EDITOR_LEVEL_BUTTON_OPEN_TEXT);
    buttonSave.setLabel(EDITOR_LEVEL_BUTTON_SAVE_TEXT);

    buttonExit.setLayout(
        LEVEL_EDITOR_BUTTONS_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonNew.setLayout(
        LEVEL_EDITOR_BUTTONS_POSITION_X,
        LEVEL_EDITOR_BUTTON_NEW_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonOpen.setLayout(
        LEVEL_EDITOR_BUTTONS_POSITION_X,
        LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonSave.setLayout(
        LEVEL_EDITOR_BUTTONS_POSITION_X,
        LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    levelNameLabelColor.r = constants::Colors::COLOR_WHITE_RED;
    levelNameLabelColor.g = constants::Colors::COLOR_WHITE_GREEN;
    levelNameLabelColor.b = constants::Colors::COLOR_WHITE_BLUE;
    levelNameLabelColor.a = constants::Colors::COLOR_ALPHA_FULL;

    levelNameLabelUnsavedColor.r = constants::Colors::COLOR_GREY_RED;
    levelNameLabelUnsavedColor.g = constants::Colors::COLOR_GREY_GREEN;
    levelNameLabelUnsavedColor.b = constants::Colors::COLOR_GREY_BLUE;
    levelNameLabelUnsavedColor.a = constants::Colors::COLOR_ALPHA_FULL;

    errorLabelColor.r = constants::Colors::COLOR_RED_RED;
    errorLabelColor.g = constants::Colors::COLOR_RED_GREEN;
    errorLabelColor.b = constants::Colors::COLOR_RED_BLUE;
    errorLabelColor.a = constants::Colors::COLOR_ALPHA_FULL;

    levelNameLabelFont.loadFromFile(constants::Fonts::getTextFontPath());

    levelNameLabel.setFont(levelNameLabelFont);
    levelNameLabel.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    levelNameLabel.setColor(levelNameLabelUnsavedColor);

    errorLabel.setFont(levelNameLabelFont);
    errorLabel.setCharacterSize(constants::Fonts::SIZE_MESSAGE_FONT);
    errorLabel.setColor(errorLabelColor);
    errorLabel.setString(STRING_NEW_LEVEL_ERROR);
    errorLabel.setPosition(
        ERROR_MESSAGE_POSITION_X,
        ERROR_MESSAGE_POSITION_Y
    );

    inputTextNew.setLayout(
        POSITION_NEW_LEVEL_INPUT_TEXT_X,
        POSITION_NEW_LEVEL_INPUT_TEXT_Y,
        SIZE_NEW_LEVEL_TEXT
    );

    cellSelector.setPosition(
        CELL_SELECTOR_POSITION_X,
        CELL_SELECTOR_POSITION_Y
    );

    status = MAIN_MENU;

    levelAlreadyExists = false;

    buttonSave.setEnable(false);
}

/**
 *
 */
unsigned short EditorLevelController::render(utils::Context* pContext)
{
    titleBar.display(pContext);
    buttonExit.display(pContext);
    buttonNew.display(pContext);
    buttonOpen.display(pContext);
    buttonSave.display(pContext);

    level.displayAllCells(pContext);
    cellSelector.display(pContext);

    // displays the input text line for new level
    if (status == NEW_LEVEL) {
        inputTextNew.display(pContext);
    }

    // displays the name of the level if one level is being edited
    else if (status == EDIT_LEVEL) {
        pContext->getWindow()->draw(levelNameLabel);
    }

    // displays the error message if the level name is being edited and an error occured
    if (levelAlreadyExists) {
        pContext->getWindow()->draw(errorLabel);
    }

    cursor.display(pContext);

    while(pContext->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Return: {

                        if (status == NEW_LEVEL) {

                            if (levelExists(inputTextNew.getText())) {
                                levelAlreadyExists = true;
                                continue;
                            }

                            levelNameLabel.setString(
                                inputTextNew.getText()
                            );
                            levelNameLabel.setPosition(
                                constants::Window::WIDTH -
                                levelNameLabel.getLocalBounds().width,
                                constants::Dimensions::POSITION_NAME_LABEL_Y
                            );

                            level.setName(inputTextNew.getText());

                            buttonSave.setEnable(true);

                            levelAlreadyExists = false;
                            status = EDIT_LEVEL;
                        }
                    }
                    default: {

                        if (status == NEW_LEVEL) {
                            inputTextNew.update(&event);
                        }
                    }
                }
            }
            case sf::Event::MouseButtonPressed: {
                switch(event.mouseButton.button) {
                    case sf::Mouse::Left: {
                        switch(status) {
                            case EDIT_LEVEL: {

                                if(buttonSave.isMouseHover()) {
                                    if (!levelExists(inputTextNew.getText())) {
                                        utils::FileWriter::createFile(
                                            constants::Directories::LEVELS_DIRECTORY_PATH +
                                            level.getName() +
                                            constants::Extensions::LEVELS_EXTENSION
                                        );
                                    }

                                    //TODO: rewrite file content

                                    displaySavedLevelName(true);

                                    buttonSave.setEnable(false);
                                }
                            }
                            default: {
                                if(buttonExit.isMouseHover()) {
                                    nextControllerId =
                                        factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
                                }
                                else if(buttonNew.isMouseHover()) {
                                    status = NEW_LEVEL;
                                }
                                else if(cellSelector.isMouseHover()) {
                                    cellSelector.selectCellOnClick();
                                }
                            }
                        break;
                        }
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
void EditorLevelController::displaySavedLevelName(bool saved)
{
    if (saved) {
        levelNameLabel.setColor(levelNameLabelColor);
    } else {
        levelNameLabel.setColor(levelNameLabelUnsavedColor);
    }
}

/**
 *
 */
bool EditorLevelController::levelExists(std::string levelName)
{
    std::string levelsDirectory =
        constants::Directories::LEVELS_DIRECTORY_PATH;

    std::string levelsExtension =
        constants::Extensions::LEVELS_EXTENSION;

    std::vector<std::string> levelsName =
        utils::DirReader::getAllFiles(
            levelsDirectory.c_str(),
            levelsExtension.c_str()
        );

    return utils::StringsListsUtils::stringsListContainsString(
        levelsName,
        levelName
    );
}
