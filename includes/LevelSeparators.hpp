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
 * @file LevelSeparators.hpp
 * @brief two vertical lines at both sides of the level cells grid
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELSEPARATORS_H_
#define MEMORIS_LEVELSEPARATORS_H_

#include <memory>

namespace memoris
{
namespace utils
{

class Context;

class LevelSeparators
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    LevelSeparators(const utils::Context& context);

    LevelSeparators(const LevelSeparators&) = delete;

    LevelSeparators& operator=(const LevelSeparators&) = delete;

    /**
     * @brief destructor
     */
    ~LevelSeparators();

    /**
     * @brief renders the separators
     *
     * not noexcept as sf::RenderWindow::draw function is not noexcept
     */
    void display() const &;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
