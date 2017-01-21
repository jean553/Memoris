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
 * @file AnimatedBackground.hpp
 * @brief main menu background animation
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ANIMATEDBACKGROUND_H_
#define MEMORIS_ANIMATEDBACKGROUND_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace utils
{

class AnimatedBackground
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context to use
     */
    AnimatedBackground(const utils::Context& context);

    AnimatedBackground(const AnimatedBackground&) = delete;
    AnimatedBackground& operator=(const AnimatedBackground&) = delete;

    /**
     * @brief default destructor
     */
    ~AnimatedBackground();

    /**
     * @brief render the animated background, display all the cells
     *
     * utils::Context::getClockMillisecondsTime() and
     * other SFML methods are not noexcept
     */
    void render() const &;

private:

    /**
     * @brief initialize every cells of the animated background
     *
     * entities::Cell constructor is not noexcept as it calls SFML methods
     */
    void initializeCells() const &;

    /**
     * @brief returns a random cell type or return 0
     *
     * @return const char
     */
    const char getCellByRandomNumber() const & noexcept;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
