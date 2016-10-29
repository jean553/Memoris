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
 * @file ShapesManager.hpp
 * @brief loads and provides sprites assets
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
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

namespace utils
{
class Context;
}

namespace managers
{

class ShapesManager
{

public:

    /**
     * @brief constructor, loads each texture/sprite one by one, stop if one
     * texture cannot be loaded and throw an exception
     *
     * @throw std::invalid_argument thrown if the texture cannot be loaded,
     * the exception is never caught to voluntary stop the program
     */
    ShapesManager();

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~ShapesManager() noexcept;

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
    std::unique_ptr<Impl> impl;
};

}
}

#endif
