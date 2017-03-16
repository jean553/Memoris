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
 * @file LoseLevelEndingScreen.hpp
 * @brief the losing screen that is displayed when the user loses the level
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LOSELEVELENDINGSCREEN_H_
#define MEMORIS_LOSELEVELENDINGSCREEN_H_

#include "LevelEndingScreen.hpp"

namespace memoris
{
namespace utils
{

class LoseLevelEndingScreen : public LevelEndingScreen
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the context to use
     */
    LoseLevelEndingScreen(const Context& context);

    /* this class use the default definition of render(context) */
};

}
}

#endif
