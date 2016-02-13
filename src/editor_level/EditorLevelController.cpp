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

#include "../defines/Positions.hpp"
#include "../defines/Dimensions.hpp"
#include "../defines/Window.hpp"
#include "../defines/Colors.hpp"
#include "../defines/Fonts.hpp"

#include "../utils/ControllerFactory.hpp"

using namespace controllers;

const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_EXIT_TEXT = "Exit";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_NEW_TEXT = "New";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_OPEN_TEXT = "Open";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_SAVE_TEXT = "Save";
const std::string EditorLevelController::STRING_EDITOR_LEVEL_TITLE = "Level editor";
const std::string EditorLevelController::DEFAULT_LEVEL_NAME = "untitled";

const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTONS_POSITION_X = 1390;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_NEW_POSITION_Y = 170;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y = 240;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y = 310;
const unsigned short EditorLevelController::LEVEL_POSITION_X = 5;
const unsigned short EditorLevelController::LEVEL_POSITION_Y = 90;

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

    levelNameLabelFont.loadFromFile(constants::Fonts::getTextFontPath());

    levelNameLabel.setFont(levelNameLabelFont);
    levelNameLabel.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    levelNameLabel.setColor(levelNameLabelColor);
    levelNameLabel.setString(DEFAULT_LEVEL_NAME);
    levelNameLabel.setPosition(
        constants::Window::WIDTH -
        levelNameLabel.getLocalBounds().width,
        constants::Dimensions::POSITION_NAME_LABEL_Y
    );
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

    //TODO: displays only the level name when a level is loaded
    pContext->getWindow()->draw(levelNameLabel);

    cursor.display(pContext);

    while(pContext->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::MouseButtonPressed: {
                switch(event.mouseButton.button) {
                    case sf::Mouse::Left: {
                        if(buttonExit.isMouseHover()) {
                            nextControllerId = factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
                        }
                    }
                }
            }
        }
    }

    return nextControllerId;
}
