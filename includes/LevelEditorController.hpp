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
#include "NewLevelDialog.hpp"
#include "aliases.hpp"

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
     * @param context reference to the current context
     */
    LevelEditorController(utils::Context& context);

    /**
     * @brief render the level editor controller, returns the id of the next
     * controller to render
     *
     * @param context reference to the current context to use
     *
     * @return unsigned short
     */
    unsigned short render(utils::Context& context)
    override;

private:

    /**
     * @brief true if the current displayed dialog window is the save level
     * window; this function is declared to refactor common code that is
     * called at different locations
     *
     * @return const bool
     *
     * do not return a reference, because directly return a boolean using
     * the 'return' instruction
     */
    const bool saveDialogIsActive() const noexcept;

    /**
     * @brief true if the current displayed dialog window is the new level
     * window; this function is declared to refactor common code that is
     * called at different locations
     *
     * @return const bool
     *
     * do not return a reference, because directly return a boolean using
     * the 'return' instruction
     */
    const bool newDialogIsActive() const & noexcept;

    /**
     * @brief delete the displayed active dialog window; this function checks
     * first if a dialog window is currently displayed; this function is
     * declared for refactoring purposes
     *
     * not constant because it modifies the dialog pointer
     */
    void deleteActiveDialog() noexcept;

    /**
     * @brief update the level name surface position; the position of this
     * surface is calculated according to its width
     *
     * not constant because it modifies the level name surface position
     */
    void updateLevelNameSurfacePosition() noexcept;

    /**
     * @brief save the current level cells type into a level file, creates a
     * new level file with the given name or overwrittes the existing one
     *
     * @param name the name of the level to create
     * @param cells constant reference to the container of cells pointers
     *
     * @throw std::ios_base::failure thrown if the file manipulation failed;
     * this exception is never caught by the program and the game directly
     * stops
     */
    void saveLevelFile(
        const std::string& name,
        aliases::ConstUniquePtrCellsContainerRef cells
    ) const &;

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

    /* SFML surface that displays the current floor number */
    sf::Text floorSurface;

    std::unique_ptr<popups::SaveLevelDialog> saveLevelDialog {nullptr};
    std::unique_ptr<popups::NewLevelDialog> newLevelDialog {nullptr};
};

}
}

#endif
