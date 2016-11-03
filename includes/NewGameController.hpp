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
 * @file NewGameController.hpp
 * @brief controller that displays the new game screen; this screen contains
 * a title and an input text widget to let the user enter the name of the
 * new game
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
     * @brief constructor, creates the title surface and the explanation
     * label surface; creates the input text widget
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    NewGameController(utils::Context& context);

    /**
     * @brief default destructor, empty, only declared here in order to use
     * forwarding declaration
     */
    ~NewGameController() noexcept;

    /**
     * @brief render the new game screen
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(
        const utils::Context& context
    ) & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
