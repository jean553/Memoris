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
 * @file EditorLevelController.hpp
 * @brief levels editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_LEVEL_CONTROLLER
#define DEF_EDITOR_LEVEL_CONTROLLER

#include <SFML/Graphics.hpp>

#include "Controller.hpp"

#include "ButtonWidget.hpp"
#include "CursorWidget.hpp"
#include "TitleBarWidget.hpp"
#include "InputTextWidget.hpp"

#include "Level.hpp"

namespace controllers {
class EditorLevelController : public Controller {

    static const std::string EDITOR_LEVEL_BUTTON_EXIT_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_NEW_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_OPEN_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_SAVE_TEXT;

    static const std::string STRING_EDITOR_LEVEL_TITLE;
    static const std::string STRING_NEW_LEVEL_ERROR;

    static const unsigned short LEVEL_EDITOR_BUTTONS_POSITION_X;
    static const unsigned short LEVEL_EDITOR_BUTTON_NEW_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y;

    static const unsigned short LEVEL_POSITION_X;
    static const unsigned short LEVEL_POSITION_Y;

    static const unsigned short ERROR_MESSAGE_POSITION_X;
    static const unsigned short ERROR_MESSAGE_POSITION_Y;

    static const unsigned short POSITION_NEW_LEVEL_INPUT_TEXT_X;
    static const unsigned short POSITION_NEW_LEVEL_INPUT_TEXT_Y;

    static const unsigned short SIZE_NEW_LEVEL_TEXT;

public:

    EditorLevelController();

    /**
     * @brief renders the level editor screen
     *
     * @param pContext commons items for controller
     *
     * @return short    id of the new screen controller
     */
    unsigned short render(utils::Context* pContext);

private:

    enum EditorLevelStatus {
        MAIN_MENU,
        NEW_LEVEL,
        EDIT_LEVEL
    };

    EditorLevelStatus status;

    widgets::ButtonWidget buttonExit;
    widgets::ButtonWidget buttonNew;
    widgets::ButtonWidget buttonOpen;
    widgets::ButtonWidget buttonSave;

    widgets::CursorWidget cursor;

    widgets::TitleBarWidget titleBar;

    widgets::InputTextWidget inputTextNew;

    entities::Level level;

    sf::Font levelNameLabelFont;

    sf::Color levelNameLabelColor;
    sf::Color levelNameLabelUnsavedColor;
    sf::Color errorLabelColor;

    sf::Text levelNameLabel;
    sf::Text errorLabel;

    bool levelAlreadyExists;

    /**
     * @brief check if a level name already exists
     *
     * @param levelName name of the level
     *
     * @return boolean
     */
    bool levelExists(std::string levelName);

    /**
     * @brief change the color of the level name
     * according if the file is saved or not
     *
     * @param saved boolean of the value to display
     */
    void displaySavedLevelName(bool saved);
};
}

#endif
