/*
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
 * @file EditorDashboard.hpp
 * @brief dashboard displayed into the level editor
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_EDITORDASHBOARD_H_
#define MEMORIS_EDITORDASHBOARD_H_

#include <memory>

namespace memoris
{
namespace utils
{

class Context;

class EditorDashboard
{

public:

    /* public static constant expressions used by the level editor controller
       in order to know which button has been selected */

    static constexpr unsigned short EXIT_ACTION_ID {1};
    static constexpr unsigned short SAVE_ACTION_ID {2};
    static constexpr unsigned short FLOOR_UP_ACTION_ID {3};
    static constexpr unsigned short FLOOR_DOWN_ACTION_ID {4};
    static constexpr unsigned short NEW_ACTION_ID {5};
    static constexpr unsigned short OPEN_ACTION_ID {6};

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the context object to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    EditorDashboard(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared here in order to use
     * forwarding declaration
     */
    ~EditorDashboard() noexcept;

    /**
     * @brief display the editor dashboard
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void display(const utils::Context& context) const &;

    /**
     * @brief returns an action id according to the tool bar selected button
     *
     * @return const unsigned short
     *
     * the returned value is not a reference because we return constant
     * expressions values and rvalue
     *
     * not 'noexcept' because it contains sub-functions that calls SFML methods
     * that are not noexcept
     */
    const unsigned short getActionIdBySelectedButton() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
