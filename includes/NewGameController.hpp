/**
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
     */
    virtual const ControllerId& render() const & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
