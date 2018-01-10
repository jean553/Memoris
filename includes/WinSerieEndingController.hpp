/*
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
 * @file WinSerieEndingController.hpp
 * @brief displayed when the player wins the serie
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WINSERIEENDINGCONTROLLER_H_
#define MEMORIS_WINSERIEENDINGCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{
namespace controllers
{

class WinSerieEndingController : public Controller
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
     * @throws std::invalid_argument the format of serie record is incorrect
     * and the time cannot be calculated; the function throws an exception,
     * this exception is caught and an error message is displayed into the
     * error controller
     */
    WinSerieEndingController(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~WinSerieEndingController();

    /**
     * @brief renders the controller
     *
     * @return const ControllerId&
     *
     * no one of the controllers overwritten render() method is noexcept;
     * (check parent declaration for details);
     * they all use not noexcept SFML methods
     */
    const ControllerId& render() const & override;

private:

    /**
     * @brief updates the current game file in order to unlock the next serie
     *
     * not noexcept as manipulating std::fstream may throw exceptions
     */
    inline void unlockNextSerieFromGameFile() const &;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
