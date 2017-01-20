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
 * @brief the main menu for the serie selection; the player can choose between
 * the official series and the personal series
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
     * @param context reference to the current context to use
     *
     * not 'noexcept' because calls SFML methods that are not noexcept
     */
    SerieMainMenuController(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~SerieMainMenuController() noexcept;

    /**
     * @brief render the serie editor screen
     *
     * @return const ControllerId&
     *
     * not 'const' because this method modifies the value of some attributes
     * like the expected controller id
     *
     * not 'noexcept' because the parent function is not noexcept (there are
     * too many calls to noexcept functions in all the implementation of this
     * method)
     */
    virtual const ControllerId& render() & override;

private:

    /**
     * @brief overwrite the parent method; defines which constroller is called
     * when one menu item is selected
     */
    virtual void selectMenuItem() const & noexcept override;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
