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
 * @file PersonalSeriesMenuController.hpp
 * @brief displays and selects user's created series
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PERSONALSERIESMENUCONTROLLER_H_
#define MEMORIS_PERSONALSERIESMENUCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{

namespace utils
{
class Context;
}

namespace controllers
{

class PersonalSeriesMenuController : public Controller
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     *
     * @throws std::invalid_argument throws if the files list cannot
     * be loaded from the personal series directory;
     * this exception is never caught and the program terminates
     */
    PersonalSeriesMenuController(const utils::Context& context);

    /**
     * the copy constructor and copy operator are already deleted
     * into the parent Controller class
     */

    /**
     * @brief default destructor
     */
    ~PersonalSeriesMenuController();

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

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
