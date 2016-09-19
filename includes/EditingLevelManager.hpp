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
 * @file EditingLevelManager.hpp
 * @brief manager dynamically created into the context to store data that have
 * to be passed between controllers of level edition
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_EDITINGLEVELMANAGER_H_
#define MEMORIS_EDITINGLEVELMANAGER_H_

#include <memory>

namespace memoris
{
namespace managers
{

class EditingLevelManager
{

public:

    /**
     * @brief default constructor, empty, only declared in order to use
     * forwarding declaration
     */
    EditingLevelManager() noexcept;

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~EditingLevelManager() noexcept;

    /**
     * @brief setter of the level name string; not in constructor because this
     * attribute is empty when the manager is created
     *
     * @param name the name of the level to save into the manager
     *
     * @throw std::bad_alloc the string allocation failed
     *
     * not 'const' because it modifies the levelName attribute
     */
    void setLevelName(const std::string& name) &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
