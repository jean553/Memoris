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
 * Serie editor main screen.
 *
 * @file EditorSerieController.hpp
 * @brief serie editor screen
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_SERIE_CONTROLLER
#define DEF_EDITOR_SERIE_CONTROLLER

#include <SFML/Graphics.hpp>

#include "Controller.hpp"
#include "Context.hpp"
#include "Serie.hpp"
#include "TitleBarWidget.hpp"
#include "ButtonWidget.hpp"
#include "CursorWidget.hpp"
#include "OrderedItemsListWidget.hpp"
#include "InputTextWidget.hpp"

namespace memoris
{
namespace controllers
{

class EditorSerieController : public Controller
{

    static const std::string STRING_EDITOR_SERIE_TITLE;
    static const std::string EDITOR_SERIE_BUTTON_NEW_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_OPEN_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_SAVE_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_ADD_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_EXIT_TEXT;
    static const std::string STRING_OK;
    static const std::string STRING_CANCEL;
    static const std::string STRING_NEW_SERIE_ERROR;
    static const std::string STRING_NEW_LEVEL_ERROR;

    static const unsigned short EDITOR_SERIE_BUTTON_EXIT_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_NEW_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_OPEN_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_SAVE_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_ADD_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_Y;
    static const unsigned short EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_X;
    static const unsigned short EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_Y;
    static const unsigned short LEVELS_LIST_POSITION_X;
    static const unsigned short LEVELS_LIST_POSITION_Y;
    static const unsigned short LEVELS_LIST_WIDTH;
    static const unsigned short LEVELS_LIST_LEVELS_NUMBER;
    static const unsigned short POSITION_NEW_SERIE_INPUT_TEXT_X;
    static const unsigned short POSITION_NEW_SERIE_INPUT_TEXT_Y;
    static const unsigned short SIZE_NEW_SERIE_TEXT;
    static const unsigned short ERROR_MESSAGE_POSITION_X;
    static const unsigned short ERROR_MESSAGE_POSITION_Y;

public:

    /**
     * @brief constructor
     */
    EditorSerieController();

    /**
     * @brief render the serie editor screen
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render();

private:

    static const std::string LEVELS_SPRT;

    bool errorNewSerie;
    bool errorNewLevel;

    enum EditorSerieStatus
    {
        MAIN_MENU,
        NEW_SERIE,
        EDIT_SERIE
    };

    EditorSerieStatus status;

    ::widgets::TitleBarWidget titleBar;

    ::widgets::ButtonWidget buttonNew;
    ::widgets::ButtonWidget buttonOpen;
    ::widgets::ButtonWidget buttonSave;
    ::widgets::ButtonWidget buttonAdd;
    ::widgets::ButtonWidget buttonExit;
    ::widgets::ButtonWidget buttonNewOk;
    ::widgets::ButtonWidget buttonNewCancel;

    ::widgets::CursorWidget cursor;

    ::widgets::OrderedItemsListWidget levelsList;

    ::widgets::InputTextWidget inputTextNew;

    sf::Text serieNameLabel;
    sf::Text errorLabel;
    sf::Text levelErrorLabel;

    entities::Serie serie;

    /**
     * @brief enable/disable all the series editor main menu buttons
     *
     * @param areEnabled true to enable, false to disable
     */
    void switchMainMenuButtons(bool areEnabled);

    /**
     * @brief enable the add and save buttons, disable the new and open button
     */
    void switchMainMenuButtonsToEditSerieStatus();

    /**
     * @brief initialize the main menu buttons
     */
    void initializeMainMenuButtons();

    /**
     * @brief check if a serie name is already used
     *
     * @param serieName name of the serie
     *
     * @return boolean
     */
    bool serieExists(std::string serieName);

    /**
     * @brief changes the color of the displayed serie
     * name, according if the latest version of
     * the serie has been persisted
     *
     * @param saved true if saved, false if unsaved
     */
    void displaySavedSerieName(bool saved);

    /**
     * @brief update the position of the serie name label
     */
    void updateSerieNameLabelPosition();

    /**
     * @brief initialize the serie editor if one serie is already opened,
     * only used if the controller has been called after the OpenLevel one
     */
    void initializeOpenedSerie();

    /**
     * @brief write the levels into the serie file, the content
     * of the file is deleted before
     */
    void writeLevelsIntoSerie();
};

}
}

#endif
