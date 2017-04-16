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
 * @brief render the level editor
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
    using Level = std::shared_ptr<entities::Level>;

public:

    /**
     * @brief constructor, empty for now, just used to transfer parameter
     *
     * @param context reference to the current context
     * @param level constant reference to the shared pointer that contains
     * a level to use
     * @param displayTime boolean that indicates if the tested time must
     * be displayed; this boolean is false by default and true if the level
     * has just been tested
     */
    LevelEditorController(
        const utils::Context& context,
        const Level& level,
        const bool& displayTime = false
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
     * @return const ControllerId&
     */
    virtual const ControllerId& render() const & override;

private:

    static constexpr const char* UNNAMED_LEVEL {"unnamed"};
    static constexpr const char* SAVE_LEVEL_NAME_MESSAGE {"Level name"};
    static constexpr const char* ERASE_LEVEL_MESSAGE
        {"Erase the current level ? y / n"};

    static constexpr float CELLS_DEFAULT_TRANSPARENCY {255.f};
    static constexpr float TITLES_HORIZONTAL_POSITION {1200.f};

    static constexpr unsigned short FIRST_FLOOR_INDEX {0};

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
