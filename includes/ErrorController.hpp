/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief controller that displays errors
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ERRORCONTROLLER_H_
#define MEMORIS_ERRORCONTROLLER_H_

#include "Controller.hpp"

namespace sf
{
class String;
}

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
     * @param context the current context
     * @param message the error message to display
     * @param previousControllerId the previous controller id (to go back)
     */
    ErrorController(
        const utils::Context& context,
        const sf::String& message,
        const ControllerId& previousControllerId
    );

    /**
     * @brief default destructor
     */
    ~ErrorController();

    /**
     * @brief renders the controller with the error message
     *
     * @return const ControllerId&
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    virtual const ControllerId& render() const & override;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
