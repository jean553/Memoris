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

#include "../utils/Controller.hpp"

#include "../widgets/TitleBarWidget.hpp"
#include "../widgets/ButtonWidget.hpp"
#include "../widgets/CursorWidget.hpp"
#include "../widgets/ItemsListWidget.hpp"

namespace controllers {
class OpenSerieController : public Controller {

    static const std::string STRING_OPEN_SERIE_TITLE;
    static const std::string OPEN_SERIE_BUTTON_EXIT;

    static const unsigned int OPEN_SERIE_BUTTON_EXIT_POSITION_X = 1400;
    static const unsigned int OPEN_SERIE_BUTTON_EXIT_POSITION_Y = 10;
    static const unsigned int OPEN_SERIE_BUTTONS_WIDTH = 200;
    static const unsigned int SERIES_LIST_POSITION_X = 10;
    static const unsigned int SERIES_LIST_POSITION_Y = 130;
    static const unsigned int SERIES_LIST_WIDTH = 1580;
    static const unsigned int SERIES_LIST_SERIES_NUMBER = 18;

public:

    OpenSerieController();
    
    /**
     * @brief render the open serie screen
     *
     * @param context commons items for controller
     *
     * @return char   id of the next screen controller
     */
    unsigned char render(
        utils::Context* context
    );

private:

    widgets::TitleBarWidget titleBar;

    widgets::ButtonWidget buttonExit;

    widgets::CursorWidget cursor;

    widgets::ItemsListWidget seriesList;
};
}

#endif
