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

#include "../utils/Controller.hpp"
#include "../utils/Context.hpp"
#include "../utils/ScreenFactory.hpp"
#include "../utils/DirReader.hpp"

#include "../defines/Fonts.hpp"
#include "../defines/Colors.hpp"

#include "../widgets/TitleBarWidget.hpp"
#include "../widgets/ButtonWidget.hpp"
#include "../widgets/CursorWidget.hpp"
#include "../widgets/ItemsListWidget.hpp"
#include "../widgets/InputTextWidget.hpp"

namespace controllers {
class EditorSerieController : public Controller {

    static const std::string STRING_EDITOR_SERIE_TITLE;
    static const std::string EDITOR_SERIE_BUTTON_NEW_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_OPEN_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_SAVE_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_ADD_TEXT;
    static const std::string EDITOR_SERIE_BUTTON_EXIT_TEXT;
    static const std::string STRING_OK;
    static const std::string STRING_CANCEL;

    static constexpr unsigned int EDITOR_SERIE_BUTTON_NEW_POSITION_X = 10;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_OPEN_POSITION_X = 240;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_SAVE_POSITION_X = 470;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_ADD_POSITION_X = 700;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_EXIT_POSITION_X = 1390;
    static constexpr unsigned int EDITOR_SERIE_BUTTONS_POSITION_Y = 100;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_X = 600;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_NEW_SERIE_OK_POSITION_Y = 175;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_X = 810;
    static constexpr unsigned int EDITOR_SERIE_BUTTON_NEW_SERIE_CANCEL_POSITION_Y = 175;
    static constexpr unsigned int EDITOR_SERIE_BUTTONS_WIDTH = 200;
    static constexpr unsigned int LEVELS_LIST_POSITION_X = 10;
    static constexpr unsigned int LEVELS_LIST_POSITION_Y = 250;
    static constexpr unsigned int LEVELS_LIST_WIDTH = 1580;
    static constexpr unsigned int LEVELS_LIST_LEVELS_NUMBER = 15;
    static constexpr unsigned int POSITION_NEW_SERIE_INPUT_TEXT_X = 10;
    static constexpr unsigned int POSITION_NEW_SERIE_INPUT_TEXT_Y = 175;
    static constexpr unsigned int SIZE_NEW_SERIE_TEXT = 350;
    static constexpr unsigned int POSITION_SERIE_NAME_LABEL_Y = 0;

public:

    EditorSerieController();

    /**
     * @brief render the serie editor screen
     *
     * @param context commons items for controller
     *
     * @return char   id of the next screen controller
     */
    unsigned char render(
        utils::Context* context
    );

private:

    enum EditorSerieStatus {
        MAIN_MENU,
        NEW_SERIE,
        EDIT_SERIE,
        NEW_LEVEL
    };

    EditorSerieStatus status;

    widgets::TitleBarWidget titleBar;

    widgets::ButtonWidget buttonNew;
    widgets::ButtonWidget buttonOpen;
    widgets::ButtonWidget buttonSave;
    widgets::ButtonWidget buttonAdd;
    widgets::ButtonWidget buttonExit;
    widgets::ButtonWidget buttonNewOk;
    widgets::ButtonWidget buttonNewCancel;

    widgets::CursorWidget cursor;

    widgets::ItemsListWidget levelsList;

    widgets::InputTextWidget inputTextNew;

    sf::Font serieNameLabelFont;

    sf::Color serieNameLabelColor;

    sf::Text serieNameLabel;

    /**
     * @brief enable/disable all the series editor main menu buttons
     *
     * @param areEnabled true to enable, false to disable
     */
    void switchMainMenuButtons(bool areEnabled);

    /**
     * @brief initialize the main menu buttons
     */
    void initializeMainMenuButtons();
};
}

#endif
