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
 * @file WinLevelEndingScreen.hpp
 * @brief screen displayed when the user wins the game
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WINLEVELENDINGSCREEN_H_
#define MEMORIS_WINLEVELENDINGSCREEN_H_

#include "AbstractLevelEndingScreen.hpp"

namespace memoris
{
namespace utils
{

class WinLevelEndingScreen : public AbstractLevelEndingScreen
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
    WinLevelEndingScreen(const Context& context);

    /**
     * @brief default destructor
     */
    ~WinLevelEndingScreen();

    /**
     * @brief overrites the rendering function because additional
     * information and animated text have to be displayed for the win screen
     *
     * not const because the object is updated continuously for animations
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    virtual void render() & override;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
