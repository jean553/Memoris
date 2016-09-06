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

#include "Context.hpp"

#include "LevelSeparators.hpp"
#include "Button.hpp"

namespace memoris
{
namespace utils
{

class EditorDashboard
{

public:

    /* public actions ids used to communicate with the level editor */

    static constexpr unsigned short EXIT_ACTION_ID {1};
    static constexpr unsigned short SAVE_ACTION_ID {2};

    /**
     * @brief constructor, initializes the level separator
     *
     * @param context shared pointer to the current context to use
     */
    EditorDashboard(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief display the editor dashboard
     *
     * @param context shared pointer to the current context to use
     */
    void display(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief proxy method that returns an event id, this event id is got
     * by the level editor; with this action id, the level id knows what to
     * do (leave, display a popup, go to another controller...); the events
     * ids are public constant expressions of this class; they are public
     * to let the level editor use them; returns 0 if no button selected
     *
     * @return unsigned short
     */
    unsigned short getActionIdBySelectedButton() const;

private:

    /* the vertical separators at both sides of the dashboard */
    utils::LevelSeparators separators;

    /* buttons of the tool bar */
    widgets::Button buttonNew;
    widgets::Button buttonOpen;
    widgets::Button buttonSave;
    widgets::Button buttonExit;
    widgets::Button buttonTime;
};

}
}

#endif
