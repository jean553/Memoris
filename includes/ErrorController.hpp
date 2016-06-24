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
 * @brief display exceptions messages
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_ERR_CONTROLLER
#define DEF_ERR_CONTROLLER

#include <string>

#include "Context.hpp"
#include "Controller.hpp"
#include "fonts.hpp"


namespace memoris
{
namespace controllers
{
class ErrorController : public Controller
{
public:

    /**
     * @brief constructor
     *
     * @param context reference to the current context
     * @param msg error message to display
     */
    ErrorController(
        utils::Context& context,
        const std::string& msg
    );

    /**
     * @brief renders the error message screen
     *
     * @param context commons items for controller
     *
     * @return unsigned short id of the new screen controller
     */
    unsigned short render(utils::Context& context);

private:

    static const float_t ERR_HRTL_PSTN;
    static const float_t ERR_VRTL_PSTN;

    std::string errMsg;

    sf::Text error;
};
}
}

#endif
