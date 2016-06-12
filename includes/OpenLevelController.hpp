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
     * @param context commons items for controller
     *
     * @return uint8_t   id of the next screen controller
     */
    uint8_t render(utils::Context& context);

private:

    bool errorAlreadyAddedLevel;

    /**
     * @brief modifies the value of the next controller according of
     * the controller that called the current one
     *
     * @param context current context pointer
     */
    void changeNextControllerId(utils::Context& context);

    widgets::TitleBarWidget titleBar;

    widgets::ItemsListWidget levelsList;

    widgets::CursorWidget cursor;

    sf::Color errorLabelColor;

    sf::Text errorLabel;

    sf::Font errorLabelFont;
};
}

#endif
