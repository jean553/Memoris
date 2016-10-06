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
 * @file WinLevelEndingScreen.hpp
 * @brief the wining screen that is displayed when the user wins the level
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WINLEVELENDINGSCREEN_H_
#define MEMORIS_WINLEVELENDINGSCREEN_H_

#include "LevelEndingScreen.hpp"

namespace memoris
{
namespace utils
{

class WinLevelEndingScreen : public LevelEndingScreen
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls the SFML functions that are not noexcept
     */
    WinLevelEndingScreen(const Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration and to ensure correct destructors calls when
     * using polymorphism
     */
    virtual ~WinLevelEndingScreen() noexcept;

    /**
     * @brief overrite the render(context) function because additional
     * information and animated text have to be displayed for the win screen
     *
     * @param context constant reference to the current context to use
     *
     * not 'const' because the flashing text animation updates the object
     * time attributes
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    virtual void render(const Context& context) & override;

private:

    /**
     * @brief render the flashing animation of the left levels amount text
     *
     * @param context constant reference to the current context to use
     *
     * private because it is simply a refactored of what could be directly
     * done into the render() method; we put this logic here for organization
     * purposes
     */
    void animateLeftLevelsAmount(const Context& context) &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
