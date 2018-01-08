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
 * @file ShapesManager.hpp
 * @brief loads and provides separators for level animations
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 *
 * TODO: #1173 the shape manager is only used for level animations separators,
 * maybe we can simply delete it and handle those separator elsewhere
 */

#ifndef MEMORIS_SHAPESMANAGER_H_
#define MEMORIS_SHAPESMANAGER_H_

#include <memory>

namespace sf
{
class RectangleShape;
}

namespace memoris
{
namespace managers
{

class ShapesManager
{

public:

    /**
     * @brief constructor
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    ShapesManager();

    ShapesManager(const ShapesManager&) = delete;

    ShapesManager& operator=(const ShapesManager) = delete;

    /**
     * @brief default destructor
     */
    ~ShapesManager();

    /**
     * @brief getter for the horizontal mirror animation separator shape
     *
     * @return const sf::RectangleShape&
     */
    const sf::RectangleShape& getHorizontalSeparator() const & noexcept;

    /**
     * @brief getter for the vertical mirror animation separator shape
     *
     * @return const sf::RectangleShape&
     */
    const sf::RectangleShape& getVerticalSeparator() const & noexcept;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
