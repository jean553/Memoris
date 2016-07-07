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
 * Open level screen for series editor.
 *
 * @file OpenLevelController.hpp
 * @brief open level screen
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_OPEN_LEVEL_CONTROLLER
#define DEF_OPEN_LEVEL_CONTROLLER

#include <SFML/Graphics.hpp>

#include "Controller.hpp"
#include "TitleBarWidget.hpp"
#include "ItemsListWidget.hpp"
#include "CursorWidget.hpp"

namespace memoris
{
namespace controllers
{

class OpenLevelController : public Controller
{

    static const std::string STRING_OPEN_LEVEL_TITLE;
    static const std::string STRING_ALREADY_ADDED_ERROR_MESSAGE;

    static const unsigned short LEVELS_LIST_WIDTH;
    static const unsigned short LEVELS_LIST_POSITION_X;
    static const unsigned short LEVELS_LIST_POSITION_Y;
    static const unsigned short LEVELS_LIST_LEVELS_NUMBER;

    static const float ERROR_MESSAGE_POSITION_X;
    static const float ERROR_MESSAGE_POSITION_Y;

public:
    OpenLevelController();

    /**
     * @brief render the open serie screen
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render();

private:

    bool errorAlreadyAddedLevel;

    /**
     * @brief modifies the value of the next controller according of
     * the controller that called the current one
     */
    void changeNextControllerId();

    widgets::TitleBarWidget titleBar;

    widgets::ItemsListWidget levelsList;

    widgets::CursorWidget cursor;

    sf::Text errorLabel;
};

}
}

#endif
