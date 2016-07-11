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
 * Open serie screen for series editor.
 *
 * @file OpenSerieController.hpp
 * @brief open serie screen
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_OPEN_SERIE_CONTROLLER
#define DEF_OPEN_SERIE_CONTROLLER

#include "Controller.hpp"

#include "TitleBarWidget.hpp"
#include "ButtonWidget.hpp"
#include "CursorWidget.hpp"
#include "ItemsListWidget.hpp"

namespace memoris
{
namespace controllers
{

class OpenSerieController : public Controller
{

    static const std::string STRING_OPEN_SERIE_TITLE;
    static const std::string OPEN_SERIE_BUTTON_EXIT;

    static const unsigned short OPEN_SERIE_BUTTON_EXIT_POSITION_X;
    static const unsigned short OPEN_SERIE_BUTTON_EXIT_POSITION_Y;

    static const unsigned short OPEN_SERIE_BUTTONS_WIDTH;
    static const unsigned short SERIES_LIST_WIDTH;

    static const unsigned short SERIES_LIST_POSITION_X;
    static const unsigned short SERIES_LIST_POSITION_Y;

    static const unsigned short SERIES_LIST_SERIES_NUMBER;

public:

    OpenSerieController();

    /**
     * @brief render the open serie screen
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render();

private:

    ::widgets::TitleBarWidget titleBar;

    ::widgets::ButtonWidget buttonExit;

    ::widgets::CursorWidget cursor;

    ::widgets::ItemsListWidget seriesList;
};
}
}

#endif
