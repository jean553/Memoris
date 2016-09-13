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
 * @file AnimatedBackground.hpp
 * @brief manage the menu background animation
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ANIMATEDBACKGROUND_H_
#define MEMORIS_ANIMATEDBACKGROUND_H_

#include "Cell.hpp"
#include "Context.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

namespace memoris
{
namespace utils
{

class AnimatedBackground
{

public:
    /* use deleted functions to prevent copy of class object */

    AnimatedBackground(const AnimatedBackground&) = delete;
    AnimatedBackground operator=(const AnimatedBackground&) = delete;

    /**
     * @brief constructor, does nothin except calling the function to
     * initialize the cells of the background
     *
     * @param context reference to the current context to use
     */
    AnimatedBackground(utils::Context& context);

    /**
     * @brief render the animated background, display all the cells
     *
     * @param context shared pointer to the context to use
     */
    void render(utils::Context& context);

private:

    /**
     * @brief initialize all the cells of the animated background; this
     * method is the unique function that is called by the animated background
     * constructor; the creation of the cells could be done directly into
     * the constructor, but I prefer separate it into a dedicated function, as
     * this method requires a lot of internal variables
     *
     * @param context reference to the current context to use
     */
    void initializeCells(utils::Context& context);

    /* the array of displayed cells in the animated background; we do not know
       in advance the size of the array, it depends of the random generation
       of cells */
    /* NOTE: the container is a pointers container for two reasons: we do not
       have to overwritte the copy constructor of Cell to handle the sprites,
       textures transfert during the copy (when append the object in the
       container); we analyzed that the execution speed is almost ten times
       faster when copying pointers (clock() usage); we use an unique pointer
       because we do not need to handle ownership management of the objects */
    std::vector<std::unique_ptr<entities::Cell>> cells;

    /* last time of the cell movement; we use a SFML unsigned integer of 32
       bits because this is the data type used by the SFML clock; initialize
       the cells movement last animation with the value 0 */
    sf::Uint32 cellsMovementLastAnimation {0};
};

}
}

#endif
