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
 * @file SerieMainMenuController.hpp
 * @brief main menu to select between official and personal series
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SERIEMAINMENUCONTROLLER_H_
#define MEMORIS_SERIEMAINMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

namespace memoris
{
namespace controllers
{

class SerieMainMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context the current context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    SerieMainMenuController(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~SerieMainMenuController();

    /**
     * @brief render the serie editor screen
     *
     * @return const ControllerId&
     *
     * no one of the controllers overwritten render() method is noexcept;
     * (check parent declaration for details);
     * they all use not noexcept SFML methods
     */
    virtual const ControllerId& render() const & override;

private:

    /**
     * @brief updates the expected controller id according to the selection
     */
    virtual void selectMenuItem() const & noexcept override;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
