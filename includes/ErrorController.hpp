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
 * @file ErrorController.hpp
 * @brief display exceptions messages in a dedicated screen (resources cannot
 * be found, level/serie cannot be found... etc...)
 * TODO: #559 this controller is partially developped and only display a black
 * screen for now...
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ERRORCONTROLLER_H_
#define MEMORIS_ERRORCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{
namespace controllers
{

class ErrorController : public Controller
{

public:

    /**
     * @brief constructor, does nothing, just declared and defined to pass
     * the context shared pointer to the Controller constructor as it is the
     * parent class
     *
     * @param contextPtr shared pointer to the context to use
     */
    ErrorController(std::shared_ptr<utils::Context> contextPtr);

    /**
     * @brief renders the error message screen
     *
     * @return unsigned short
     */
    unsigned short render();
};

}
}

#endif
