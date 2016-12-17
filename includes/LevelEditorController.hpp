/**
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
 * @file LevelEditorController.hpp
 * @package controllers
 * @brief render the level editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELEDITORCONTROLLER_H_
#define MEMORIS_LEVELEDITORCONTROLLER_H_

#include "Controller.hpp"

#include "aliases.hpp"

namespace memoris
{

namespace entities
{
class Level;
}

namespace controllers
{

class LevelEditorController : public Controller
{
    using Level = std::unique_ptr<entities::Level>;

public:

    /**
     * @brief constructor, empty for now, just used to transfer parameter
     *
     * @param context reference to the current context
     */
    LevelEditorController(
        const utils::Context& context,
        Level level
    );

    /**
     * @brief default destructor, empty, declared in order to use forwarding
     * declaration
     */
    ~LevelEditorController() noexcept;

    /**
     * @brief render the level editor controller, returns the id of the next
     * controller to render
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(
        const utils::Context& context
    ) & override final;

private:

    static constexpr const char* const UNNAMED_LEVEL {"unnamed"};

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
    const bool saveDialogIsActive() const & noexcept;

    /**
     * @brief delete the displayed active dialog window; this function checks
     * first if a dialog window is currently displayed; this function is
     * declared for refactoring purposes
     *
     * not constant because it modifies the dialog pointer
     */
    void deleteActiveDialog() & noexcept;

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
        aliases::ConstUniquePtrCellsContainerRef cells
    ) const &;

    /**
     * @brief updates the name of the level in the editing level context
     * manager and also updates the level name surface in the level editor
     *
     * @param context constant reference to the current context to use
     * @param levelName constant reference to the actuel level name
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void changeLevelName(
        const utils::Context& context,
        const std::string& levelName
    ) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
