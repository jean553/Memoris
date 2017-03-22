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

    static constexpr float TITLE_VERTICAL_POSITION {200.f};
    static constexpr float TIME_VERTICAL_POSITION {400.f};
    static constexpr float RESULTS_FIRST_ITEM_VERTICAL_POSITION {300.f};
    static constexpr float RESULTS_INTERVAL {50.f};

    static constexpr unsigned short SECONDS_IN_ONE_MINUTE {60};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
