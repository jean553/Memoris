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
 * @file EditorDashboard.hpp
 * @brief level editor dashboard
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_EDITORDASHBOARD_H_
#define MEMORIS_EDITORDASHBOARD_H_

#include <memory>

namespace sf
{
template<typename T>
class Vector2;
}

namespace memoris
{
namespace utils
{

class Context;

class EditorDashboard
{

public:

    /**
     * @enum EditorDashboard::Action
     * @brief the action selected by the user from the editor dashboard
     */
    enum class Action
    {
        EXIT,
        NEW,
        SAVE,
        OPEN,
        PLAY,
        UP,
        DOWN,
        NO_ACTION /** < used when nothing is selected */
    };

    /**
     * @brief constructor
     *
     * @param context constant reference to the context object to use
     */
    EditorDashboard(const utils::Context& context);

    EditorDashboard(const EditorDashboard&) = delete;

    EditorDashboard& operator=(const EditorDashboard&) = delete;

    /**
     * @brief default destructor
     */
    ~EditorDashboard();

    /**
     * @brief displays the editor dashboard
     *
     * @param cursorPosition the cursor position
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void display(const sf::Vector2<float>& cursorPosition) const &;

    /**
     * @brief returns the selected action from the dashboard
     *
     * @return const EditorDashboard::Action
     *
     * not noexcept because it contains sub-functions that calls SFML methods
     */
    const Action getActionIdBySelectedButton() const &;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
