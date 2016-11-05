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
     * @brief constructor, empty, only declared here in order to call the
     * parent class constructor
     *
     * @param context constant reference to the current context
     * @param message constant reference to the SFML string to render
     */
    ErrorController(
        const utils::Context& context,
        const sf::String& message
    );

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~ErrorController() noexcept;

    /**
     * @brief renders the error message screen
     *
     * @param context constant reference to the current context
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(
        const utils::Context& context
    ) & override final;

private:

    static constexpr float MESSAGE_VERTICAL_POSITION {300.f};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
