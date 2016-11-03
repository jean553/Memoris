/**
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
 * @file OpenGameController.hpp
 * @brief controller that displays the games list
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_OPENGAMECONTROLLER_H_
#define MEMORIS_OPENGAMECONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{

namespace utils
{
class Context;
}

namespace controllers
{

class OpenGameController : public Controller
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    OpenGameController(const utils::Context& context);

    /**
     * @brief default destructor, empty, declared here only in order to use
     * forwarding declaration
     */
    ~OpenGameController() noexcept;

    /**
     * @brief render the open game screen
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     *
     * the context parameter is not a constant reference to keep compliance
     * with based virtual function declaration
     *
     * not 'const' to match with the parent virtual function
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    virtual const unsigned short& render(const utils::Context& context) & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
