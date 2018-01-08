/**
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
 * @file LevelEditorController.hpp
 * @package controllers
 * @brief renders the level editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELEDITORCONTROLLER_H_
#define MEMORIS_LEVELEDITORCONTROLLER_H_

#include "Controller.hpp"

#include <vector>

namespace memoris
{

namespace entities
{
class Level;
class Cell;
}

namespace controllers
{

class LevelEditorController : public Controller
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level to load and display by default
     * @param tested indicates if the level test time has to be displayed
     *
     * a level pointer is passed to the constructor because a being edited
     * level can be loaded directly when the controller is started,
     * this happens after a test of the current edited level
     *
     * a level time is passed to the constructor because this time
     * is displayed in the editor after a test of the being edited level
     */
    LevelEditorController(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const bool& tested
    );

    /**
     * @brief default destructor
     */
    ~LevelEditorController();

    /**
     * @brief renders the level editor controller
     *
     * @return const ControllerId&
     */
    virtual const ControllerId& render() const & override;

private:

    /**
     * @brief update the level name surface position; the position of this
     * surface is calculated according to its width
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void updateLevelNameSurfacePosition() const &;

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
        const std::vector<std::unique_ptr<entities::Cell>>& cells
    ) const &;

    /**
     * @brief updates the name of the level in the editing level context
     * manager and also updates the level name surface in the level editor
     *
     * @param levelName constant reference to the actuel level name
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void changeLevelName(const std::string& levelName) const &;

    /**
     * @brief renders the controller components only, without foregrounds
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void renderControllerMainComponents() const &;

    /**
     * @brief handles the events of the new level foreground
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void handleNewLevelForegroundEvents() const &;

    /**
     * @brief handles the events of the save level foreground
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void handleSaveLevelForegroundEvents() const &;

    /**
     * @brief handles the events of the controller without foreground
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void handleControllerEvents() const &;

    /**
     * @brief updates the level displayed floor and floor surface
     *
     * @param movement 1 or -1 to move up or down
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void updateFloor(const short& movement) const &;

    /**
     * @brief loads the new level foreground for display
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void openNewLevelForeground() const &;

    /**
     * @brief loads the save level foreground for display
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void openSaveLevelForeground() const &;

    /**
     * @brief resets the level pointer for future usage
     * (before leaving the controller)
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void resetLevel() const &;

    /**
     * @brief saves the level into the dedicated file and
     * updates the level name displayed in the dashboard
     *
     * @param levelName the name of the level
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void saveLevel(const std::string& levelName) const &;

    /**
     * @brief prepares the level for test
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void testLevel() const &;

    /**
     * @brief indicates if a cell is selected into the cells selector
     *
     * @return const bool
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    const bool cellIsSelectedFromCellsSelector() const &;

    /**
     * @brief indicates if the last saved level version has been updated
     *
     * @return const bool
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    const bool lastLevelVersionUpdated() const &;

    /**
     * @brief updates the level name with an asterisk
     * to indicate it has to be saved
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void markLevelHasToBeSaved() const &;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
