/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file OpenLevelController.hpp
 * @brief level selector in the editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_OPENLEVELCONTROLLER_H_
#define MEMORIS_OPENLEVELCONTROLLER_H_

#include "Controller.hpp"

#include <memory>

namespace memoris
{
namespace controllers
{

class OpenLevelController : public Controller
{

public:

    /**
     * @brief constructor, initialize the implementation
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because calls SFML methods (through implementation) that
     * are not noexcept
     */
    OpenLevelController(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared for forwarding
     * declaration
     */
    ~OpenLevelController() noexcept;

    /**
     * @brief renders the open level controller
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(
        const utils::Context& context
    ) & override final;

private:

    static constexpr float TITLE_HORIZONTAL_POSITION {620.f};
    static constexpr float TITLE_VERTICAL_POSITION {50.f};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
