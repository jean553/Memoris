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
    void display(const std::shared_ptr<utils::Context>& context) const;

private:

    /* the vertical separators at both sides of the dashboard */
    utils::LevelSeparators separators;

    /* buttons of the tool bar */
    widgets::Button buttonNew;
    widgets::Button buttonOpen;
    widgets::Button buttonSave;

};

}
}

#endif
