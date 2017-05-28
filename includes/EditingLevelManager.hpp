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
 * @file EditingLevelManager.hpp
 * @brief manager handles data transfers between editing level controllers
 * (game controller and level editor controller)
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_EDITINGLEVELMANAGER_H_
#define MEMORIS_EDITINGLEVELMANAGER_H_

#include <memory>
#include <vector>

namespace memoris
{

namespace entities
{
class Level;
}

namespace managers
{

class EditingLevelManager
{

public:

    /**
     * @brief constructor
     *
     * @throw std::bad_alloc|std::length_error the string allocation failed;
     * those exceptions are never caught and the program immeidately stops
     */
    EditingLevelManager();

    /**
     * @brief default destructor
     */
    ~EditingLevelManager();

    /**
     * @brief setter of the level name
     *
     * @param name the name of the level to save into the manager
     *
     * @throw std::bad_alloc the string allocation failed
     */
    void setLevelName(const std::string& name) const &;

    /**
     * @brief getter of the level name
     *
     * @return const std::string&
     */
    const std::string& getLevelName() const & noexcept;

    /**
     * @brief setter of the Level shared pointer;
     * used in order to switch between the level editor and the game controller
     *
     * @param level the current level to save
     */
    void setLevel(const std::shared_ptr<entities::Level>& level) const &
        noexcept;

    /**
     * @brief getter of the shared pointer to the level
     *
     * @return const std::shared_ptr<entities::Level>&
     */
    const std::shared_ptr<entities::Level>& getLevel() const & noexcept;

    /**
     * @brief refresh the level pointer;
     * used by the game controller when a tested level is finished
     */
    void refreshLevel() const & noexcept;

    /**
     * @brief make a copy of an array of cells;
     * used after level test in order to restablish initial level
     *
     * @param cells list of cells types
     */
    void setCellsBackup(const std::vector<char>& cells) const & noexcept;

    /**
     * @brief returns a list of characters representing each level cell
     *
     * @return const std::vector<char>&
     */
    const std::vector<char>& getCellsBackup() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
