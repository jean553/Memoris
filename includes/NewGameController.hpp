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
 * @file NewGameController.hpp
 * @brief displays an input text widget to let the user create a new game
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_NEWGAME_H_
#define MEMORIS_NEWGAME_H_

#include "Controller.hpp"

namespace memoris
{
namespace controllers
{

class NewGameController : public Controller
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    NewGameController(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~NewGameController();

    /**
     * @brief render the new game screen
     *
     * @return const ControllerId&
     *
     * @throw std::ios_base::failure error when the new game file is created
     * the exception is never caught and the program simply terminates
     *
     * no one of the controllers overwritten render() method is noexcept;
     * (check parent declaration for details);
     * they all use not noexcept SFML methods
     */
    virtual const ControllerId& render() const & override;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
