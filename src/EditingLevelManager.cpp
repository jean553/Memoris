/*
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
 * @file EditingLevelManager.cpp
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditingLevelManager.hpp"

#include <string>

namespace memoris
{
namespace managers
{

class EditingLevelManager::Impl
{

public:

    std::string levelName;
};

/**
 *
 */
EditingLevelManager::EditingLevelManager() :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
EditingLevelManager::~EditingLevelManager() noexcept = default;

/**
 *
 */
void EditingLevelManager::setLevelName(const std::string& name) const &
{
    impl->levelName = name;
}

/**
 *
 */
const std::string& EditingLevelManager::getLevelName() const & noexcept
{
    return impl->levelName;
}

}
}
