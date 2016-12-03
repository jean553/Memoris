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
 * @file PersonalSeriesMenuController.hpp
 * @brief personal series menu; displays all the series created by users
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PERSONALSERIESMENUCONTROLLER_H_
#define MEMORIS_PERSONALSERIESMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

#include <memory>

namespace memoris
{
namespace controllers
{

class PersonalSeriesMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the current context to use
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    PersonalSeriesMenuController(const utils::Context& context);

    /**
     * @brief destructor, empty, only declared in order to use forwarding
     * declaration
     */
    ~PersonalSeriesMenuController() noexcept;

    /**
     * @brief renders the controller
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(
        const utils::Context& context
    ) & override;

private:

    /**
     * @brief defines what happens when a menu item is selected
     *
     * not 'const' because the the expected controller id is modified
     */
    virtual void selectMenuItem() & noexcept override;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
