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
#include "Screens.hpp"
#include "Messages.hpp"
#include "CellsFilter.hpp"
#include "CellsFileRepresentations.hpp"

using namespace controllers;

const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_EXIT_TEXT = "Exit";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_NEW_TEXT = "New";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_OPEN_TEXT = "Open";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_SAVE_TEXT = "Save";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_NEXT_FLOOR_TEXT = "Up";
const std::string EditorLevelController::EDITOR_LEVEL_BUTTON_PREVIOUS_FLOOR_TEXT = "Down";
const std::string EditorLevelController::STRING_EDITOR_LEVEL_TITLE = "Level editor";
const std::string EditorLevelController::STRING_NEW_LEVEL_ERROR = "The level already exists !";
const std::string EditorLevelController::STRING_SAVE_LEVEL_ERROR = "The level cannot be saved !";
const std::string EditorLevelController::STRING_FLOOR_PREFIX_LABEL = "Floor";

const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTONS_POSITION_X = 1390;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_NEW_POSITION_Y = 170;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y = 240;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y = 310;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_LEVEL_UP_POSITION_Y = 760;
const unsigned short EditorLevelController::LEVEL_EDITOR_BUTTON_LEVEL_DOWN_POSITION_Y = 830;
const unsigned short EditorLevelController::LEVEL_POSITION_X = 5;
const unsigned short EditorLevelController::LEVEL_POSITION_Y = 90;
const unsigned short EditorLevelController::CELL_SELECTOR_POSITION_X = 1050;
const unsigned short EditorLevelController::CELL_SELECTOR_POSITION_Y = 90;
const unsigned short EditorLevelController::ERROR_MESSAGE_POSITION_X = 780;
const unsigned short EditorLevelController::ERROR_MESSAGE_POSITION_Y = 30;
const unsigned short EditorLevelController::POSITION_NEW_LEVEL_INPUT_TEXT_X = 1230;
const unsigned short EditorLevelController::POSITION_NEW_LEVEL_INPUT_TEXT_Y = 10;
const unsigned short EditorLevelController::SIZE_NEW_LEVEL_TEXT = 350;

const float EditorLevelController::FLOOR_SELECTION_FRAME_HORIZONTAL_SIZE = 210;
const float EditorLevelController::FLOOR_SELECTION_FRAME_VERTICAL_SIZE = 245;
const float EditorLevelController::FLOOR_SELECTION_FRAME_HORIZONTAL_POSITION = 1385;
const float EditorLevelController::FLOOR_SELECTION_FRAME_VERTICAL_POSITION = 650;
const float EditorLevelController::FLOOR_PREFIX_LABEL_HORIZONTAL_POSITION = 1440;
const float EditorLevelController::FLOOR_PREFIX_LABEL_VERTICAL_POSITION = 650;
const float EditorLevelController::FLOOR_LABEL_HORIZONTAL_POSITION = 1465;
const float EditorLevelController::FLOOR_LABEL_VERTICAL_POSITION = 670;

/**
 *
 */
EditorLevelController::EditorLevelController() : Controller(), level(LEVEL_POSITION_X, LEVEL_POSITION_Y)
{
    currentFloor = 0;

    titleBar.setDisplayedText(
        STRING_EDITOR_LEVEL_TITLE
    );

    buttonExit.setLabel(EDITOR_LEVEL_BUTTON_EXIT_TEXT);
    buttonNew.setLabel(EDITOR_LEVEL_BUTTON_NEW_TEXT);
    buttonOpen.setLabel(EDITOR_LEVEL_BUTTON_OPEN_TEXT);
    buttonSave.setLabel(EDITOR_LEVEL_BUTTON_SAVE_TEXT);
    buttonNextFloor.setLabel(EDITOR_LEVEL_BUTTON_NEXT_FLOOR_TEXT);
    buttonPreviousFloor.setLabel(EDITOR_LEVEL_BUTTON_PREVIOUS_FLOOR_TEXT);

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

    buttonNextFloor.setLayout(
        LEVEL_EDITOR_BUTTONS_POSITION_X,
        LEVEL_EDITOR_BUTTON_LEVEL_UP_POSITION_Y,
        constants::Dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonPreviousFloor.setLayout(
        LEVEL_EDITOR_BUTTONS_POSITION_X,
        LEVEL_EDITOR_BUTTON_LEVEL_DOWN_POSITION_Y,
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

    floorPrefixLabel.setFont(levelNameLabelFont);
    floorPrefixLabel.setCharacterSize(constants::Fonts::SIZE_MESSAGE_FONT);
    floorPrefixLabel.setColor(levelNameLabelColor);
    floorPrefixLabel.setString(STRING_FLOOR_PREFIX_LABEL);
    floorPrefixLabel.setPosition(
        FLOOR_PREFIX_LABEL_HORIZONTAL_POSITION,
        FLOOR_PREFIX_LABEL_VERTICAL_POSITION
    );

    floorLabel.setFont(levelNameLabelFont);
    floorLabel.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    floorLabel.setColor(levelNameLabelColor);
    floorLabel.setString(std::to_string(currentFloor + 1));
    floorLabel.setPosition(
        FLOOR_LABEL_HORIZONTAL_POSITION,
        FLOOR_LABEL_VERTICAL_POSITION
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

    floorSelectionFrame.setColor(
        constants::Colors::COLOR_WHITE_RED,
        constants::Colors::COLOR_WHITE_GREEN,
        constants::Colors::COLOR_WHITE_BLUE
    );
    floorSelectionFrame.setSize(
        FLOOR_SELECTION_FRAME_HORIZONTAL_SIZE,
        FLOOR_SELECTION_FRAME_VERTICAL_SIZE
    );
    floorSelectionFrame.setPosition(
        FLOOR_SELECTION_FRAME_HORIZONTAL_POSITION,
        FLOOR_SELECTION_FRAME_VERTICAL_POSITION
    );

    status = MAIN_MENU;

    levelAlreadyExists = false;
    saveLevelError = false;

    buttonSave.setEnable(false);
    buttonNextFloor.setEnable(false);
    buttonPreviousFloor.setEnable(false);

    level.loadCells();
}

/**
 *
 */
uint8_t EditorLevelController::render(utils::Context* pContext)
{
    titleBar.display(pContext);
    buttonExit.display(pContext);
    buttonNew.display(pContext);
    buttonOpen.display(pContext);
    buttonSave.display(pContext);
    buttonNextFloor.display(pContext);
    buttonPreviousFloor.display(pContext);

    level.displayAllCellsByFloor(
        pContext,
        currentFloor
    );

    cellSelector.display(pContext);
    floorSelectionFrame.display(pContext);

    pContext->getWindow()->draw(floorPrefixLabel);
    pContext->getWindow()->draw(floorLabel);

    /* displays the input text line for new level */
    if (status == NEW_LEVEL)
    {
        inputTextNew.display(pContext);
    }

    /* displays the name of the level if one level is being edited */
    else if (status == EDIT_LEVEL)
    {
        pContext->getWindow()->draw(levelNameLabel);
    }

    /* displays the error message if the level name is being edited and an error occured */
    if (levelAlreadyExists)
    {
        errorLabel.setString(STRING_NEW_LEVEL_ERROR);
    }

    /* displays an error message if the file cannot be saved */
    if (saveLevelError)
    {
        errorLabel.setString(STRING_SAVE_LEVEL_ERROR);
    }

    if (levelAlreadyExists || saveLevelError)
    {
        pContext->getWindow()->draw(errorLabel);
    }

    cursor.display(pContext);

    nextControllerId = animateScreenTransition(pContext);

    while(pContext->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Return:
            {
                if (status == NEW_LEVEL)
                {
                    if (levelExists(inputTextNew.getText()))
                    {
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
            default:
            {

                if (status == NEW_LEVEL)
                {
                    inputTextNew.update(&event);
                }
            }
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                switch(status)
                {
                case EDIT_LEVEL:
                {
                    if(buttonSave.isMouseHover())
                    {
                        saveLevelError = !utils::FileWriter::writeFile(
                                             constants::Directories::LEVELS_DIRECTORY_PATH +
                                             level.getName() +
                                             constants::Extensions::LEVELS_EXTENSION,
                                             level.getCellsAsString()
                                         );

                        displaySavedLevelName(true);

                        buttonSave.setEnable(false);
                        buttonNextFloor.setEnable(true);
                        buttonPreviousFloor.setEnable(true);
                    }
                    else if (buttonNextFloor.isMouseHover())
                    {
                        updateFloorNumber(1);
                    }
                    else if (buttonPreviousFloor.isMouseHover())
                    {
                        updateFloorNumber(-1);
                    }
                }
                default:
                {
                    if(buttonExit.isMouseHover())
                    {
                        pContext->removeAllMessages();

                        expectedControllerId =
                            factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;
                    }
                    else if(buttonNew.isMouseHover())
                    {
                        status = NEW_LEVEL;
                    }
                    else if(buttonOpen.isMouseHover())
                    {

                        pContext->addMessageByName(
                            constants::Messages::PREVIOUS_CONTROLLER_MESSAGE,
                            constants::Screens::LEVEL_EDITOR_SCREEN_NAME
                        );

                        expectedControllerId =
                            factories::ControllerFactory::OPEN_LEVEL_CONTROLLER_ID;
                    }
                    else if(cellSelector.isMouseHover() && status != MAIN_MENU)
                    {
                        cellSelector.selectCellOnClick();
                        status = EDIT_LEVEL;
                    }
                    else if(level.isMouseHover(currentFloor) && status != MAIN_MENU)
                    {
                        /* check if the cell can be added at the given location */
                        if (!currEditIsAllowed())
                        {
                            continue;
                        }

                        updateOneCell(
                            level.getSelectedCellPointer(),
                            cellSelector.getSelectedNewCellPointer()
                        );

                        /* for some new cells, other cells have to be updated */
                        updtLevelForSpecCells(
                            level.getSelectedCellPointer(),
                            cellSelector.getSelectedNewCellPointer()
                        );

                        displaySavedLevelName(false);
                        buttonSave.setEnable(true);
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
    if (saved)
    {
        levelNameLabel.setColor(levelNameLabelColor);
    }
    else
    {
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

/**
 *
 */
void EditorLevelController::updateOneCell(
    entities::Cell* pSelectedCell,
    entities::Cell* pCellsSelectorCell
)
{
    if (
        pSelectedCell == NULL ||
        pCellsSelectorCell == NULL
    )
    {
        return;
    }

    if (
        !utils::CellsFilter::canBeAdded(
            level.getCellsAsString(),
            pCellsSelectorCell->getStringRepresentation(),
            pSelectedCell->getAddress() == 0
        )
    )
    {
        return;
    }

    float horizontalPosition = pSelectedCell->getHorizontalPosition();
    float verticalPosition = pSelectedCell->getVerticalPosition();

    uint16_t address = static_cast<uint16_t>(pSelectedCell->getAddress());

    std::vector<entities::Cell>* pCells = level.getPointerCells();

    ((*pCells)[address]).setStringRepresentation(pCellsSelectorCell->getStringRepresentation());
    ((*pCells)[address]).setPicturePath(pCellsSelectorCell->getPicturePath());
    ((*pCells)[address]).setPosition(
        horizontalPosition,
        verticalPosition
    );
}

/**
 *
 */
void EditorLevelController::updateFloorNumber(short updateValue)
{
    /* use a if(), got some troubles with the ternary condition... */
    if (
        (currentFloor ==
         constants::Dimensions::LEVEL_MAX_FLOOR_NUMBER &&
         updateValue > 0) ||
        (currentFloor == 0 && updateValue < 0)
    )
    {
        return;
    }

    currentFloor += updateValue;

    /* add one to be more user friendly */
    floorLabel.setString(std::to_string(currentFloor + 1));
}

/**
 *
 */
void EditorLevelController::updtLevelForSpecCells(
    entities::Cell* pSelectedCell,
    entities::Cell* pCellsSelectorCell
)
{
    std::vector<entities::Cell>* cells = level.getPointerCells();

    /* floor down has to be added if the cell is floor up */
    if (
        pCellsSelectorCell->getStringRepresentation() ==
        constants::CellsFileRepresentations::FLOOR_UP_CELL
    )
    {
        uint16_t addr = pSelectedCell->getAddress() + constants::Dimensions::LEVEL_CELLS_PER_FLOOR;
        entities::Cell* otrCell = &(*cells)[addr];
        entities::Cell* downCell = cellSelector.getFloorDownCell();

        updateOneCell(otrCell, downCell);
    }
}

/**
 *
 */
bool EditorLevelController::currEditIsAllowed()
{
    std::vector<entities::Cell>* cells = level.getPointerCells();

    entities::Cell* cell = cellSelector.getSelectedNewCellPointer();
    entities::Cell* levCell = level.getSelectedCellPointer();

    /* preliminary check for floor cells */
    uint16_t addr = levCell->getAddress();
    entities::Cell *cellPrevFloor = NULL, *cellNextFloor = NULL;

    if (addr - constants::Dimensions::LEVEL_CELLS_PER_FLOOR >= 0)
    {
        cellPrevFloor = &(*cells)[addr - constants::Dimensions::LEVEL_CELLS_PER_FLOOR];
    }
    if (addr + constants::Dimensions::LEVEL_CELLS_PER_FLOOR < constants::Dimensions::CELLS_PER_LEVEL)
    {
        cellNextFloor = &(*cells)[addr + constants::Dimensions::LEVEL_CELLS_PER_FLOOR];
    }

    /* cannot add floor up on the last floor, cannot add floor down on the first floor */
    if (
        (
            cell->getStringRepresentation() ==
            constants::CellsFileRepresentations::FLOOR_UP_CELL &&
            currentFloor == constants::Dimensions::LEVEL_FLOORS - 1
        ) ||
        (
            cell->getStringRepresentation() ==
            constants::CellsFileRepresentations::FLOOR_DOWN_CELL &&
            currentFloor == 0
        )
    )
    {
        return false;
    }

    /* cannot have two floor up cells one after the other */
    if (
        cell->getStringRepresentation() ==
        constants::CellsFileRepresentations::FLOOR_UP_CELL &&
        cellNextFloor != NULL
    )
    {
        if (
            cellNextFloor->getStringRepresentation() ==
            constants::CellsFileRepresentations::FLOOR_UP_CELL
        )
        {
            return false;
        }
    }

    /* cannot have two floor down cells one after the other */
    if (
        cell->getStringRepresentation() ==
        constants::CellsFileRepresentations::FLOOR_DOWN_CELL &&
        cellPrevFloor != NULL
    )
    {
        if (
            cellPrevFloor->getStringRepresentation() ==
            constants::CellsFileRepresentations::FLOOR_DOWN_CELL
        )
        {
            return false;
        }
    }

    return true;
}
