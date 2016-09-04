/**
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
 * @file LevelEditorController.hpp
 * @package controllers
 * @brief render the level editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELEDITORCONTROLLER_H_
#define MEMORIS_LEVELEDITORCONTROLLER_H_

#include "Controller.hpp"

#include "EditorDashboard.hpp"
#include "Level.hpp"
#include "Cursor.hpp"
#include "CellsSelector.hpp"
#include "SaveLevelDialog.hpp"

namespace memoris
{
namespace controllers
{

class LevelEditorController : public Controller
{

public:

    /**
     * @brief constructor, empty for now, just used to transfer parameters
     * ot the parent class and initialize the objects
     *
     * @param context shared pointer to the current context
     */
    LevelEditorController(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief render the level editor controller, returns the id of the next
     * controller to render
     *
     * @param context shared pointer to the current context to use
     *
     * @return unsigned short
     */
    unsigned short render(const std::shared_ptr<utils::Context>& context)
    override;

private:

    /* the editor dashboard with all the tool buttons */
    utils::EditorDashboard dashboard;

    /* the cells selector, used to put the cells on the level */
    utils::CellsSelector selector;

    /* the level to display */
    entities::Level level;

    /* the current level floor to display */
    unsigned short floor {0};

    /* many actions can be returned by the dashboard; to keep trace of these
       actions in the controller, we use this id; with this id, we can now
       which dialog window is currently rendered */
    unsigned short currentActionId {0};

    /* custom cursor object */
    widgets::Cursor cursor;

    /* SFML surface that contains the name of the level */
    sf::Text levelNameSurface;

    /* unique pointer to the current rendered dialog, set to null by default
       and if there is no displayed dialog currently */
    std::unique_ptr<popups::Dialog> dialog {nullptr};
};

}
}

#endif
