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

#include "../utils/Controller.hpp"

#include "../widgets/ButtonWidget.hpp"
#include "../widgets/CursorWidget.hpp"
#include "../widgets/TitleBarWidget.hpp"

#include "../entities/Level.hpp"

namespace controllers {
class EditorLevelController : public Controller {

    static const std::string EDITOR_LEVEL_BUTTON_EXIT_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_NEW_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_OPEN_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_SAVE_TEXT;
    static const std::string STRING_EDITOR_LEVEL_TITLE;
    static const std::string DEFAULT_LEVEL_NAME;

    static const unsigned short LEVEL_EDITOR_BUTTONS_POSITION_X;
    static const unsigned short LEVEL_EDITOR_BUTTON_NEW_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y;
    static const unsigned short LEVEL_POSITION_X;
    static const unsigned short LEVEL_POSITION_Y;

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

    widgets::ButtonWidget buttonExit;
    widgets::ButtonWidget buttonNew;
    widgets::ButtonWidget buttonOpen;
    widgets::ButtonWidget buttonSave;

    widgets::CursorWidget cursor;

    widgets::TitleBarWidget titleBar;

    entities::Level level;

    sf::Font levelNameLabelFont;

    sf::Color levelNameLabelColor;

    sf::Text levelNameLabel;
};
}

#endif
