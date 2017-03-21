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
 * @file Cursor.hpp
 * @brief graphical cursor that moves according to the mouse
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CURSOR_H_
#define MEMORIS_CURSOR_H_

#include <memory>

namespace sf
{
template<typename T>
class Vector2;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class Cursor
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    Cursor(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~Cursor();

    /**
     * @brief render the cursor on the screen
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void render() const &;

    /**
     * @brief getter of the current cursor position
     *
     * @return const sf::Vector2<float>&
     */
    const sf::Vector2<float>& getPosition() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
