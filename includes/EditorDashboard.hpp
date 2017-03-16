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
 * @brief dashboard displayed into the level editor
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
     *
     * public because accessed from the level editor controller
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
     * @param cursorPosition the cursor position
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void display(const sf::Vector2<float>& cursorPosition) const &;

    /**
     * @brief returns an action id according to the tool bar selected button
     *
     * @return const EditorDashboard::Action
     *
     * not noexcept because it contains sub-functions that calls SFML methods
     * that are not noexcept
     */
    const Action getActionIdBySelectedButton() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
