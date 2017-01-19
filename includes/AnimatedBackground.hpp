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
 * @brief manage the menu background animation
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
     * @brief constructor, does nothin except calling the function to
     * initialize the cells of the background
     *
     * @param context reference to the current context to use
     */
    AnimatedBackground(const utils::Context& context);

    AnimatedBackground(const AnimatedBackground&) = delete;
    AnimatedBackground& operator=(const AnimatedBackground&) = delete;

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~AnimatedBackground() noexcept;

    /**
     * @brief render the animated background, display all the cells
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls some SFML functions that are not
     * noexcept
     */
    void render(const utils::Context& context) const &;

private:

    static constexpr unsigned short BACKGROUND_CELLS_AMOUNT {575};
    static constexpr unsigned short MAXIMUM_RANDOM_NUMBER {28};
    static constexpr unsigned short CELLS_PER_COLUMN {18};

    /**
     * @brief initialize all the cells of the animated background; this
     * method is the unique function that is called by the animated background
     * constructor; the creation of the cells could be done directly into
     * the constructor, but I prefer separate it into a dedicated function, as
     * this method requires a lot of internal variables
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void initializeCells(const utils::Context& context) &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
