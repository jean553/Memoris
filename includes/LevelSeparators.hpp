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
 * @file LevelSeparators.hpp
 * @brief two vertical separators, displayed at each side of the level,
 * handled by this separated class because used in both of the game controller
 * and the level controller
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELSEPARATORS_H_
#define MEMORIS_LEVELSEPARATORS_H_

#include "Context.hpp"

namespace memoris
{
namespace utils
{

class LevelSeparators
{

public:

    /**
     * @brief constructor, initializes the two SFML surfaces
     *
     * @param context reference to the current context
     */
    LevelSeparators(utils::Context& context);

    /**
     * @brief renders the two SFML surfaces together
     *
     * @param context reference to the current context
     */
    void display(utils::Context& context) const;

private:

    /* SFML surfaces used for the separator */

    sf::RectangleShape left;
    sf::RectangleShape right;
};

}
}

#endif
