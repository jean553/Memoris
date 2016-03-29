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

#include "Controller.hpp"
#include "TitleBarWidget.hpp"

namespace controllers {
class OpenLevelController : public Controller {

    static const std::string STRING_OPEN_LEVEL_TITLE;

public:
    OpenLevelController();

    /**
     * @brief render the open serie screen
     *
     * @param pContext commons items for controller
     *
     * @return short   id of the next screen controller
     */
    unsigned short render(
        utils::Context* pContext
    );

private:

    widgets::TitleBarWidget titleBar;
};
}

#endif
