/**
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
 * @file RemoveGameController.hpp
 * @brief displayed when the user wants to delete one game, displays the
 * confirmation message and handles the file deletion
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_REMOVEGAMECONFIRMATIONCONTROLLER_H_
#define MEMORIS_REMOVEGAMECONFIRMATIONCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{
namespace controllers
{

class RemoveGameController : public Controller
{

public:

    /**
     * @brief constructor, intializes the implementation
     *
     * @param context constant reference to the current context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    RemoveGameController(const utils::Context& context);

    /**
     * @brief default destructor, only declared in order to use the forwarding
     * declaration
     */
    ~RemoveGameController() noexcept;

    /**
     * @brief render the remove game controller
     *
     * @return const ControllerId&
     */
    const ControllerId& render() const & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
