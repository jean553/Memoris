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

#include "dimensions.hpp"
#include "Positions.hpp"
#include "Directories.hpp"
#include "Extensions.hpp"
#include "fonts.hpp"
#include "DirReader.hpp"
#include "StringsListsUtils.hpp"
#include "FileWriter.hpp"
#include "Screens.hpp"
#include "Messages.hpp"
#include "window.hpp"
#include "controllers.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

namespace memoris
{
namespace controllers
{

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
const std::string EditorSerieController::LEVELS_SPRT = "|";

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
EditorSerieController::EditorSerieController() :
    Controller(),
    inputTextNew(
        POSITION_NEW_SERIE_INPUT_TEXT_X,
        POSITION_NEW_SERIE_INPUT_TEXT_Y,
        SIZE_NEW_SERIE_TEXT,
        10
    )
{
    errorNewSerie = false;
    errorNewLevel = false;

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
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonOpen.setLayout(
        EDITOR_SERIE_BUTTON_OPEN_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonSave.setLayout(
        EDITOR_SERIE_BUTTON_SAVE_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonAdd.setLayout(
        EDITOR_SERIE_BUTTON_ADD_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonExit.setLayout(
        EDITOR_SERIE_BUTTON_EXIT_POSITION_X,
        constants::Positions::EDITOR_BUTTONS_POSITION_Y,
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonNewOk.setLayout(
        EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_X,
        EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_Y,
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    buttonNewCancel.setLayout(
        EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_X,
        EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_Y,
        memoris::dimensions::EDITOR_BUTTONS_WIDTH
    );

    levelsList.setLayout(
        LEVELS_LIST_POSITION_X,
        LEVELS_LIST_POSITION_Y,
        LEVELS_LIST_WIDTH,
        LEVELS_LIST_LEVELS_NUMBER
    );

    serieNameLabel.setFont(memoris::fonts::FontsManager::get().getTextFont());
    serieNameLabel.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    serieNameLabel.setColor(memoris::colors::ColorsManager::get().getColorGrey());

    errorLabel.setFont(memoris::fonts::FontsManager::get().getTextFont());
    errorLabel.setCharacterSize(memoris::fonts::INFORMATION_SIZE);
    errorLabel.setColor(memoris::colors::ColorsManager::get().getColorRed());
    errorLabel.setString(STRING_NEW_SERIE_ERROR);
    errorLabel.setPosition(
        ERROR_MESSAGE_POSITION_X,
        ERROR_MESSAGE_POSITION_Y
    );

    levelErrorLabel.setFont(memoris::fonts::FontsManager::get().getTextFont());
    levelErrorLabel.setCharacterSize(memoris::fonts::INFORMATION_SIZE);
    levelErrorLabel.setColor(memoris::colors::ColorsManager::get().getColorRed());
    levelErrorLabel.setString(STRING_NEW_LEVEL_ERROR);
    levelErrorLabel.setPosition(
        ERROR_MESSAGE_POSITION_X,
        ERROR_MESSAGE_POSITION_Y
    );

    initializeOpenedSerie();
}

/**
 *
 */
unsigned short EditorSerieController::render()
{
    titleBar.display();
    buttonNew.display();
    buttonOpen.display();
    buttonSave.display();
    buttonAdd.display();
    buttonExit.display();
    levelsList.display();

    if (status == NEW_SERIE)
    {
        buttonNewOk.display();
        buttonNewCancel.display();
        inputTextNew.display();
    }

    if (status != MAIN_MENU)
    {
        utils::Context::get().getSfmlWindow().draw(serieNameLabel);
    }

    if (errorNewSerie)
    {
        utils::Context::get().getSfmlWindow().draw(errorLabel);
    }
    else if (errorNewLevel)
    {
        utils::Context::get().getSfmlWindow().draw(levelErrorLabel);
    }

    cursor.display();

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

                expectedControllerId =
                    MAIN_MENU_CONTROLLER_ID;

                break;
            }
            default:
            {

                if(status == NEW_SERIE)
                {
                    inputTextNew.update(event);
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

                if(buttonExit.isMouseHover())
                {
                    utils::Context::get().removeAllMessages();

                    expectedControllerId =
                        MAIN_MENU_CONTROLLER_ID;
                }
                /* check buttons click according to current status */
                switch(status)
                {
                case MAIN_MENU:
                    if(buttonNew.isMouseHover())
                    {

                        switchMainMenuButtons(false);

                        status = NEW_SERIE;
                    }
                    if(buttonOpen.isMouseHover())
                    {
                        expectedControllerId =
                            OPEN_SERIE_CONTROLLER_ID;
                    }
                    break;
                case NEW_SERIE:
                    if(buttonNewOk.isMouseHover())
                    {

                        if (serieExists(inputTextNew.getText()))
                        {
                            errorNewSerie = true;
                            continue;
                        }

                        serie.setName(inputTextNew.getText());

                        errorNewSerie = false;

                        serieNameLabel.setString(inputTextNew.getText());
                        updateSerieNameLabelPosition();

                        switchMainMenuButtonsToEditSerieStatus();

                        status = EDIT_SERIE;
                    }
                    if(buttonNewCancel.isMouseHover())
                    {

                        buttonNew.setEnable(true);
                        buttonOpen.setEnable(true);

                        errorNewSerie = false;

                        status = MAIN_MENU;

                        /* TODO: temporary deleted to make refactor of the
                           input text widget easier */
                        //inputTextNew.clear();
                    }
                    break;
                case EDIT_SERIE:
                    if(buttonSave.isMouseHover())
                    {

                        if (!serieExists(serie.getName()))
                        {
                            ::utils::FileWriter::writeFile(
                                constants::Directories::SERIES_DIRECTORY_PATH +
                                serie.getName() +
                                constants::Extensions::SERIES_EXTENSION
                            );
                        }

                        writeLevelsIntoSerie();

                        displaySavedSerieName(true);
                    }
                    if(buttonAdd.isMouseHover())
                    {
                        utils::Context::get().addMessageByName(
                            constants::Messages::PREVIOUS_CONTROLLER_MESSAGE,
                            constants::Screens::SERIE_EDITOR_SCREEN_NAME
                        );

                        utils::Context::get().addMessageByName(
                            constants::Messages::OPEN_SERIE_MESSAGE,
                            serie.getName()
                        );

                        utils::Context::get().setStringsList(levelsList.getStringsList());

                        expectedControllerId =
                            OPEN_LEVEL_CONTROLLER_ID;

                    }
                }
                break;
            }
            default:
            {
                /* useless, added here to respect the syntax */
                break;
            }
            }
        }
        default:
        {
            /* useless, added here to respect the syntax */
            break;
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
    if (saved)
    {
        serieNameLabel.setColor(memoris::colors::ColorsManager::get().getColorWhite());
    }
    else
    {
        serieNameLabel.setColor(memoris::colors::ColorsManager::get().getColorGrey());
    }

    buttonSave.setEnable(!saved);
}

/**
 *
 */
bool EditorSerieController::serieExists(std::string serieName)
{
    std::string seriesDirectory =
        constants::Directories::SERIES_DIRECTORY_PATH;

    std::string seriesExtension =
        constants::Extensions::SERIES_EXTENSION;

    std::vector<std::string> seriesNames =
        ::utils::DirReader::getAllFiles(
            seriesDirectory.c_str(),
            seriesExtension.c_str()
        );

    return ::utils::StringsListsUtils::stringsListContainsString(
               seriesNames,
               serieName
           );
}

/**
 *
 */
void EditorSerieController::updateSerieNameLabelPosition()
{
    serieNameLabel.setPosition(
        window::WIDTH -
        serieNameLabel.getLocalBounds().width,
        0
    );
}

/**
 *
 */
void EditorSerieController::initializeOpenedSerie()
{
    std::string openedSerie =
        utils::Context::get().getMessageByName(constants::Messages::OPEN_SERIE_MESSAGE);

    if (openedSerie.empty())
    {
        initializeMainMenuButtons();
        status = MAIN_MENU;

        return;
    }

    serie.setName(openedSerie);

    serieNameLabel.setString(openedSerie);
    status = EDIT_SERIE;

    updateSerieNameLabelPosition();
    switchMainMenuButtonsToEditSerieStatus();

    levelsList.setStringsList(utils::Context::get().getStringsList());
}

/**
 *
 */
void EditorSerieController::writeLevelsIntoSerie()
{
    std::vector<std::string> strList = levelsList.getStringsList();
    std::string strToWrt;

    for (
        std::vector<std::string>::iterator i = strList.begin();
        i != strList.end();
        ++i
    )
    {
        strToWrt = strToWrt + (*i);

        /* do not add the separator if the level is the last one; use a cast
           to make the strings list size a signed value (std::distance can
           return a signed value too */
        if (
            std::distance(strList.begin(), i) !=
            static_cast<int>(strList.size() - 1))
        {
            strToWrt = strToWrt + LEVELS_SPRT;
        }
    }

    ::utils::FileWriter::writeFile(
        constants::Directories::SERIES_DIRECTORY_PATH +
        serie.getName() +
        constants::Extensions::SERIES_EXTENSION,
        strToWrt
    );
}

}
}
