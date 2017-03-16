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
 * @file OfficialSeriesMenuController.hpp
 * @brief displays all the official series of the game
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_OFFICIALSERIESMENUCONTROLLER_H_
#define MEMORIS_OFFICIALSERIESMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

#include <memory>

namespace memoris
{

namespace controllers
{

class OfficialSeriesMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    OfficialSeriesMenuController(const utils::Context& context);

    /**
     * the copy constructor and copy operator are already deleted
     * into the parent Controller class
     */

    /**
     * @brief default destructor
     */
    ~OfficialSeriesMenuController();

    /**
     * @brief renders the controller
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
     * @brief defines what happens when a menu item is selected
     */
    virtual void selectMenuItem() const & noexcept override;

    /**
     * @brief returns the name of the serie file to open according to the
     * selected menu item
     *
     * @return const std::string
     */
    const std::string getSerieNameByItemId() const & noexcept;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
