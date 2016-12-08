/*
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
 * @file RankingController.hpp
 * @brief renders the three best times for the current serie
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_RANKINGCONTROLLER_H_
#define MEMORIS_RANKINGCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{

namespace utils
{
class Context;
}

namespace controllers
{

class RankingController : public Controller
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param constant reference to the current context to use
     */
    RankingController(const utils::Context& context);

    /**
     * @brief destructor, empty, only declared in order to use forwarding
     * declaration
     */
    ~RankingController() noexcept;

    /**
     * @brief overrides the render() method of the Controller parent class
     *
     * @param context constant reference to the current context to use
     *
     * @return const unsigned short&
     */
    const unsigned short& render(const utils::Context& context) & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
